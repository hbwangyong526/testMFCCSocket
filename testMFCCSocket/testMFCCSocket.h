
// testMFCCSocket.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CtestMFCCSocketApp:
// �йش����ʵ�֣������ testMFCCSocket.cpp
//

class CtestMFCCSocketApp : public CWinApp
{
public:
	CtestMFCCSocketApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CtestMFCCSocketApp theApp;