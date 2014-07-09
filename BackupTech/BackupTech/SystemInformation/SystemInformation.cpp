// SystemInformation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <string>
#include <sstream>

typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);
typedef BOOL(WINAPI *PGPI)(DWORD, DWORD, DWORD, DWORD, DWORD);
#define PRODUCT_PROFESSIONAL    0x00000030
#define VER_SUITE_WH_SERVER     0x00008000

bool WindowsVersionName(wchar_t* str, int bufferSize)
{
    OSVERSIONINFOEXW osvi;
    SYSTEM_INFO si;
    BOOL bOsVersionInfoExW;
    DWORD dwType;


    ZeroMemory(&si, sizeof(SYSTEM_INFO));
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEXW));

    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXW);
    bOsVersionInfoExW = GetVersionEx((OSVERSIONINFO*)&osvi);

    if (0 == bOsVersionInfoExW){
        return FALSE;   // Call GetNativeSystemInfo if supported or GetSystemInfo otherwise
    }

    PGNSI

}

int _tmain(int argc, _TCHAR* argv[])
{
    return 0;
}