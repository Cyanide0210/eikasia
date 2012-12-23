#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <Iphlpapi.h>
#include <Assert.h>
#include <process.h>

#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


#include "../../eikasia.h"


typedef int (WINAPI *PCONNECT)(SOCKET s, const struct sockaddr *address, int namelen);
typedef int (WINAPI *PGETHOSTBYNAME)(const char *name);
typedef int (WINAPI *PSEND)(SOCKET s, const char* buf, int len, int flags);
typedef int (WINAPI *PRECV)(SOCKET s, const char* buf, int len, int flags);
typedef int (WINAPI *PSENDTO) (SOCKET s, const char *buf, int len, int flags, const struct sockaddr *to, int tolen);
typedef int (WINAPI *PWSASEND)(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
typedef int (WINAPI *PWSARECV)(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
typedef SOCKET (WINAPI *PSOCKET) (int af, int type, int protocol);
typedef int (WINAPI *PCLOSESOCKET) (SOCKET s);

/*
typedef int (WINAPI *PSPRINTF) (char *_Dest, const char *_Format, va_list ap);
typedef time_t (WINAPI *PTIME)(time_t *);

typedef void (WINAPI *PGRFREADER) (char *grf_file, int grf_num);
typedef void (__fastcall *PHOTKEY) (int key_num);
typedef int (WINAPI *PMakeWindow) (int window);
typedef int (WINAPI *PLoginWindow) (int a, int b);
*/
PSOCKET	OrigSocket;
PCONNECT OrigConnect;
PSEND OrigSend;
PSENDTO	OrigSendTo;
PRECV OrigRecv;
PWSASEND OrigWSASend;
PWSARECV OrigWSARecv;
PGETHOSTBYNAME OrigGethost;
PCLOSESOCKET OrigClosesocket;

/*
PGRFREADER OrigGrfReader;
PHOTKEY OrigHotKey;

PMakeWindow OrigMakeWindow;
int WINAPI MyMakeWindow(int window) {
	return OrigMakeWindow(window);
}


PLoginWindow OrigLoginWindow;
int WINAPI MyLoginWindow(int a, int b) {
	return OrigLoginWindow(a, b);
}

PSPRINTF OrigSprintf;
PTIME OrigTime;*/

SYSTEMTIME st;

//===========================Socket===========================
SOCKET WINAPI MySocket(int af, int type, int protocol) {
	return OrigSocket(af, type, protocol);
}

int WINAPI MyClosesocket (SOCKET s) {
	return OrigClosesocket(s);
}
/*
int WINAPI MySprintf (char *_Dest, const char *_Format, ...) {

	va_list ap;
	int ret;

	va_start(ap,_Format);
	ret = vsprintf(_Dest, _Format, ap);
	va_end(ap);

	return ret;
}

void test(char *grf_file, int grf_num) {
	char msgbuf[255];
	const char* grf_files[] = { "data.grf", "rdata.grf" };
	int i = 0, e =0;

	for(i=0; i <= ARRAYLENGTH(grf_files); i++) {
		if(strcmp(grf_files[0],grf_file) == 0)
			break;
		else
			e++;
	}
			FILE *fp = fopen("log.txt", "ab");
			sprintf(msgbuf, "%d - %s", grf_num, grf_file);
			fwrite(msgbuf, strlen(msgbuf), 1, fp);
			fputc(0x0d, fp);
			fputc(0x0a, fp);
			fclose(fp);

	if(e > ARRAYLENGTH(grf_files))
		exit(0);
}

void WINAPI MyGrfReader(char *grf_file, int grf_num) {
	OrigGrfReader(grf_file, grf_num);
	//test(grf_file, grf_num);
}

void __fastcall MyHotKey(int key_num) {
	OrigHotKey(key_num);
	//test(grf_file, grf_num);
}
*/

//===========================SEND===========================
int WINAPI __stdcall MySend(SOCKET s, const char* buf, int len, int flags)
{
	eikasia_process_send(s, buf, &len, flags); // Process the buffer before send

	int SentBytes = OrigSend(s, buf, len, flags);
	if(SentBytes == SOCKET_ERROR) return SentBytes;

	SentBytes = eikasia_process_send_after(s, buf, &len, flags, SentBytes); // Process the buffer after send

	return SentBytes;
}

//===========================RECV===========================
int WINAPI __stdcall MyRecv(SOCKET s, const char* buf, int len, int flags)
{
	int RecvedBytes = OrigRecv(s, buf, len, flags);
	if(RecvedBytes == SOCKET_ERROR) return RecvedBytes;

	eikasia_process_recv(s, buf, &RecvedBytes, flags); // Process the recived buffer
	return RecvedBytes;
}

//===========================CONNECT===========================
int WINAPI __stdcall MyConnect(SOCKET s, const struct sockaddr *address, int namelen)
{
	int errors = OrigConnect(s, address, namelen);
	if(errors == SOCKET_ERROR) return errors;
	return errors;
}

//===========================WSASEND===========================
int WINAPI __stdcall MyWSASend(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	int Errors = OrigWSASend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, lpFlags, lpOverlapped, lpCompletionRoutine);
	if(Errors == SOCKET_ERROR) return Errors;
	return Errors;
}

//===========================WSARECV===========================
int WINAPI __stdcall MyWSARecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	int Errors = OrigWSARecv(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpOverlapped, lpCompletionRoutine);
	if(Errors == SOCKET_ERROR) return Errors;
	return Errors;
}

//===========================GETHOSTBYNAME===========================
int WINAPI __stdcall Mygethostbyname(const char *name)
{
	return OrigGethost(name);

}

//===========================SENDTO===========================
int WINAPI __stdcall MySendTo(SOCKET s, const char *buf, int len, int flags, const struct sockaddr *to, int tolen)
{
	return OrigSendTo(s, buf, len, flags, to, tolen);
}

void WINAPI WinsockHook(void)
{
	WSADATA wsaData;
	//char msgbuf[255];
	WSAStartup(MAKEWORD(1,1), &wsaData);

//	FILE *fp = fopen("log.txt", "ab");
//	sprintf(msgbuf, "%x", GetProcAddress(GetModuleHandle("Ws2_32.dll"), "send"));
//	fwrite(msgbuf, strlen(msgbuf), 1, fp);
//	fputc(0x0d, fp);
//	fputc(0x0a, fp);
//	fclose(fp);

	*(PDWORD)&OrigSend = APIHook((DWORD)GetProcAddress(GetModuleHandle("Ws2_32.dll"), "send"), (DWORD)MySend, (DWORD)OrigSend);
	*(PDWORD)&OrigRecv = APIHook((DWORD)GetProcAddress(GetModuleHandle("Ws2_32.dll"), "recv"), (DWORD)MyRecv, (DWORD)OrigRecv);
	*(PDWORD)&OrigSendTo = APIHook((DWORD)GetProcAddress(GetModuleHandle("Ws2_32.dll"), "sendto"), (DWORD)MySendTo, (DWORD)OrigSendTo);
	*(PDWORD)&OrigGethost = APIHook((DWORD)GetProcAddress(GetModuleHandle("Ws2_32.dll"), "gethostbyname"), (DWORD)Mygethostbyname, (DWORD)OrigGethost);
	*(PDWORD)&OrigClosesocket = APIHook((DWORD)GetProcAddress(GetModuleHandle("Ws2_32.dll"), "closesocket"), (DWORD)MyClosesocket, (DWORD)OrigClosesocket);
	*(PDWORD)&OrigConnect = APIHook((DWORD)GetProcAddress(GetModuleHandle("Ws2_32.dll"), "connect"), (DWORD)MyConnect, (DWORD)OrigConnect);
	*(PDWORD)&OrigSocket = APIHook((DWORD)GetProcAddress(GetModuleHandle("Ws2_32.dll"), "socket"), (DWORD)MySocket, (DWORD)OrigSocket);
	*(PDWORD)&OrigWSASend = APIHook((DWORD)GetProcAddress(GetModuleHandle("Ws2_32.dll"), "WSASend"), (DWORD)MyWSASend, (DWORD)OrigWSASend);
	*(PDWORD)&OrigWSARecv = APIHook((DWORD)GetProcAddress(GetModuleHandle("Ws2_32.dll"), "WSARecv"), (DWORD)MyWSARecv, (DWORD)OrigWSARecv);

//	*(PDWORD)&OrigGrfReader = APIHook(0x005426E0, (DWORD)MyGrfReader, (DWORD)OrigGrfReader);
//	*(PDWORD)&OrigGrfReader = APIHook(0x00735D4A, (DWORD)MyGrfReader, (DWORD)OrigGrfReader);
//	*(PDWORD)&OrigGrfReader = APIHook(0x00540560, (DWORD)MyGrfReader, (DWORD)OrigGrfReader);
//	*(PDWORD)&OrigMakeWindow = APIHook(0x00507540, (DWORD)MyMakeWindow, (DWORD)OrigMakeWindow);
//	*(PDWORD)&OrigLoginWindow = APIHook(0x0045A970, (DWORD)MyLoginWindow, (DWORD)OrigLoginWindow);
//	*(PDWORD)&OrigSprintf = APIHook(FUNC_SPRINTF, (DWORD)MySprintf, (DWORD)OrigSprintf);
//	*(PDWORD)&OrigHotKey = APIHook(FUNC_PROCESS_HOTKEY, (DWORD)MyHotKey, (DWORD)OrigHotKey);
//	*(PDWORD)&OrigTime = APIHook(0x0070E028, (DWORD)MyTime, (DWORD)OrigTime);
}