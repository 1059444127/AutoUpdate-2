#pragma once

#pragma comment(lib,"version.lib")

class CUpdateFile
{
public:
	CUpdateFile(LPCTSTR lpszFilePath);
	virtual ~CUpdateFile(void);
	BOOL InitUpdateFile();
// 	//   int newer = WhichIsNewer(argv[1],argv[2]);
// 	//   switch(newer) {
// 	//      case 1:
// 	//      case 2: printf("%s is newer\n",argv[newer]); break;
// 	//      case 3: printf("they are the same version\n"); break;
// 	//      case 0:
// 	//      default: printf("there was an error\n"); break;
// 	//   }
// 	INT WhichIsNewer(TCHAR *fname1, TCHAR *fname2);

	static INT CheckVersionNewer(CString &strVersion1, CString &strVersion2);

private:
//	void EmitErrorMsg (HRESULT hr);
	HRESULT GetFileVersion(LPCTSTR szFileName, VS_FIXEDFILEINFO *vsf);
	HRESULT GetFileDate(LPCTSTR szFileName, FILETIME *pft);
	HRESULT LastError();

//	bool GetVersion(TCHAR* pszFileName);
	VS_FIXEDFILEINFO m_vfixedFileInfo;

public:
	ULONGLONG m_ullSize;
	CString m_strFileName;
	CString m_strFileVersion;
	CString m_strProductVersion;

	INT		m_iLangID;
	bool	m_bRegister;		// �Ƿ�ע�ᣬ����������Ҫע��
	CString m_strInstallDir;	// WINDOWSDIR SYSTEMDIR CURRENTDIR ��װĿ¼
	bool	m_bZipFile;			// �Ƿ�ΪZIP�ļ�������ǣ�Ҫ��ѹ
	bool	m_bForceOverwrite;	// �Ƿ񸲸� ������°汾�����������ǣ������ֵΪ�棬����������
	bool	m_bUpdateNotExist;	// �����ڲŸ��¡����ڲ�����
	bool	m_bExecute;			// �Ƿ�ִ��
	CString m_strExecParam;		// ���ִ�У�ִ�в���
	CString m_strLocalPath;		// ��װ�����·��
//	FILETIME m_fileTime;		// �ļ�����
	CString m_strFilePath;		// �����ļ�����·��
	CString m_strURL;			// ������URL��ַ��HTTP���ļ��������� m_strFileName ��ͬ
	CString m_strMD5;			// �ļ�MD5ֵ�����ڱȶԺ�У��
// 	CString m_strUserName;		// ����ṩ��¼����¼�û���
// 	CString m_strPassword;		// ����ṩ��¼����¼����

	// ��鵱ǰ�ļ��Ƿ���Ҫ����
	INT CheckNeedUpdate();
	// ��鵱ǰ�ļ��Ƿ���Ҫ����
	INT CheckNeedDownload(BOOL &bHasDownloadedFile);
	// �鿴�Ƿ��Ѿ����أ������Ƿ���Ҫ����
	INT CheckDownloadedAndIfNeedUpdate(BOOL &bHasDownloadFile);
	// �鿴���¿ͻ����Ƿ��Ѿ����أ������Ƿ���Ҫ����
	INT CheckSelfDownloadedAndIfNeedUpdate(BOOL &bHasDownloadFile);
	BOOL m_bLocalNeedUpdate;
};

class CFileToExecute
{
public:
	CFileToExecute(CUpdateFile *pUpdateFile)
	{
		m_strPath = g_objGlobalData.g_strProductDir + _T("\\") + pUpdateFile->m_strFileName;

		m_bRegister = pUpdateFile->m_bRegister;
		m_bZipFile = pUpdateFile->m_bZipFile;
		m_bExecute = pUpdateFile->m_bExecute;
		m_strExecParam = pUpdateFile->m_strExecParam;
	}
	virtual ~CFileToExecute(void) {}

	CString m_strPath;
	bool	m_bRegister;		// �Ƿ�ע�ᣬ����������Ҫע��
	bool	m_bZipFile;			// �Ƿ�ΪZIP�ļ�������ǣ�Ҫ��ѹ
	bool	m_bExecute;			// �Ƿ�ִ��
	CString m_strExecParam;		// ���ִ�У�ִ�в���
};

class CFileToUpdateInfo
{
public:
	CFileToUpdateInfo(CUpdateFile *pUpdateFile)
	{
		m_strSrcPath = pUpdateFile->m_strFilePath + UPDATE_FILE_POSTFIX;
		m_strDetPath = g_objGlobalData.g_strProductDir + _T("\\") + pUpdateFile->m_strFileName;
	}
	virtual ~CFileToUpdateInfo(void) {}

	// �ڸ���Ŀ¼������Ŀ¼��
	CString m_strSrcPath;
	// �ڲ�ƷĿ¼��
	CString m_strDetPath;
};