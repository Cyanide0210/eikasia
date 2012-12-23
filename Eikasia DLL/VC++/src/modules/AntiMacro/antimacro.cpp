#include <stdio.h>
#include <windows.h>

#include "../../eikasia.h"

#ifdef AntiMacro

735D4A

typedef BOOL (WINAPI *PRHK)(HWND hWnd, int id, UINT fsModifiers, UINT vk);
typedef void (WINAPI *Pkeybd_event) (BYTE bVk, BYTE bScan, DWORD dwFlags, ULONG_PTR dwExtraInfo);
typedef UINT (WINAPI *PSI) (UINT nInputs, LPINPUT pInputs, int cbSize);

PRHK OrigRHK;
Pkeybd_event Origkeybd_event;
PSI OrigSI;

void WINAPI MyRHK (HWND hWnd, int id, UINT fsModifiers, UINT vk) {
}

void WINAPI Mykeybd_event (BYTE bVk, BYTE bScan, DWORD dwFlags, ULONG_PTR dwExtraInfo) {
}

void WINAPI MySI (UINT nInputs, LPINPUT pInputs, int cbSize) {
}




void WINAPI AMACRO(void)
{
	*(PDWORD)&OrigRHK = APIHook((DWORD)GetProcAddress(GetModuleHandle("User32.dll"), "RegisterHotKey"), (DWORD)MyRHK, (DWORD)OrigRHK);
	*(PDWORD)&Origkeybd_event = APIHook((DWORD)GetProcAddress(GetModuleHandle("User32.dll"), "keybd_event"), (DWORD)Mykeybd_event, (DWORD)Origkeybd_event);
	*(PDWORD)&OrigSI = APIHook((DWORD)GetProcAddress(GetModuleHandle("User32.dll"), "SendInput"), (DWORD)MySI, (DWORD)OrigSI);

}
/*
#define AMACRO_TIME_INTERVAL 500 // Time in milliseconds.

unsigned long __stdcall AMACRO( void* pVoid )
{
	unsigned char szBuffer[ 8 ];

	// First bytes of RHK/GTC/TGT
	unsigned char bOriginalRHK[6];
	unsigned char bOriginalUHK[6];
	unsigned char bOriginalSI[6];

	int i;

	unsigned long dwRHKCall = (unsigned long)GetProcAddress( GetModuleHandle( "User32.dll" ), "RegisterHotKey" );
	unsigned long dwUHKCall = (unsigned long)GetProcAddress( GetModuleHandle( "User32.dll" ), "UnregisterHotKey" );
	unsigned long dwSICall = (unsigned long)GetProcAddress( GetModuleHandle( "User32.dll" ), "SendInput" );
	ReadProcessMemory( GetCurrentProcess( ), (void *)dwRHKCall, bOriginalRHK, 6, 0 );
	ReadProcessMemory( GetCurrentProcess( ), (void *)dwUHKCall, bOriginalUHK, 6, 0 );
	ReadProcessMemory( GetCurrentProcess( ), (void *)dwSICall, bOriginalSI, 6, 0 );

	while( true )
	{
		ReadProcessMemory( GetCurrentProcess( ), (void *)dwRHKCall, szBuffer, 6, 0 );
		for( i = 0; i < 6; i++ )
		{
			// RegisterHotKey
			if( bOriginalRHK[ i ] != szBuffer[ i ] )
			{
	FILE *fp = fopen("log.txt", "ab");
	fwrite("aaa", strlen("aaa"), 1, fp);
	fputc(0x0d, fp);
	fputc(0x0a, fp);
	fclose(fp);
				WriteProcessMemory( GetCurrentProcess( ), (void *)dwRHKCall, bOriginalRHK, 6, 0 );
				break;
			}				 
		}

		ReadProcessMemory( GetCurrentProcess( ), (void *)dwUHKCall, szBuffer, 6, 0 );
		for( i = 0; i < 6; i++ )
		{
			// UnregisterHotKey
			if( bOriginalUHK[ i ] != szBuffer[ i ] )
			{
	FILE *fp = fopen("log.txt", "ab");
	fwrite("aaas", strlen("aaas"), 1, fp);
	fputc(0x0d, fp);
	fputc(0x0a, fp);
	fclose(fp);
				WriteProcessMemory( GetCurrentProcess( ), (void *)dwUHKCall, bOriginalUHK, 6, 0 );
				break;
			}				 
		}

		ReadProcessMemory( GetCurrentProcess( ), (void *)dwSICall, szBuffer, 6, 0 );
		for( i = 0; i < 6; i++ )
		{
			// SendInput
			if( bOriginalSI[ i ] != szBuffer[ i ] )
			{
				FILE *fp = fopen("log.txt", "ab");
	fwrite("daaa", strlen("daaa"), 1, fp);
	fputc(0x0d, fp);
	fputc(0x0a, fp);
	fclose(fp);
				WriteProcessMemory( GetCurrentProcess( ), (void *)dwSICall, bOriginalSI, 6, 0 );
				break;
			}				 
		}

		Sleep( AMACRO_TIME_INTERVAL );
	}
	return 0;
};
*/
#endif