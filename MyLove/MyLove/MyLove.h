
// MyLove.h : MyLove Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMyLoveApp:
// �йش����ʵ�֣������ MyLove.cpp
//

class CMyLoveApp : public CWinApp
{
public:
	CMyLoveApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyLoveApp theApp;
