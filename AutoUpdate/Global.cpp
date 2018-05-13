#include "StdAfx.h"
#include "Global.h"

CGlobal::CGlobal(void)
{
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

	// ȡ�ø��¹���Ŀ¼
	g_strUpdateDir = szPath;
	// ȥ�����һ��'\'
	g_strUpdateDir.Delete(g_strUpdateDir.GetLength() - 1, 1);
	// ȥ������Ŀ¼����ò�Ʒ����Ŀ¼
	g_strProductDir = g_strUpdateDir.Left(g_strUpdateDir.ReverseFind(_T('\\')));
}

CGlobal::~CGlobal(void)
{
}

BOOL CGlobal::FileExist(CString strFileName)
{
	DWORD dwAttr = GetFileAttributes(strFileName);
	return (dwAttr != INVALID_FILE_ATTRIBUTES) 
		&& !(dwAttr & FILE_ATTRIBUTE_DIRECTORY);
}

BOOL CGlobal::ShellExecute(LPCTSTR lpOperation, LPCTSTR lpFile, LPCTSTR lpParameters, LPCTSTR lpDirectory, INT nShowCmd)
{
	BOOL bRet = FALSE;
	// vs2005�Ժ�Wow64DisableWow64FsRedirection��Wow64RevertWow64FsRedirection�����ڿ���ֱ����
	// �ʵͰ汾����Ҫ��dll�л�ȡ������ַ
	PVOID oldValue;
	// �رյ����̵߳��ļ�ϵͳ�ض��򡣲������ڱ����Իָ��ֳ����ļ�ϵͳ�ض���Ĭ�Ͽ�����
	// OldValue [out]
	//	The WOW64 file system redirection value. The system uses this parameter to store information necessary to revert (re-enable) file system redirection.
	typedef	BOOL (WINAPI *lpfnWow64DisableWow64FsRedirection) (PVOID *OldValue);
	// �ָ��ض�����
	typedef	BOOL (WINAPI *lpfnWow64RevertWow64FsRedirection) (PVOID OldValue);

	// ���庯��ָ��
	lpfnWow64DisableWow64FsRedirection fnWow64DisableWow64FsRedirection = NULL;
	lpfnWow64RevertWow64FsRedirection fnWow64RevertWow64FsRedirection = NULL;

	// ����ϵͳ��̬���ӿ�"Kernel32.dll"
	HINSTANCE hInstance = LoadLibrary(_T("Kernel32.dll"));
	// ������سɹ�
	if (hInstance)
	{
		// �õ�������ַ
		fnWow64DisableWow64FsRedirection = (lpfnWow64DisableWow64FsRedirection)GetProcAddress(hInstance, "Wow64DisableWow64FsRedirection");
		fnWow64RevertWow64FsRedirection = (lpfnWow64RevertWow64FsRedirection)GetProcAddress(hInstance, "Wow64RevertWow64FsRedirection");
		// ����ر��ض�������óɹ�
		if (fnWow64DisableWow64FsRedirection)
		{
			// ����ر��ض���ʧ��
			if (FALSE == fnWow64DisableWow64FsRedirection(&oldValue))
			{
				// ע�⣺�˺�����32λϵͳ�¿϶���ʧ��
				// Show Error Info.
			}
		}
		// ִ�в���
		bRet = (INT)::ShellExecute(NULL, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd) > 32;
		// ����ָ��ض�������óɹ�
		if (fnWow64RevertWow64FsRedirection)
		{
			// ����ָ��ض���ʧ��
			if (FALSE == fnWow64RevertWow64FsRedirection(oldValue))
			{
				// ע�⣺�˺�����32λϵͳ�¿϶���ʧ��
				// Show Error Info.
			}
		}
		// �ͷ�ϵͳ��̬���ӿ���
		FreeLibrary(hInstance);
	}
	return bRet;
}

// �ж�Ŀ¼�Ƿ����    
BOOL CGlobal::FolderExists(CString strFolderPath)
{
	DWORD attr;
	attr = ::GetFileAttributes(strFolderPath);
	return (attr != (DWORD)(INVALID_FILE_ATTRIBUTES)) && (attr & FILE_ATTRIBUTE_DIRECTORY);
}

// ����Ŀ¼
BOOL CGlobal::CreateFolder(CString strFolderPath)
{
	if (strFolderPath.Mid(1, 1) != _T(":") || strFolderPath.GetLength() < 2)
	{
		return FALSE;
	}
	// �������, ����Ҫ����, ֱ�ӷ���
	if (FolderExists(strFolderPath))
	{
		return TRUE;
	}
	// ���������, �򴴽���һ��Ŀ¼
	else
	{
		if (!CreateFolder(strFolderPath.Left(strFolderPath.ReverseFind(_T('\\')))))
		{
			return FALSE;
		}
	}
	return ::CreateDirectory(strFolderPath, 0);
}

//#ifdef _DEBUG
void CGlobal::OutputDebugString(LPCTSTR lpszFmt, ...)
{
	TCHAR msg[1024];
	memset(msg, 0, 1024);
	va_list args;
	va_start(args, lpszFmt);
#if _MSC_VER >= 1400 // vs2005+
	_vstprintf_s(msg, 1024, lpszFmt, args);
#else
	_vstprintf(msg, lpszFmt, args);
#endif
	va_end(args);
	::OutputDebugString(msg);
}

BOOL CGlobal::ForceDeleteFile( CString strPath)
{
	BOOL ret = TRUE;
	unlocker::File* file = unlocker::Path::Exists((LPCTSTR)strPath);
	if (file) {
		ret = file->ForceDelete();
		delete file;
	}
	return ret;
}

//#endif
