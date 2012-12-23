#include <windows.h>
#include <stdio.h>

#include "eikasia.h"
#include "userinfo.h"


extern "C" __declspec (dllexport) void AntiALL( ){} // This is the function to be injected

//*********************************************************************
// * DllMain : Input method of the DLL
// ********************************************************************
extern "C" __declspec (dllexport) BOOL APIENTRY DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved)
{
	switch(reason)
	{					 
		case DLL_PROCESS_ATTACH:
				ProcessAttach();
			break;
				
 		case DLL_PROCESS_DETACH:
			//#include "attachs/process_detach.cpp"
			break;
			
			
		case DLL_THREAD_ATTACH:
			//#include "attachs/Thread Attach.cpp"
			break;
			
				
 		case DLL_THREAD_DETACH:
			//#include "attachs/Thread Detach.cpp"
			break;
		
	}
	return true;
}
