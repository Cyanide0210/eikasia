#ifndef _USERINFO_H // Multi def protection
#define _USERINFO_H

#define UserKey "5be609d096b63a0cc789336dee2f161c653fff21"
#define UserIP "127.0.0.1"
//#define AntiWPE
#define AntiSPH
//#define AntiMacro
#define AntiBot
#define BanMac
//#define BanHwID
//#define DataObf
#define CALL_PROCESS_GRF 0x00735D4A
#define DATAINI "ANTR.INI"
#define DATAINI_CRYPT "ANTR.CRP"
#define PACKETVER	20110101


/*
#define CALL_PROCESS_HOTKEY            0x0050d726
#define FUNC_PROCESS_HOTKEY            0x0050f520
#define FUNC_RAND                      0x0070e8a4
#define FUNC_SRAND                     0x0070e897
#define FUNC_TIME                      0x00710a87
#define FUNC_MALLOC                    0x0070e8c6
#define FUNC_FREE                      0x0070e84f
#define FUNC_SPRINTF                   0x0070e028
*/


#endif

#ifdef AntiBOT
	//bool isencrypt[] = {1,1,0,1,1,0,1,0,1,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,1,1,0,1,0,1,0,1,1,0,0,1,1,1,1,0,0,1,0,0,0,1,1,0,0,1,1,0,1,0,1,0,1,0,0,0,1,1}; // Es cadena o es basura
	//unsigned short pos[] = {44,52,2,32,22,24,10,33,40,12,14,43,59,11,31,8,1,42,34,20,27,54,58,9,55,6,30,61,50,21,25,28,49,62,35,7,45,3,19,29,56,17,13,48,0,51,53,63,5,47,23,18,60,4,26,36,16,38,15,46,37,41,39,57}; // Posicion de cadena o basura
	//unsigned short algoritmo[] = {4,1,19,21,17,11,16,20,0,3,23,10,14,6,2,30,15,24,7,27,31,18,29,12,26,13,9,8,5,22,28,25};
	bool isencrypt[] = {0,0,1,1,1,1,1,0,1,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,1,1,1,0,1,0,1,0,1,1,0,0,1,1,1,1,0,0,1,0,0,0,1,1,0,0,1,1,0,1,0,1,0,1,0,0,0,1,1}; // Es cadena o es basura
	unsigned short pos[] = {44,52,32,2,24,22,10,33,40,12,14,43,59,11,31,8,1,42,34,20,27,54,58,9,55,6,30,61,50,21,25,28,49,62,35,7,45,3,19,29,56,17,13,48,0,51,53,63,5,47,23,18,60,4,26,36,16,38,15,46,37,41,39,57}; // Posicion de cadena o basura
	unsigned short algoritmo[] = {1,4,21,19,17,11,16,20,0,3,23,10,14,6,2,30,15,24,7,27,31,18,29,12,26,13,9,8,5,22,28,25};
#endif
