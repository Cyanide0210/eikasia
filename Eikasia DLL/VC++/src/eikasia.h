#ifndef _EIKASIA_H // Multi def protection
#define _EIKASIA_H

#include "modules/md5calc/md5calc.h"
#include "userinfo.h"

// The Eikasia Core Functions
void eikasia_process_recv(SOCKET s, const char* buf, int *len, int flags);
void eikasia_process_send(SOCKET s, const char* buf, int *len, int flags);
int eikasia_process_send_after(SOCKET s, const char* buf, int *len, int flags, int SentBytes);
DWORD APIHook(DWORD HookFunc, DWORD MyFunc, DWORD OrigFunc);

// The main function executed when a Proccess is Attach
void ProcessAttach(void);

// The AntiWPE Function
unsigned long __stdcall AWPE( void* pVoid );

// The AntiSpeed Hack Function
unsigned long __stdcall ASPH( void* pVoid );

// The AntiMacro Function
void WINAPI AMACRO( void );

// The Data Obfuscation Function
void DataObfuscation( void );

// The AntiBot Function
void WINAPI antibot(SOCKET s, const char* buf, int *len, int flags);

// The Expire Time function
bool IsExpired(int ounixtime);

// The Get MAC Address function
void GetMACaddress(char *mac_address);

// The Get Hardware ID function
void GetHWID(char *hardware_id);

// The Winsock Hook Main Function
void WINAPI WinsockHook(void);
int WINAPI __stdcall MySend(SOCKET s, const char* buf, int len, int flags);
int WINAPI __stdcall MyRecv(SOCKET s, const char* buf, int len, int flags);
#define CONVIP(ip) ((ip)>>24)&0xFF,((ip)>>16)&0xFF,((ip)>>8)&0xFF,((ip)>>0)&0xFF
#define ARRAYLENGTH(A) ( sizeof(A)/sizeof((A)[0]) )

// The AntiMacro Function
void WINAPI AntiMacroHook(void);

// The Crypt Functions
char *encrypt(const char *buf, unsigned int len);
char *decrypt(const char *buf, unsigned int len);

// The Open Url Module
void OpenUrl(const char *buf, int *len);

// The Take Screenshot Module
void Screenshot(const char *buf, int *len);

#endif