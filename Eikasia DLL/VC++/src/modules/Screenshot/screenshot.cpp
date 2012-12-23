#include <windows.h>
#include <stdio.h>
#include <wingdi.h>
#include <time.h>

#include "../../eikasia.h"

void Screenshot_sub(void)
{
	BITMAPINFO bmi;
	BITMAPFILEHEADER bfh;
	int nWidth;
	int nHeight;

	HWND hWnd;
	HDC hdc;
	HDC memDC;
	HBITMAP hbm;
	HBITMAP hbmOld;
	BYTE *pbBits;

	HANDLE hfile;
	DWORD dwWritten;
	RECT Wrec;

	hWnd = GetForegroundWindow();
	GetWindowRect(hWnd, &Wrec);

	nHeight = Wrec.bottom - Wrec.top;
	nWidth = Wrec.right - Wrec.left;

	hdc = GetWindowDC(hWnd);
	memDC = CreateCompatibleDC(hdc);
	hbm = CreateCompatibleBitmap(hdc, nWidth, nHeight);
	hbmOld = (HBITMAP)SelectObject(memDC, hbm);

	BitBlt(memDC, 0, 0, nWidth, nHeight, hdc, 0, 0, SRCCOPY);

	ZeroMemory(&bmi, sizeof(bmi));

	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = nWidth;
	bmi.bmiHeader.biHeight = nHeight;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = 32 * nWidth * nHeight / 8;

	pbBits = (byte *) malloc(bmi.bmiHeader.biSizeImage); ;

	GetDIBits( memDC, hbm, 0, bmi.bmiHeader.biHeight, pbBits, &bmi, DIB_RGB_COLORS);

	bfh.bfType = ('M' << 8) + 'B';
	bfh.bfSize = sizeof(BITMAPFILEHEADER) + bmi.bmiHeader.biSizeImage + sizeof(BITMAPINFOHEADER);
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


    CreateDirectory("ScreenShot", NULL);
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    strftime(output,128,"ScreenShot\\%d-%m-%y %H_%M_%S.bmp",tlocal);

	hfile = CreateFile( (output), GENERIC_WRITE, 0, 0, OPEN_ALWAYS, 0, 0);

	WriteFile(hfile,&bfh, sizeof(bfh), &dwWritten, NULL);
	WriteFile(hfile,&bmi.bmiHeader, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
	WriteFile(hfile,pbBits, bmi.bmiHeader.biSizeImage, &dwWritten, NULL);

	CloseHandle(hfile);

	SelectObject(memDC, hbmOld);
	DeleteDC(memDC);

	ReleaseDC(hWnd, hdc);
	DeleteObject(hbm);

	free(pbBits);
}

void Screenshot(const char *buf, int *len) {
	char *buf_rest;
	int len_copy = *len - 2;

	// Revise if there is more info in the buffer
	if(len_copy > 0) {
		buf_rest = (char*) malloc(len_copy); // Allocate memory for the rest of the buffer
		memcpy(buf_rest, buf+2, len_copy); // Clone the rest of the original buffer if exists
	}


	// Replace the url for a ack packet
	*(unsigned short*)buf = 0x187; // Packet 0x187
	*(unsigned int*)(buf+2) = 0;
	memcpy((char*)(buf+6), buf_rest, len_copy); // Copy the rest of the original buffer
	memset((char*)(buf+len_copy+6), '\0', 1); // Add the finish null characters
	*len = (6 + len_copy); // Readjust buffer lengh

	Screenshot_sub(); // Take the screenshot
	free(buf_rest); // Free th buf_Rest buffer
}