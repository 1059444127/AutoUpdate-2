
// AutoUpdate.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "AutoUpdate.h"
#include "AutoUpdateDlg.h"

#include "..\Common\IniFileOperations.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoUpdateApp

BEGIN_MESSAGE_MAP(CAutoUpdateApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAutoUpdateApp ����

CAutoUpdateApp::CAutoUpdateApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CAutoUpdateApp ����

CAutoUpdateApp theApp;

CGlobal g_objGlobalData;

CLocalizeMgr g_objLocalizeMgr;

CIniFileOperations g_objIniFileOperations(IFO_FILE_NAME, IFO_FILE_EXT);

// CAutoUpdateApp ��ʼ��

BOOL CAutoUpdateApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	::CoInitialize(NULL);

	AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	// SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	HANDLE hMutex = ::CreateMutex(NULL, FALSE, _T("Magon_Auto_Update"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		// ���ʵ���Ѿ�����
		if (hMutex)
		{
			CloseHandle(hMutex);
		}
		return FALSE;
	}

	// ��ȡ�����в�����URL������ID
	CString strCommand = m_lpCmdLine;
	if (!strCommand.IsEmpty())
	{
		INT iPos = strCommand.Find(_T(" "));
		if (iPos > 0)
		{
			// ��ȡURL
			g_objGlobalData.g_strUpdateURL = strCommand.Left(iPos);
			if (g_objGlobalData.g_strUpdateURL.Right(1) != _T("/"))
			{
				g_objGlobalData.g_strUpdateURL += _T("/");
			}

			// ��ȡ����ID
			strCommand = strCommand.Right(strCommand.GetLength() - iPos -1);
			strCommand.Trim();
			if (!strCommand.IsEmpty())
			{
				// ��ȡ����ID
				g_objLocalizeMgr.m_iLangID = _ttoi(strCommand);
			}
			else
			{
				// ��ȡϵͳ����ID
				g_objLocalizeMgr.GetLocaleLangID();
			}
		}
		else
		{
			// ֻ��URLʱ������URL
			g_objGlobalData.g_strUpdateURL = strCommand;
			if (g_objGlobalData.g_strUpdateURL.Right(1) != _T("/"))
			{
				g_objGlobalData.g_strUpdateURL += _T("/");
			}
		}
	}
	else
	{
		// ��ȡϵͳ����ID
		g_objLocalizeMgr.GetLocaleLangID();
		::MessageBox(NULL, g_objLocalizeMgr.GetString(LID_DONT_NEED_MANUAL_CALL_TEXT, LID_DNMCT_DEFAULT), g_objLocalizeMgr.GetString(LID_DONT_NEED_MANUAL_CALL_CAPTION, LID_DNMCC_DEFAULT), MB_ICONERROR);
		return FALSE;
	}
#if  _MSC_VER >= 1400 // vs2005+
	_tcscpy_s(m_lpCmdLine, 1, _T(""));
#else
	_tcscpy(m_lpCmdLine, _T(""));
#endif

	CAutoUpdateDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	::CoUninitialize();

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
