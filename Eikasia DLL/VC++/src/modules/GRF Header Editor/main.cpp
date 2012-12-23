#include <windows.h>
#include <stdio.h>
#include <fstream>

using namespace std;

void GRF_Header_Editor(char* grffile, string header, bool warningbox){

    ofstream dgrffile(grffile, ios::in|ios::out);

    if(dgrffile.fail() && warningbox)
	{
		if(MessageBox(0,"Unable to configure the GRF.\nMay not exist, this being used by another process, or do not have sufficient permissions to write to it.\nPlease contact technical support.\n\nNote: The application can be started, but may not work correctly.\nWould you like to continue anyway?","Unable to configure the GRF",MB_ICONEXCLAMATION|MB_YESNO) == IDNO)
			TerminateProcess(OpenProcess(PROCESS_ALL_ACCESS,0,GetCurrentProcessId()),0); // Close application
	}
	else
	{
        dgrffile.seekp(0, ios::beg);
        dgrffile << header;
        dgrffile.close();
    }

}
