#include <windows.h>
#include <stdio.h>
#include "../eikasia.h"
#include "dataobfuscator.h"

char *file = "DATA.INI";
char *ofile = "DATA.CRP";

void help(void) {
	puts("Usage: data-obfuscator [options]");
	puts("Options:");
	puts("  Commands\t\t\tDescription");
	puts("-----------------------------------------------------------------------------");
	puts("  No Arguments			Crypt file, DATTA.INI by default");
	puts("  --decrypt, --dc			Decript file, DATA.CPR by default");
	puts("  --help, --h				Displays this help screen");
	puts("  --file, --f				Choose file to encrypt");
	puts("  --ofile, --of			Choose the output file");
	puts("\n");
	exit(1);
}

extern int main( int argc, const char* argv[] )
{
	int i, op = 0;

	for (i = 1; i < argc ; i++) {
		if (strcmp(argv[i], "--file") == 0 || strcmp(argv[i],"--f") == 0) {
			file = NULL;
			file = (char*)malloc(strlen(argv[i+1]));
			memcpy(file, argv[i+1], strlen(argv[i+1]));
			file[strlen(argv[i+1])+1] = '\0';
		}
		if (strcmp(argv[i], "--output-file") == 0 || strcmp(argv[i],"--of") == 0) {
			ofile = NULL;
			ofile = (char*)malloc(strlen(argv[i+1]));
			memcpy(ofile, argv[i+1], strlen(argv[i+1]));
			ofile[strlen(argv[i+1])+1] = '\0';
		}
		if (strcmp(argv[i],"--help") == 0 || strcmp(argv[i],"--h") == 0)
			help();
		else if (strcmp(argv[i], "--decrypt") == 0 || strcmp(argv[i],"--dc") == 0) {
			op = 1;
		}
	}
	Dataobf dt(file, ofile);
	if(op == 1) {
		dt.flip();
		dt.uncrypt();
	} else {
		dt.crypt();
	}

}
