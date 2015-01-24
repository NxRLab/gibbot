#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <assert.h>

#define BYTES_TO_TX 1
#define BYTES_TO_RX 1
#define SIZE 100

#define BAUD_RATE 9600 //CBR_115200

#define READ_TIMEOUT_MS 35
#define WRITE_TIMEOUT_MS 35

static HANDLE hComm;
static char info[SIZE];

int open_comm()
{
	hComm = CreateFile(  TEXT("\\\\.\\COM24"),
                    GENERIC_READ | GENERIC_WRITE, 
                    0, 
                    0, 
                    OPEN_EXISTING,
                    0,
                    0);

	if (hComm == INVALID_HANDLE_VALUE) {
		return -1;
	}

	COMMTIMEOUTS comm_to = {0, READ_TIMEOUT_MS, 0, WRITE_TIMEOUT_MS, 0};
	SetCommTimeouts(hComm, &comm_to);

	// set comm parameters
	DCB dcb = {0};
	if(GetCommState(hComm, &dcb) == 0) {
		CloseHandle(hComm);
		return -3;
	}

	dcb.BaudRate = BAUD_RATE;
	dcb.fParity = FALSE;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;

	if(SetCommState(hComm, &dcb) == 0) {
		CloseHandle(hComm);
		return -4;
	}

	if(SetupComm(hComm, 1600, 1600) == 0) {
		CloseHandle(hComm);
		return GetLastError();
		return -8;
	}

	return 0;
}

int write_comm(char *buf, int len)
{
	DWORD bytes;

	WriteFile(hComm, buf, len, &bytes, NULL);
	/*
	if(WriteFile(hComm, buf, len, &bytes, NULL) == FALSE) {
		return GetLastError();
	}
	*/

	return 0;
}

int read_comm(char *buf, int len)
{
	DWORD bytes;

	ReadFile(hComm, buf, len, &bytes, NULL);
	/*
	if(ReadFile(hComm, buf, len, &bytes, NULL) == FALSE) {
		return GetLastError();
	}
	*/

	return 0;
}

int close_comm()
{
	CloseHandle(hComm);
	return 0;
}

double print_time(LARGE_INTEGER *freq, LARGE_INTEGER *start, LARGE_INTEGER *stop)
{
	assert(stop->QuadPart > start->QuadPart);
	return (stop->QuadPart - start->QuadPart) / (freq->QuadPart * 1.0);
}

#define DATA_LEN 12
#define BUF_LEN 10
#define PIC_LEN 17
int main(int argc, char *argv[])
{
	int rc, i;
	char buf[BUF_LEN];
	LARGE_INTEGER ws, we, rs, re;
	//char data[] = "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char data[DATA_LEN];
	double wsum, rsum;
	LARGE_INTEGER freq;

	memset(data, 'U', DATA_LEN);
	memset(buf, 0, BUF_LEN);

	QueryPerformanceFrequency(&freq);

	rc = open_comm();
	if(rc) {
		return rc;
	}

	//write_comm(buf, 1);

	rsum = wsum = 0;
	int run = 1;
	int err = 0, j;

	char key = 0;
	while(key != 'q') {
		key = (char) _getch();
		write_comm(&key, 1);
		read_comm(buf, 1);
		putch(buf[0]);
		//printf("%s", buf);
	}


	for(i = 0; i < run; i++) {
		QueryPerformanceCounter(&ws);
		write_comm(data, DATA_LEN);
		QueryPerformanceCounter(&we);

		QueryPerformanceCounter(&rs);
		read_comm(buf, DATA_LEN);
		QueryPerformanceCounter(&re);

		for(j = 0; j < DATA_LEN; j++) {
			if(data[j] != buf[j]) {
				err++;
			}
		}

		wsum += print_time(&freq, &ws, &we);
		rsum += print_time(&freq, &rs, &re);
		memset(buf, 0, DATA_LEN);
	}

	double avg_wr = wsum / run;
	double avg_rd = rsum / run;
	double rtt =  (8 * DATA_LEN) / (avg_wr + avg_rd);

	printf("baud rate: %d (bps)\n", BAUD_RATE);
	printf("packet size: %d\n", DATA_LEN);
	printf("number of runs: %d\n", run);
	printf("avg. error: %d (%g%%)\n", err, (err * 1.0) / (DATA_LEN * run) * 100);
	printf("avg. write time: %g (us)\n", avg_wr * 1e6);
	printf("avg. read time: %g (us)\n", avg_rd * 1e6);
	printf("avg. RTT: %g (bps)\n", rtt);
	printf("avg. RTT: %g (Bps)\n", rtt / 8);

	close_comm();

	_getch();
	return 0;
}