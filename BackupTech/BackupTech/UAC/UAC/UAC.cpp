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

bool OpenProcessToInject(HWND hWnd, HANDLE *pOutProcHandle, DWORD dwPid, const wchar_t *szProcName)
{
    *pOutProcHandle = NULL;

    if(szProcName == NULL){
        printf("Empty process name!\n");
        return false;
    }

    *pOutProcHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
    if(*pOutProcHandle == 0){
        DWORD dwError = GetLastError();

        wchar_t szPID[128];
        _itow_s(dwPid, szPID, _countof(szPID), 10);

        wchar_t szError[128];
        _itow_s(dwError, szError, _countof(szError), 10);

        std::wstring strMsg = L"Error in open process";
        strMsg += szProcName;
        strMsg += L" (pid: ";
        strMsg += szPID;
        strMsg += L") ";

        if(dwError == ERROR_ACCESS_DENIED){
            strMsg += L"ERROR_ACCESS_DENIED\n(we might inject administrator process, choose another process don't need administrator privilege.)\n";
        } else {
            strMsg += L"Error: ";
            strMsg += szError;
        }

        wprintf(L"%ls", strMsg.c_str());
        return false;
    }
    return true;
}

bool GetFilePath(std::wstring &strPath, std::wstring &m_strFilePath, HINSTANCE m_hInstance, int m_iResourceId)
{
    if(m_strFilePath.empty()){
        wchar_t szTempPath[MAX_PATH];
        DWORD dwTemp = GetTempPath(_countof(szTempPath), szTempPath);
        if(dwTemp != 0 && dwTemp < _countof(szTempPath)){
            HRSRC hResource = FindResource(m_hInstance, MAKEINTRESOURCE(m_iResourceId), L"BINARY");
            if(hResource){
                HGLOBAL hLoadedResource = LoadResource(m_hInstance, hResource);
                if(hLoadedResource){
                    LPVOID pLockedResource = LockResource(hLoadedResource);
                    if(pLockedResource){
                        DWORD dwResourceSize = SizeofResource(m_hInstance, hResource);
                        if(dwResourceSize != 0){
                            wchar_t szTempFilePath[MAX_PATH];
                            if(GetTempFileName(szTempPath, L"w7e", 0, szTempFilePath) != 0){
                                HANDLE hFile = CreateFile(szTempFilePath,
                                                    GENERIC_WRITE,
                                                    0,
                                                    NULL,
                                                    CREATE_ALWAYS,
                                                    FILE_ATTRIBUTE_NORMAL,
                                                    NULL);
                                if(INVALID_HANDLE_VALUE != hFile){
                                    DWORD dwBytesWritten = 0;
                                    if(WriteFile(hFile,
                                        pLockedResource,
                                        dwResourceSize,
                                        &dwBytesWritten,
                                        NULL)){
                                        if(dwBytesWritten == dwResourceSize){
                                            m_strFilePath = szTempFilePath;
                                        }
                                        CloseHandle(hFile);
                                        if(m_strFilePath.empty()){
                                            DeleteFile(szTempFilePath);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(!m_strFilePath.empty()){
        strPath = m_strFilePath;
        return true;
    }
    strPath.clear();
    return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
    std::map< DWORD, std::wstring > g_mapProcs;
    HWND hWnd = NULL;
    BOOL bResult;

    bResult = GetProcessList(hWnd, g_mapProcs);

    return 0;
}

