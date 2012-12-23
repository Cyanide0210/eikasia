#include <windows.h>
#include <stdio.h>

int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	Splash Splash( NULL );
	Splash.Show( NULL, 1000 );
	Sleep ( 1000 );
}

