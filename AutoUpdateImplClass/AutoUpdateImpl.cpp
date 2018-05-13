#include "stdafx.h"
#include "AutoUpdateImpl.h"

CAutoUpdateImpl g_objAutoUpdateImpl;

CAutoUpdateImpl::CAutoUpdateImpl(void)
{
	m_hProcess = NULL;

	TCHAR szPath	[_MAX_PATH];
	TCHAR szDrive	[_MAX_DRIVE];
	TCHAR szDir		[_MAX_DIR];
	TCHAR szFName	[_MAX_FNAME];
	TCHAR szExt		[_MAX_EXT];
	GetModuleFileName(NULL, szPath, _MAX_PATH);

#if  _MSC_VER >= 1400 // vs2005+
	_tsplitpath_s(szPath, szDrive, _MAX_DRIVE, szDir, _MAX_DIR, szFName, _MAX_FNAME, szExt, _MAX_EXT);
#else
	_tsplitpath(szPath, szDrive, szDir, szFName, szExt);
#endif

#if  _MSC_VER >= 1400 // vs2005+
	_tmakepath_s(szPath, _MAX_PATH, szDrive, szDir, _T(""), _T(""));
#else
	_tmakepath(szPath, szDrive, szDir, _T(""), _T(""));
#endif

	CString strAutoUpdateClientName = szPath;
	strAutoUpdateClientName += UPDATE_WORKING_DIRECTORY;
	strAutoUpdateClientName += _T("\\");
	strAutoUpdateClientName += UPDATE_FILE_NAME;

	CString strFileName(szFName);
	strFileName.Remove(_T(' '));
	CString strParameters;
	strParameters.Format(_T("%s%s/ %d"), UPDATE_DEFAULT_URL, strFileName, GetLocaleLangID());

	CString strCmdLine;
	strCmdLine.Format(_T("\"%s\" %s"), strAutoUpdateClientName, strParameters);

	if (GetFileAttributes(strAutoUpdateClientName) != INVALID_FILE_ATTRIBUTES)
	{
		CreateProcess(NULL, strCmdLine, NULL, SW_SHOW);
	}
}

CAutoUpdateImpl::~CAutoUpdateImpl(void)
{
	if (m_hProcess != NULL)
	{
		// ��δ�ر�
		if (WaitForSingleObject(m_hProcess, 100) == WAIT_TIMEOUT)
		{
			TerminateProcess(m_hProcess, 1);
			Sleep(1000);
			RefreshTrayIcons();
		}
		CloseHandle(m_hProcess);
	}
}

BOOL CAutoUpdateImpl::CreateProcess(LPCTSTR lpFile, LPCTSTR lpParameters, LPCTSTR lpDirectory, INT nShowCmd)
{
	BOOL bRet = FALSE;
	// vs2005�Ժ�Wow64DisableWow64FsRedirection��Wow64RevertWow64FsRedirection�����ڿ���ֱ����
	// �ʵͰ汾����Ҫ��dll�л�ȡ������ַ
	PVOID oldValue;
#if _MSC_VER < 1400 // for IDE less than vc8(vs2005)
	// �رյ����̵߳��ļ�ϵͳ�ض��򡣲������ڱ����Իָ��ֳ����ļ�ϵͳ�ض���Ĭ�Ͽ�����
	// OldValue [out]
	//	The WOW64 file system redirection value. The system uses this parameter to store information necessary to revert (re-enable) file system redirection.
	typedef	BOOL (WINAPI *lpfnWow64DisableWow64FsRedirection) (PVOID *OldValue);
	// �ָ��ض�����
	typedef	BOOL (WINAPI *lpfnWow64RevertWow64FsRedirection) (PVOID OldValue);

	// ���庯��ָ��
	lpfnWow64DisableWow64FsRedirection Wow64DisableWow64FsRedirection = NULL;
	lpfnWow64RevertWow64FsRedirection Wow64RevertWow64FsRedirection = NULL;

	// ����ϵͳ��̬���ӿ�"Kernel32.dll"
	HINSTANCE hInstance = LoadLibrary(_T("Kernel32.dll"));
	// ������سɹ�
	if (hInstance)
	{
		// �õ�������ַ
		Wow64DisableWow64FsRedirection = (lpfnWow64DisableWow64FsRedirection)GetProcAddress(hInstance, "Wow64DisableWow64FsRedirection");
		Wow64RevertWow64FsRedirection = (lpfnWow64RevertWow64FsRedirection)GetProcAddress(hInstance, "Wow64RevertWow64FsRedirection");
		// ����ر��ض�������óɹ�
		if (Wow64DisableWow64FsRedirection)
		{
#endif
			// ����ر��ض���ʧ��
			if (FALSE == Wow64DisableWow64FsRedirection(&oldValue))
			{
				// ע�⣺�˺�����32λϵͳ�¿϶���ʧ��
				// Show Error Info.
			}
#if _MSC_VER < 1400 // for IDE less than vc8(vs2005)
		}
#endif
		// ִ�в���
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = nShowCmd;
		ZeroMemory(&pi, sizeof(pi));

		if (bRet = ::CreateProcess(lpFile, (LPTSTR)lpParameters, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, lpDirectory, &si, &pi))
		{
			m_hProcess = pi.hProcess;
		}
		// ShellExecute(NULL, _T("open"), lpFile, lpParameters, NULL, nShowCmd);

#if _MSC_VER < 1400 // for IDE less than vc8(vs2005)
		// ����ָ��ض�������óɹ�
		if (Wow64RevertWow64FsRedirection)
		{
#endif
			// ����ָ��ض���ʧ��
			if (FALSE == Wow64RevertWow64FsRedirection(oldValue))
			{
				// ע�⣺�˺�����32λϵͳ�¿϶���ʧ��
				// Show Error Info.
			}
#if _MSC_VER < 1400 // for IDE less than vc8(vs2005)
		}
		// �ͷ�ϵͳ��̬���ӿ���
		FreeLibrary(hInstance);
	}
#endif
	return bRet;
}

INT CAutoUpdateImpl::GetLocaleLangID()
{
	// ������ID
	LANGID wLangPID = PRIMARYLANGID(::GetSystemDefaultLangID());
	// ������ID
	WORD wLangSID = SUBLANGID(::GetSystemDefaultLangID());
	// ��������ID
	switch (wLangPID) 
	{
	case LANG_CHINESE: 
		switch (wLangSID)
		{
		case SUBLANG_CHINESE_HONGKONG:
		case SUBLANG_CHINESE_MACAU:
		case SUBLANG_CHINESE_TRADITIONAL:
			return AUI_CHINESE_TRADITIONAL;
			break;

		case SUBLANG_CHINESE_SINGAPORE:
		case SUBLANG_CHINESE_SIMPLIFIED:
			return AUI_CHINESE_SIMPLE;
			break;

		default:
			return AUI_ENGLISH;
			break;
		}
		break;

	case LANG_ENGLISH: 
		return AUI_ENGLISH;
		break;

	case LANG_TURKISH:
		return AUI_TURKISH;
		break;

	case LANG_GERMAN:
		return AUI_GERMAN;
		break;

	case LANG_FRENCH:
		return AUI_FRENCH;
		break;

	case LANG_ITALIAN:
		return AUI_ITALIAN;
		break;

	case LANG_SPANISH:
		return AUI_SPANISH;
		break;

	case LANG_JAPANESE:
		return AUI_JAPANESE;
		break;

	default:
		return AUI_ENGLISH;
		break;
	}
	return AUI_ENGLISH;
}

void CAutoUpdateImpl::RefreshTrayIcons()
{
	// �õ���������� 
	HWND hTaskbar = ::FindWindow(_T("Shell_TrayWnd"), NULL);
	if (hTaskbar == NULL)
	{
		return;
	}
	// ���½�����
	HWND hNotify = FindWindowEx(hTaskbar, NULL, _T("TrayNotifyWnd"), NULL);
	if (hNotify == NULL)
	{
		return;
	}
	HWND hSysPager = FindWindowEx(hNotify, NULL, _T("SysPager"), NULL); 
	if (hSysPager == NULL)
	{
		return;
	}
	// ���½�����(������ʱ��)
	HWND hIconBox = FindWindowEx(hSysPager, NULL, _T("ToolBarWindow32"), NULL);
	if (hIconBox == NULL)
	{
		return;
	}
	//-------------------�����ǵõ����������½�һ��ط��ľ�� 
	DWORD pid = 0;     
	GetWindowThreadProcessId(hIconBox, &pid);     
	if (pid == 0)
	{
		return;
	}

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_ALL_ACCESS, TRUE, pid);     
	if (hProcess == NULL)
	{
		return;
	}
	::SendMessage(hIconBox, WM_PAINT, NULL, NULL);

	CRect rect;
	::GetWindowRect(hIconBox, &rect);
	::InvalidateRect(hIconBox, &rect, FALSE);

	// ��ȡ��������ͼ�����
	INT iNum = ::SendMessage(hIconBox, TB_BUTTONCOUNT, NULL, NULL);

	ULONG ulN = 0;
	TBBUTTON tButton;
	ULONG hwnd, proid;

	DWORD dwSize = sizeof(TBBUTTON);
	DWORD dwRead;
	TBBUTTON *ptButton = (TBBUTTON *)VirtualAllocEx(hProcess, NULL, sizeof(TBBUTTON), MEM_COMMIT, PAGE_READWRITE);
	if (NULL == ptButton)
	{
		CloseHandle(hProcess);
		return;
	}

	for (INT i=0; i<iNum; i++)
	{
		::SendMessage(hIconBox, TB_GETBUTTON, i, (LPARAM)(LPTBBUTTON)(ptButton));
		if (ReadProcessMemory(hProcess, (LPVOID)ptButton, &tButton, dwSize, &dwRead))
		{
			if (dwRead != dwSize)
			{
				VirtualFreeEx(hProcess, ptButton, dwSize, MEM_DECOMMIT);
				CloseHandle(hProcess);
				return;
			}
		}

		try
		{
			hwnd = NULL;
			ReadProcessMemory(hProcess, (void *)tButton.dwData, &hwnd, 4, &ulN);
		}
		catch(...)
		{
		}

		proid = 0;
		GetWindowThreadProcessId((HWND)hwnd, &proid);
		if (proid == 0)
		{
			::SendMessage(hIconBox, TB_DELETEBUTTON, i, 0); 
		}
	}
	VirtualFreeEx(hProcess, ptButton, dwSize, MEM_DECOMMIT);
	CloseHandle(hProcess);
}