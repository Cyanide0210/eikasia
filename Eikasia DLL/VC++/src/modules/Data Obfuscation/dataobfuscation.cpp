#include <stdio.h>
#include <windows.h>

#include "../../eikasia.h"

#ifdef DataObf

typedef void (WINAPI *PDATAREADER) (void);
PDATAREADER OrigDataReader;

void PreDataReader( void ) {
	char line[2048];
	char *dline;
	char *pline;
	int i = 0, c;
	FILE *fp = fopen(DATAINI_CRYPT, "rb");

	do {
		c = fgetc(fp);
		line[i] = c;
		i++;
    } while (c != EOF);
	line[i] = '\0';

	pline = (char *)malloc(strlen(line));
	strcpy(pline, line);
	dline = (char *)malloc(strlen(line));
	dline = decrypt(pline, strlen(line));


	FILE *fp2 = fopen(DATAINI, "wb");
	fwrite(dline, strlen(dline), 1, fp2);
	fclose(fp2);

	fclose(fp);
}

void PostDataReader( void ) {
	remove(DATAINI);
}

void WINAPI MyDataReader(void) {
	PreDataReader();
	OrigDataReader();
	PostDataReader();
}

void DataObfuscation( void )
{
	*(PDWORD)&OrigDataReader = APIHook(CALL_PROCESS_GRF, (DWORD)MyDataReader, (DWORD)OrigDataReader);
}

#endif