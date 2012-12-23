#include <stdio.h>
#include <windows.h>
#include "../../eikasia.h"
#define AntiBOT 1
	#include "../../userinfo.h"
#undef AntiBOT


// Antibot Funciton
#ifdef AntiBot
void WINAPI antibot(SOCKET s, const char* buf, int *len, int flags) {
	char antibot[65], enviar[32+1], cadena[32];
	char *buf_rest;
	unsigned short i, tmp = 0;
	int len_copy = *len - (sizeof(antibot)+2);

	// Revise if there is more info in the buffer
	if(len_copy > 0) {
		buf_rest = (char*) malloc(len_copy); // Allocate memory for the rest of the buffer
		memcpy(buf_rest, buf+(strlen(antibot)+2), len_copy); // Clone the rest of the original buffer if exists
	}

	strncpy(antibot,buf+2,65); // Obtenemos la cadena
	antibot[65]='\0'; // Añadimos final de cadena

	// Deshacemos el algoritmo
	for(i=0; i<64; i++){
		if(isencrypt[i]){
			cadena[algoritmo[tmp]] = antibot[pos[i]];
			tmp++;
		}
	}

	cadena[32]='\0'; // Añadimos final de cadena al la cadena a encriptar en MD5

	MD5_String(cadena, enviar); // Encriptamos en MD5 la cadena
	*(unsigned short*)buf = 0x0041; // Paquete 41
	memcpy((char*)buf+2, enviar, sizeof(enviar)); // Añadimos despues del paquete nuestra cadena encriptada
	*len = 2+sizeof(enviar); // Logintud (2 + Longitud cadena a enviar)

	Sleep(500); // Espera de 0.5 segundos para prevenir envio muy rapido de paquetes

	MySend(s, buf, *len, flags); // Enviamos la cadena al servidor

	// Replace the antibot packet for a ack packet
	*(unsigned short*)buf = 0x187; // Packet 0x187
	*(unsigned int*)(buf+2) = 0;
	memcpy((char*)(buf+6), buf_rest, len_copy); // Copy the rest of the original buffer
	memset((char*)(buf+len_copy+6), '\0', 1); // Add the finish null characters
	*len = (6 + len_copy); // Readjust buffer lengh
}
#endif