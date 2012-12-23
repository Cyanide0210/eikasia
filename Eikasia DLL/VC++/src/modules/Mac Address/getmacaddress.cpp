#include <windows.h>
#include <stdio.h>
#include <Iphlpapi.h>
#include <Assert.h>
#pragma comment(lib, "iphlpapi.lib")

#include "../../eikasia.h"

void GetMACaddress(char *mac_address)
{
	IP_ADAPTER_INFO AdapterInfo[16];			// Allocate information for up to 16 NICs
	DWORD dwBufLen = sizeof(AdapterInfo);		// Save the memory size of buffer
	DWORD dwStatus = GetAdaptersInfo(			// Call GetAdapterInfo
		AdapterInfo,							// [out] buffer to receive data
		&dwBufLen);								// [in] size of receive data buffer
	assert(dwStatus == ERROR_SUCCESS);			// Verify return value is valid, no buffer overflow
	PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;// Contains pointer to current adapter info
	sprintf(mac_address,"%02X:%02X:%02X:%02X:%02X:%02X", pAdapterInfo->Address[0],pAdapterInfo->Address[1],pAdapterInfo->Address[2],pAdapterInfo->Address[3],pAdapterInfo->Address[4],pAdapterInfo->Address[5]);
}
