
// AutoUpdateDlg.h : ͷ�ļ�
//

#pragma once

#include "AutoLock.h"
#include "UpdateFiles.h"
#include "InetFiles.h"

// CAutoUpdateDlg �Ի���
class CAutoUpdateDlg : public CDialog
{
// ����
public:
	CAutoUpdateDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AUTOUPDATE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	DWORD m_dwCount;
	DWORD m_dwTotalLen;
	DWORD m_dwAlreadyDownLen;

	CCriticalSection m_lock;

	CUpdateFiles m_RemoteFiles;
	CInetFiles m_InetFiles;

	UINT m_nMaxDownThread;
	UINT m_nCurThreadCount;
	BOOL m_bShowTrayInfo;

	CString m_strTrayInfo;

	NOTIFYICONDATA m_tNID;

	BOOL m_bSelfNeedUpdate;

	CRect m_rtTrayShowPt;

	HANDLE m_hStartDownloadFileThread;

	BOOL m_bNeedThreadRun;

	// �������ؽ���
	BOOL m_bHideWindow;

	// �رճ���ʱ���Ƿ�Ҫ����ִ���ļ��б��е��ļ�
	BOOL m_bExecuteFiles;

	// ���ڱ���Ҫִ�е��ļ��б�
	list<CFileToExecute> m_lstFileToExecute;

	static DWORD WINAPI _StartDownloadFileThread(LPVOID lParam);

	LRESULT OnTrayIconNotify(WPARAM wParam, LPARAM lParam); 

	LRESULT OnDownLoadFile(WPARAM wParam, LPARAM lParam);
	LRESULT OnDownLoadFileEnd(WPARAM wParam, LPARAM lParam);

	// У���ļ����鿴�Ƿ�ɸ���
	BOOL ValidateFiles();

	// ��ʼ������
	void StartCheckUpdate();

	// �����ļ�
	void BackupFiles();

	// ��ԭ�ļ�
	void RestoreFiles();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnYes();
	afx_msg void OnBnClickedBtnNo();
};
