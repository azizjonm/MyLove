// ICMP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <WinSock2.h>
#include <IPHlpApi.h>

#define ICMP_HEADERS_SIZE    (sizeof(ICMP4_ECHO_REPLY) + 8)

#define STATUS_OK       0
#define STATUS_SINGLE   1
#define STATUS_PROCESS_NOT_CREATED  2

#define TRANSFER_SUCCESS    1
#define TRANSFER_FAILURE    0

#define DEFAULT_TIMEOUT         3000
#define DEFAULT_DELAY           200
#define DEFAULT_MAX_BLANKS      10
#define DEFALUT_MAX_DATA_SIZE   64

FARPROC()

int _tmain(int argc, _TCHAR* argv[])
{
    return 0;
}

