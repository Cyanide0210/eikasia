#include <windows.h>
#include <stdio.h>
#include "../../eikasia.h"

/**********************************************************************
 * Function Anti Winsock Packet Editor :: Check the integrity of Send and Recv each x time (500ms by default).
 **********************************************************************/
#define AWPE_TIME_INTERVAL 500 // Time in milliseconds.


bool bHooked = false;

unsigned long __stdcall AWPE( void* pVoid )
{
	unsigned char szBuffer[ 8 ];

	// First bytes of Send/Recv
	unsigned char bOriginalRevc[6];
	unsigned char bOriginalSend[6];

	int i;

	unsigned long dwRecvCall = (unsigned long)GetProcAddress( GetModuleHandle( "WS2_32.dll" ), "recv" );
	unsigned long dwSendCall = (unsigned long)GetProcAddress( GetModuleHandle( "WS2_32.dll" ), "send" );
	ReadProcessMemory( GetCurrentProcess( ), (void *)dwRecvCall, bOriginalRevc, 6, 0 );
	ReadProcessMemory( GetCurrentProcess( ), (void *)dwSendCall, bOriginalSend, 6, 0 );

	while( true )
	{
		ReadProcessMemory( GetCurrentProcess( ), (void *)dwRecvCall, szBuffer, 6, 0 );


		for( i = 0; i < 6; i++ )
		{
			// Recv
			if( bOriginalRevc[ i ] != szBuffer[ i ] )
			{
				WriteProcessMemory( GetCurrentProcess( ), (void *)dwRecvCall, bOriginalRevc, 6, 0 );
				break;
			}				 
		}

		ReadProcessMemory( GetCurrentProcess( ), (void *)dwSendCall, szBuffer, 6, 0 );
		
		for( i = 0; i < 6; i++ )
		{
			// Send
			if( bOriginalSend[ i ] != szBuffer[ i ] )
			{
				WriteProcessMemory( GetCurrentProcess( ), (void *)dwSendCall, bOriginalSend, 6, 0 );
				break;
			}
		}
		
		Sleep( AWPE_TIME_INTERVAL );
	}
	return 0;
};