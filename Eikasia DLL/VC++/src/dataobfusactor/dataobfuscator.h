#ifndef _DATAOBF_H
#define _DATAOBF_H

#include <windows.h>
#include <stdio.h>
#include "../eikasia.h"

class Dataobf
{
	public:
		Dataobf(char *,char *);
		~Dataobf();
		void crypt(void);
		void uncrypt(void);
		void flip(void);

	private:
		char *file;
		char *ofile;
};

#endif