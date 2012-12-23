#include <windows.h>
#include "../eikasia.h"

void ProcessAttach(void) {
	//if ( IsExpired(1313798400) ) {
	//	MessageBox(0,"This DLL has been expired","Error",MB_OK);
	//	TerminateProcess(OpenProcess(PROCESS_ALL_ACCESS,0,GetCurrentProcessId()),0); // Close application
	//}
	#ifdef AntiWPE
		CreateThread( 0, 0, &AWPE, 0, 0, NULL);
	#endif

	#ifdef AntiSPH
		CreateThread( 0, 0, &ASPH, 0, 0, NULL);
	#endif

	#ifdef AntiMacro
		AMACRO();
	#endif


	WinsockHook();
	#ifdef DataObf
		DataObfuscation();
	#endif
}
/*if (InVirtualBox())
	TerminateProcess(OpenProcess(PROCESS_ALL_ACCESS,0,GetCurrentProcessId()),0); // Close application
*/
/**********************************************************************
 * md5sum
 **********************************************************************/
/*	#define OMD5SH '0','1','2','3','4','5','6','7','8','9','1','9','a','b','c','d','e','f','0','1','2','3','4','5','6','7','8','9','a','b','c','d' // Place each character between '' and separate from each other with , (letters must be lowercase)
	
	char hashoc[32], pathfile[MAX_PATH];
	
	sprintf( hashoc, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\0", OMD5SH); // To avoid modifying the hash with a hex editor
	GetModuleFileName(NULL,pathfile,sizeof(pathfile));
	
	if(!md5sum(pathfile,(string)hashoc))
	{
		MessageBox(NULL, "The integrity of the application isn\'t the waited.\nPlease contact technical support or reinstall the application.", "The application can\'t start", MB_ICONSTOP|MB_SETFOREGROUND);
		TerminateProcess(OpenProcess(PROCESS_ALL_ACCESS,0,GetCurrentProcessId()),0); // Close application
	}
*/
/*********************************************************************/

// GRF_Header_Editor("data.grf","Custom of Magic",false);
//CheckIntegrity(UserKey);



