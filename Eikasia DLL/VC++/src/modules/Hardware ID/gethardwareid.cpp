#include <windows.h>
#include <stdio.h>

#include "../../eikasia.h"

#ifdef BanHwID
void GetHWID(char *hardware_id)
{
	HW_PROFILE_INFO hwProfileInfo;
	char *hwid = (char *)malloc(sizeof(char));

	if(GetCurrentHwProfile(&hwProfileInfo) != NULL) {
		strncpy(hwid, (hwProfileInfo.szHwProfileGuid)+1, (strlen((hwProfileInfo.szHwProfileGuid)+1))-1);
		sprintf(hardware_id, "%s", hwid);
	}
}
#endif