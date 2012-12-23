#include <windows.h>
#include <stdio.h>
#include "../../eikasia.h"

#define ASPH_TIME_INTERVAL 500 // Time in milliseconds.

unsigned long __stdcall ASPH( void* pVoid )
{
	unsigned char szBuffer[ 8 ];

	// First bytes of QPC/GTC/TGT
	unsigned char bOriginalQPC[6];
	unsigned char bOriginalGTC[6];
	unsigned char bOriginalTGT[6];

	int i;

	unsigned long dwQPCCall = (unsigned long)GetProcAddress( GetModuleHandle( "Kernel32.dll" ), "QueryPerformanceCounter" );
	unsigned long dwGTCCall = (unsigned long)GetProcAddress( GetModuleHandle( "Kernel32.dll" ), "GetTickCount" );
	unsigned long dwTGTCall = (unsigned long)GetProcAddress( GetModuleHandle( "Winmm.dll" ), "timeGetTime" );
	ReadProcessMemory( GetCurrentProcess( ), (void *)dwQPCCall, bOriginalQPC, 6, 0 );
	ReadProcessMemory( GetCurrentProcess( ), (void *)dwGTCCall, bOriginalGTC, 6, 0 );
	ReadProcessMemory( GetCurrentProcess( ), (void *)dwTGTCall, bOriginalTGT, 6, 0 );

	while( true )
	{
		ReadProcessMemory( GetCurrentProcess( ), (void *)dwQPCCall, szBuffer, 6, 0 );
		for( i = 0; i < 6; i++ )
		{
			// QueryPerformanceCounter
			if( bOriginalQPC[ i ] != szBuffer[ i ] )
			{
				WriteProcessMemory( GetCurrentProcess( ), (void *)dwQPCCall, bOriginalQPC, 6, 0 );
				break;
			}				 
		}

		ReadProcessMemory( GetCurrentProcess( ), (void *)dwGTCCall, szBuffer, 6, 0 );
		for( i = 0; i < 6; i++ )
		{
			// GetTickCount
			if( bOriginalGTC[ i ] != szBuffer[ i ] )
			{
				WriteProcessMemory( GetCurrentProcess( ), (void *)dwGTCCall, bOriginalGTC, 6, 0 );
				break;
			}				 
		}

		ReadProcessMemory( GetCurrentProcess( ), (void *)dwTGTCall, szBuffer, 6, 0 );
		for( i = 0; i < 6; i++ )
		{
			// timeGetTime
			if( bOriginalTGT[ i ] != szBuffer[ i ] )
			{
				WriteProcessMemory( GetCurrentProcess( ), (void *)dwTGTCall, bOriginalTGT, 6, 0 );
				break;
			}				 
		}

		Sleep( ASPH_TIME_INTERVAL );
	}
	return 0;
};