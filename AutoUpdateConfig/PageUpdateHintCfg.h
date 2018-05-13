#pragma once

#define m_ctrlComboBoxLangList	(*((CComboBox *)GetDlgItem(IDC_COMBO_LANGLIST)))
#define m_ctrlLangDescList		(*((CMFCListCtrl *)GetDlgItem(IDC_LIST_LANG_DESCLIST)))
#define m_ctrlRichEditDesc		(*((CRichEditCtrl *)GetDlgItem(IDC_RICHEDIT2_DESC)))

// CPageUpdateHintCfg �Ի���

class CPageUpdateHintCfg : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageUpdateHintCfg)

public:
	CPageUpdateHintCfg();
	virtual ~CPageUpdateHintCfg();

// �Ի�������
	enum { IDD = IDD_PAGE_UPDATEHINTCFG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();

	map<UINT, CString> m_mapLangIDDesc;

	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnMod();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnSavetofile();
	afx_msg void OnNMClickListLangDesclist(NMHDR *pNMHDR, LRESULT *pResult);
};
