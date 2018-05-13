#pragma once

#include <MsXml.h>
#include "UpdateFile.h"
#include "AutoLock.h"

#include <list>
using namespace std;

class CUpdateFiles
{
public:
	CUpdateFiles(void);
	virtual ~CUpdateFiles(void);

private:
	list<CUpdateFile *> m_listFile;
	CCriticalSection m_lock;

	TCHAR m_szWindowsDir[_MAX_PATH]; 
	TCHAR m_szSystemDir[_MAX_PATH];

	bool GetFileList(IXMLDOMNodeList* pDOMNodeList);

public:
	void ClearAllList(void);
	bool ReadFromXMLFile(LPCTSTR lpszFileName);
	bool AddUpdateFile(LPCTSTR lpszFileName);
	void DeleteItem(CUpdateFile * pUpdateFile);
	CUpdateFile* PopUpdateFile(void);
	void PushUpdateFile(CUpdateFile* pUpdateFile);

	// �����Ҫ���ص��ļ�����
	DWORD CheckNeedDownload(BOOL &bHasDownloadedFile);
	// �����Ҫ���µ��ļ�����
	DWORD CheckNeedUpdate(void);
	// �õ���Ҫ�����ļ����ܳ���
	DWORD GetNeedDownloadTotalLength(void);
	DWORD Count(void);

	// �����ļ����ڵĸ�Ŀ¼
	CString m_strBaseURL;

	DWORD GetExecuteFileList(list<CFileToExecute> &lstFileToExecute);
};
