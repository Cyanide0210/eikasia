#include <windows.h>
#include <ctime>
#include "../../eikasia.h"

bool IsExpired(int ounixtime)
{
	if(ounixtime < time(0))
		return true;
	else
		return false;
}
