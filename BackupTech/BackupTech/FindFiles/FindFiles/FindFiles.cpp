// FindFiles.cpp : 定义控制台应用程序的入口点。
//

// Reference:   [求一程序：如何使用C\C++实现文件的检索 ？](http://zhidao.baidu.com/link?url=AB5qFE0souzBGk1cOvtEd24vciARWuIXlynajp7nG8IuZifa2I9YOrwP5n3ms47jctc6Ayk_OCBSn3421fTF3K)
//              [C++及API函数实现查找某目录下指定类型的文件](http://ltoiii.blog.163.com/blog/static/243828642009924104952805/)
//              [制作单元测试(gtest)辅助动态库接口之获取指定目录的直接文件路径](http://blog.csdn.net/infoworld/article/details/8221128)
//              [c++遍历某个路径下的所有文件](http://bbs.csdn.net/topics/390368005)
//              [一​个​C​+​+​类​实​现​文​件​全​盘​搜​索](http://wenku.baidu.com/link?url=eqQmlyi57CJkce9C5a6Z-5n1_Qv7bbwV5f-Uz_1OyioBVH0UP4hxkGkSDrkv-Hdzg8LQW2Y3Q_7DTIOXRjlZ-4PM5wBRqWaqNcYBT9pPd0u)
//              [C++遍历文件夹下的文件](http://www.oschina.net/code/snippet_119226_6095)
//              [SearchFile](http://www.pudn.com/downloads208/sourcecode/windows/system/detail977523.html)
//              [Windows下怎么按时间查找文件](http://www.myexception.cn/cpp/1510408.html)
//              [how to search the computer for files and folders](http://stackoverflow.com/questions/3365182/how-to-search-the-computer-for-files-and-folders)
//              [How can I get a list of files in a directory using C or C++?](http://stackoverflow.com/questions/612097/how-can-i-get-a-list-of-files-in-a-directory-using-c-or-c)
//              [如何通过使用 Visual C++ 以递归方式搜索文件夹](http://support.microsoft.com/kb/307009)
//              [Listing the Files in a Directory](http://msdn.microsoft.com/en-us/library/windows/desktop/aa365200%28v=vs.85%29.aspx)
//              [c++实现对文件目录树形打印](http://blog.csdn.net/qiuchengw/article/details/2985958)
//              [CFileFind Class](http://msdn.microsoft.com/en-us/library/f33e1618.aspx)

#include "stdafx.h"

void DirectorySearch(const TCHAR *dir)
{
    WIN32_FIND_DATA FindFileData;
    CFileFind FileFind;

    // TCHAR windows, when you define UNICODE, it will be wide char
    // or it will be ANSI
    // wchar_t C language wide char
    // so, when you need deal with wide char, just replace all string function strxxx into wcsxxx
    // or just replace all char/wchar_t into TCHAR && all string function strxxx/wcsxxx into _tcsxxx, all the strings have _TEXT()
    // then define ANSI/UNICODE whatever you want
    TCHAR dirPathTemp[MAX_PATH];
    TCHAR dirCodeTemp[MAX_PATH];
    _tcscpy_s(dirPathTemp, _tcslen(dir) + 1, dir);
    _tcscpy_s(dirCodeTemp, _tcslen(dir) + 1, dir);

    const TCHAR *pChar = _tcsrchr(dir, _TEXT('\\'));
    if(pChar != NULL && _tcslen(pChar) == 1){
        _tcscat_s(dirCodeTemp, _TEXT("*"));
    } else {
        _tcscat_s(dirCodeTemp, _TEXT("\\*"));
        _tcscat_s(dirPathTemp, _TEXT("\\"));
    }

    HANDLE hSearch = FindFirstFile(dirCodeTemp, &FindFileData);
    if(hSearch == INVALID_HANDLE_VALUE){
        printf("FindFirstFile failed (%d)\n", GetLastError());
        return;
    }

    if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0){
        std::wcout << _TEXT("FileName: ") << FindFileData.cFileName << _TEXT(" \n\tSize: ")
            << FindFileData.nFileSizeHigh * ((DWORDLONG)MAXDWORD + 1) + FindFileData.nFileSizeLow << std::endl;
    } else {
        std::wcout << _TEXT("DirectoryName: ") << FindFileData.cFileName << std::endl;
    }

    while(FindNextFile(hSearch, &FindFileData)){
        if(!_tcscmp(FindFileData.cFileName, _TEXT(".")) || !_tcscmp(FindFileData.cFileName, _TEXT(".."))){
            continue;
        }

        TCHAR szDirFileTemp[MAX_PATH];
        _tcscpy_s(szDirFileTemp, _tcslen(szDirFileTemp) + 1, dirPathTemp);
        _tcscat_s(szDirFileTemp, FindFileData.cFileName);
        if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0){
            std::wcout << _TEXT("FileName: ") << FindFileData.cFileName << _TEXT(" \n\tSize: ")
                << FindFileData.nFileSizeHigh * ((DWORDLONG)MAXDWORD + 1) + FindFileData.nFileSizeLow << std::endl;
        } else {
            std::wcout << _TEXT("DirectoryName: ") << FindFileData.cFileName << std::endl;
            _tcscat_s(szDirFileTemp, _TEXT("\\"));
            DirectorySearch(szDirFileTemp);
        }
    }
    FindClose(hSearch);
    hSearch = INVALID_HANDLE_VALUE;
}


int _tmain(int argc, _TCHAR* argv[])
{
    DirectorySearch(_TEXT("J:\\Entertainment\\Music"));
    return 0;
}

