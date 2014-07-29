// UAC.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <Windows.h>

bool GetProcessList(HWND hWnd, std::map<DWORD, std::wstring> &mapProcess)
{
    bool bResult = false;
    mapProcess.clear();

    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(INVALID_HANDLE_VALUE == hSnapShot){
        printf("Failed to call CreateToolhelp32Snapshot function!\n");
    } else {
        bool bFirst = true;
        PROCESSENTRY32 pe;

        while(true){
            ZeroMemory(&pe, sizeof(PROCESSENTRY32));
            pe.dwSize = sizeof(PROCESSENTRY32);

            BOOL bPR = FALSE;

            if(bFirst){
                bFirst = false;
                bPR = Process32First(hSnapShot, &pe);
            } else {
                bPR = Process32Next(hSnapShot, &pe);
            }

            if(!bPR){
                DWORD dwErr = GetLastError();
                if(ERROR_NO_MORE_FILES != dwErr){
                    printf("Failed to call Process32First/Process32Next function!\n");
                } else if (mapProcess.empty()){
                    printf("Process32First/Process32Next function returns empty!\n");
                } else {
                    bResult = true;
                }
                break;
            }

            // insert all processes we can access
            HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);
            if(hProc != 0){
                CloseHandle(hProc);
                mapProcess.insert( std::make_pair(pe.th32ProcessID, pe.szExeFile) );
            }
        }
        CloseHandle(hSnapShot);
    }
    return bResult;
}
int _tmain(int argc, _TCHAR* argv[])
{
    std::map< DWORD, std::wstring > g_mapProcs;
    HWND hWnd = NULL;
    BOOL bResult;

    bResult = GetProcessList(hWnd, g_mapProcs);

    return 0;
}

