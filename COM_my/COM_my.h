
// COM_my.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCOM_myApp: 
// �йش����ʵ�֣������ COM_my.cpp
//

class CCOM_myApp : public CWinApp
{
public:
	CCOM_myApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCOM_myApp theApp;