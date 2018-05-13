#pragma once

#include <afxinet.h>
#include "Thread.h"
#include "updatefile.h"

#define WM_DOWNLOADFILE			(WM_USER + 100)
#define WM_DOWNLOADFILEEND		(WM_USER + 101)
#define WM_TRAYICONNOTIFY		(WM_USER + 102)

typedef enum DOWNLOAD_FILE_TYPE
{
	FILELIST_XML = 0, 
	UPDATEHINT_XML, 
	GENERAL_FILE
};

// ÿ��ʵ��������һ�� GET �߳�
class CInetFile : public CThread
{
public:
	class CInetFileSession : public CInternetSession
	{
	public:
		CInetFileSession(LPCTSTR pszAppName, INT nMethod): CInternetSession(pszAppName, 1, nMethod){};

		virtual void OnStatusCallback(DWORD dwContext, DWORD dwInternetStatus,
			LPVOID lpvStatusInfomration, DWORD dwStatusInformationLen) 
		{
			if (dwInternetStatus == INTERNET_STATUS_CONNECTED_TO_SERVER)
				return;
		};
	};

	class CInetFileException : public CException
	{
	public:
		CInetFileException(INT nCode = 0) : m_nErrorCode(nCode){};
		~CInetFileException() {}

		INT m_nErrorCode;
	};

	CInetFile(void);
	virtual ~CInetFile(void);
	CString GetLastError(void);
	bool GetInetFile();

private:
	CString m_strLastErr;
	void ThrowInetFileException(INT nCode);
	virtual void ThreadProcMain(void);

public:
	bool m_bProgressMode;
	DOWNLOAD_FILE_TYPE m_dlFileType;
	CString m_strPath;
	CString m_strFileName;
	CString m_strURL;
	HWND m_hWnd;
	bool m_bWantStop;
	INT m_nDownloadTime;	// ���ش���
	UINT m_nAlreadyDown;
	DWORD m_dwTotalLen;

	INT		m_iLangID;
	bool	m_bRegister;		// �Ƿ�ע�ᣬ����������Ҫע��
	bool	m_bZipFile;			// �Ƿ�ΪZIP�ļ�������ǣ�Ҫ��ѹ (Ŀǰ����)
	bool	m_bForceOverwrite;	// �Ƿ񸲸� ������°汾�����������ǣ������ֵΪ�棬���������� (Ŀǰ����)
	bool	m_bExecute;			// �Ƿ�ִ��
	bool	m_bUpdateNotExist;	// ������ʱ�Ÿ���
	CString m_strExecParam;		// ���ִ�У�ִ�в���
	CString m_strMD5;			// �ļ�MD5������У��
};
