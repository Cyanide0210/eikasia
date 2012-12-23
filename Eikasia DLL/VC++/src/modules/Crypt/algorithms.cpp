#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "../../eikasia.h"

char *substr(char* cadena, int comienzo, int longitud)
{
	if (longitud == 0) 
		longitud = strlen(cadena)-comienzo-1;
	
	char *nuevo = (char *)malloc(sizeof(char) * longitud);
	
	strncpy(nuevo, cadena + comienzo, longitud);
	
	return nuevo;
}


char *encrypt(const char *buf, unsigned int len)
{
	char *ch, *chx;
	char *key_md5;
	char *buf_copy;
	unsigned int x = 0, i;

	ch = (char*)malloc(len+1);
	chx = (char*)malloc(len+1);
	buf_copy = (char*)malloc(len);
	key_md5 = (char*)malloc(33);

	memcpy(buf_copy, buf, len);
	MD5_String(UserKey, key_md5);

	for (i = 0; i < len; i++) {
		if( buf_copy[i] == '\0') {
			ch[i] = '\0';
		} else {
			if(x == strlen(key_md5)) {
				x = 0;
			}
			ch[i] = *substr(key_md5, x, 1);
			x++;
		}
	}
	ch[len] = '\0';

	for (i = 0; i < len; i++) {
		if( buf_copy[i] == '\0') {
			chx[i] = '\0';
		} else {
			chx[i] = (char) ( ( (int)*substr(buf_copy, i, 1) ) + ( (int)*substr(ch, i, 1) % 256) );
		}
	}
	chx[len] = '\0';

	return chx;
}

char *decrypt(const char *buf, unsigned int len_)
{
	char *ch, *chx;
	char *key_md5;
	char *buf_copy;
	unsigned int x = 0, i;
	unsigned int len = len_ -2; // FIXME

	ch = (char*)malloc(len+1);
	chx = (char*)malloc(len+1);
	buf_copy = (char*)malloc(len);
	key_md5 = (char*)malloc(33);

	memcpy(buf_copy, buf, len);
	MD5_String(UserKey, key_md5);

	for (i = 0; i < len; i++) {
		if( buf_copy[i] == '\0') {
			ch[i] = '\0';
		} else {
			if(x == strlen(key_md5)) {
				x = 0;
			}
			ch[i] = *substr(key_md5, x, 1);
			x++;
		}
	}
	ch[len] = '\0';

	for (i = 0; i < len; i ++) {
		if( buf_copy[i] == '\0') {
			chx[i] = '\0';
		} else {
			if ( (int)substr(buf_copy, i, 1) < (int)substr(ch, i, 1) ) {
				chx[i] = (char)( ((int)*substr(buf_copy, i, 1) + 256) - (int)*substr(ch, i, 1));
			} else {
				chx[i] = (char)( (int)(*substr(buf_copy, i, 1)) - (int)*substr(ch, i, 1) );
			}
		}
	}
	chx[len] = '\0';

	return chx;
}