#include <windows.h>
#include <stdio.h>
#include "../../eikasia.h"

void OpenUrl(const char *buf, int *len) {
	char *url, *buf_rest;
	int npcid = *(unsigned int*)(buf+2);
	int slen = *(unsigned int*)(buf+6);
	int len_copy = *len - (slen+10);

	// Revise if there is more info in the buffer
	if(len_copy > 0) {
		buf_rest = (char*) malloc(len_copy); // Allocate memory for the rest of the buffer
		memcpy(buf_rest, buf+(slen+10), len_copy); // Clone the rest of the original buffer if exists
	}

	url = (char*) malloc(slen); // Allocate memory for the url
	strncpy(url, buf+10, slen); // Get the URL from the recv buffer
	*(url+slen) = '\0'; // Add the null character after the whole url to prevent weird characters
	ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL); // Open the url

	// Replace the url for a ack packet
	*(unsigned short*)buf = 0x187; // Packet 0x187
	*(unsigned int*)(buf+2) = 0;
	memcpy((char*)(buf+6), buf_rest, len_copy); // Copy the rest of the original buffer
	memset((char*)(buf+len_copy+6), '\0', 1); // Add the finish null characters
	*len = (6 + len_copy); // Readjust buffer lengh
	
	free(url); // Free the url buffer
	free(buf_rest); // Free th buf_Rest buffer
}

