
// AutoUpdateConfig.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAutoUpdateConfigApp:
// �йش����ʵ�֣������ AutoUpdateConfig.cpp
//

class CAutoUpdateConfigApp : public CWinAppEx
{
public:
	CAutoUpdateConfigApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAutoUpdateConfigApp theApp;