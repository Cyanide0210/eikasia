#include "dataobfuscator.h"

Dataobf::Dataobf(char *fp, char *fp2)
{
	file = NULL;
	ofile = NULL;
	file = (char*)malloc(strlen(fp)+1);
	ofile = (char*)malloc(strlen(fp2)+1);
	memcpy(file, fp, strlen(fp));
	memcpy(ofile, fp2, strlen(fp2));
	file[strlen(fp)] = '\0';
	ofile[strlen(fp2)] = '\0';
}

Dataobf::~Dataobf()
{
}


void Dataobf::crypt(void) {
	int c, k = 0;
	char *eline;
	char *pline;
	char line[2048];
	FILE *fp;
	FILE *fp2;

	fp = fopen(file, "rb");
	if (fp==NULL) {
		perror("Error opening file");
		perror(file);
		exit(1);
	}
	do {
		c = fgetc(fp);
		line[k] = (char)c;
		k++;
	} while (c != EOF);
	line[k] = '\0';
	fclose(fp);

	pline = (char *)malloc(strlen(line));
	strcpy(pline, line);
	eline = (char *)malloc(strlen(line));
	eline = encrypt(pline, strlen(pline));

	fp2 = fopen(ofile, "wb");
	fwrite(eline, strlen(eline), 1, fp2);
	fclose(fp2);
	exit(0);
}

void Dataobf::uncrypt (void) {
	int c, k = 0;
	char *eline;
	char *pline;
	char line[2048];
	FILE *fp;
	FILE *fp2;

	fp = fopen(file, "rb");
	if (fp==NULL) {
		perror("Error opening file");
		exit(1);
	}
	do {
		c = fgetc(fp);
		line[k] = (char)c;
		k++;
	} while (c != EOF);
	line[k] = '\0';
	fclose(fp);

	pline = (char *)malloc(strlen(line));
	strcpy(pline, line);
	eline = (char *)malloc(strlen(line));
	eline = decrypt(pline, strlen(line));

	fp2 = fopen(ofile, "wb");
	fwrite(eline, strlen(eline), 1, fp2);
	fclose(fp2);
	exit(0);
}


void  Dataobf::flip(void) {
	char *cfile;

	cfile = (char*)malloc(strlen(file)+1);
	memcpy(cfile, file, strlen(file));
	cfile[strlen(file)] = '\0';
	free(file);
	file = NULL;

	file = (char*)malloc(strlen(ofile)+1);
	memcpy(file, ofile, strlen(ofile));
	file[strlen(ofile)] = '\0';
	free(ofile);
	ofile = NULL;

	ofile = (char*)malloc(strlen(cfile)+1);
	memcpy(ofile, cfile, strlen(cfile));
	ofile[strlen(cfile)] = '\0';
	free(cfile);
	cfile = NULL;

}