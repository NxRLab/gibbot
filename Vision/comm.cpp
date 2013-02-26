// WinCommExample.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <conio.h>
#include "fcdynamic.h"

#define BYTES_TO_SEND 10

static HANDLE hComm;
static unsigned char info[BYTES_TO_SEND];

int open_comm()
{
	hComm = CreateFile( TEXT("COM4"),
                    GENERIC_READ | GENERIC_WRITE, 
                    0, 
                    0, 
                    OPEN_EXISTING,
                    0,
                    0);

	if (hComm == INVALID_HANDLE_VALUE) {
		return -1;
	}

	DCB dcb = {0};
	if(GetCommState(hComm, &dcb) == 0) {
		CloseHandle(hComm);
		return -3;
	}

	dcb.BaudRate = CBR_9600;
	dcb.fParity = FALSE;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;

	if(SetCommState(hComm, &dcb) == 0) {
		CloseHandle(hComm);
		return -4;
	}

	return 0;
}

int write_comm(TrackingWindow *win, int box_x, int box_y)
{
/*
	double theta;
	DWORD bytes;

	theta = atan2(win->yc - box_y, win->xc - box_x) * 10000;
	info[0] = 'X';
	info[1] = (unsigned char) (cvRound(win->xc) >> 8);
	info[2] = (unsigned char) cvRound(win->xc);
	info[3] = 'Y';
	info[4] = (unsigned char) (cvRound(win->yc) >> 8);
	info[5] = (unsigned char) cvRound(win->yc);
	info[6] = 'T';
	info[7] = (unsigned char) (cvRound(theta) >> 8);
	info[8] = (unsigned char) (cvRound(theta));

	if(WriteFile(hComm, info, BYTES_TO_SEND, &bytes, NULL) == FALSE) {
		return -5;
	}
*/
	return 0;
}

int close_comm()
{
	CloseHandle(hComm);
	return 0;
}