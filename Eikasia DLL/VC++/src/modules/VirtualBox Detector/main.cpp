#include <windows.h>
#include <Tlhelp32.h>

bool InVirtualBox()
{
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 procinfo = { sizeof(PROCESSENTRY32) };
	while(Process32Next(handle, &procinfo))
	{
		if(!strcmp(procinfo.szExeFile, "VBoxService.exe"))
		{
			CloseHandle(handle);
			return true;
		}
	}
	CloseHandle(handle);
	return false;
}
