#pragma once

// ���ػ��������ԣ�
#include "LocalizeMgr.h"
#include "LocalizeItemDefinition.h"

// ǿ��ɾ���������ļ�
#include "unlocker.hpp"

// ȫ�����
#include "FullScreenChecker.h"

#define MG_SAFE_DELETE(ptr)				{if (ptr) { delete (ptr); (ptr) = NULL; }}
#define MG_SAFE_DELETEA(pBase)			{if (pBase) { delete [] (pBase); (pBase) = NULL; }}
#define MG_SAFE_RELEASE(ptr)			{if (ptr) { (ptr)->Release(); (ptr) = NULL; }}

#define WORKING_DIRECTORY_DOWNLOAD		_T("\\Download\\")
#define WORKING_DIRECTORY_CONFIG		_T("\\Config\\")
#define WORKING_DIRECTORY_BACKUP		_T("\\Backup\\")

#define FILENAME_FILELIST_XML			_T("FileList.xml")
#define FILENAME_UPDATEHINT_XML			_T("UpdateHint.xml")

#define IFO_FILE_NAME					_T("\\Config\\Config")
#define IFO_FILE_EXT					_T("ini")

#define IFO_SECION_AUTO_UPDATE			_T("AutoUpdate")

// #define IFO_SAU_READY_TO_UPDATE			_T("ReadyToUpdate")
// #define IFO_SAU_RTU_DFT_VALUE			FALSE

typedef enum E_UPDATE_STATUS
{
	// δ��ʼ
	E_US_NOTSTART = 0, 
	// ���ڸ���
	E_US_UPDATING
} E_UPDATE_STATUS;

#define IFO_SAU_UPDATE_STATUS			_T("UpdateStatus")
#define IFO_SAU_US_DFT_VALUE			E_US_NOTSTART

#define IFO_SAU_USER_IGNORED			_T("UserIgnored")
#define IFO_SAU_UI_DFT_VALUE			FALSE

#define IFO_SAU_LAST_PRODUCT_VERSION	_T("LastProductVersion")
#define IFO_SAU_LPV_DFT_VALUE			_T("")

#define IFO_SAU_LAST_UPDATE_TIME		_T("LastUpdateTime")

// ���������ʾ����
#define PROMPT_NETWORK_ERROR_DAYS		30

// ���صĴ������ļ���ʱ��׺
#define UPDATE_FILE_POSTFIX				_T(".update")

// �û������˳�
#define EXIT_CODE_USER_CANCEL			2
// û�п��ø���
#define EXIT_CODE_NO_UPDATE_AVAILABLE	1
// ���¹����У���������
#define EXIT_CODE_ERROR_OCCURRED		-1
// û�д���
#define EXIT_CODE_ERROR_SUCCESS			0

// ��ʱ��

// ������ʾ�������ض�ʱ��
#define TIMERID_TRAY_HIDE				0
#define TIMER_TRAY_HIDE_ELAPSE			100

// ��ʾ������Ϣ�Ի���ʱ��
#define TIMERID_SHOW_UPDATE_HINT_DLG	1
#define TIMER_SHOW_UH_DLG_ELAPSE		1000

// ��ʾ����������ݶ�ʱ��
#define TIMERID_SHOW_DOWNLOAD_COMPLETE	2
#define TIMER_SHOW_DC_ELAPSE			1000

// ��ʾȷ���滻�Ի���
#define TIMERID_SHOW_CONFIRM_UPDATE_DLG	3
#define TIMER_SHOW_CU_DLG_ELAPSE		1000

// ��ʾ����������ݶ�ʱ��
#define TIMERID_SHOW_UPDATE_COMPLETE	4
#define TIMER_SHOW_UC_ELAPSE			1000

// ��ʾ������ʱ
#define TIMERID_TRAY_BALLOON_TIMEOUT	255
#define TIMER_TRAY_BALLOON_TIMEOUT		3000

// ������Ϣˢ��ʱ����
#define INTERVAL_TIME_TRAY_INFO			500

// ��ʾ������ʾ�Ի�����Ϣ
#define WM_USER_SHOW_UPDATE_HINT		(WM_USER + 1000)
#define WM_USER_ADD_FILES_TO_LIST		(WM_USER_SHOW_UPDATE_HINT + 1)

class CGlobal
{
public:
	CGlobal(void);
	~CGlobal(void);

	// �����в����������ļ��б�����Ŀ¼URL
	CString g_strUpdateURL;

	// ��Ʒ����Ŀ¼
	CString g_strProductDir;
	// ���¹���Ŀ¼�����¹���Ŀ¼�ڲ�ƷĿ¼��һ�������˳���Ͳ�Ʒ����ͬһ��Ŀ¼�У�
	CString g_strUpdateDir;

	// �鿴�ļ��Ƿ����
	static BOOL FileExist(CString strFileName);

	// �ļ����Ƿ����
	static BOOL FolderExists(CString strFolderPath);

	// �����ļ���
	static BOOL CreateFolder(CString strFolderPath);

	// ǿ��ɾ���ļ�
	static BOOL ForceDeleteFile(CString strFolderPath);

	// ִ���ļ���64λ���ݣ�
	static BOOL ShellExecute(LPCTSTR lpOperation, LPCTSTR lpFile, LPCTSTR lpParameters, LPCTSTR lpDirectory, INT nShowCmd);

//#ifdef _DEBUG
	static void OutputDebugString(LPCTSTR lpszFmt, ...);
//#else
//	static void OutputDebugString(...){}
//#endif

	// ȫ�����
	CFullScreenChecker m_objFullScreenChecker;
};

extern CGlobal g_objGlobalData;
