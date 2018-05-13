// PageUpdateHintCfg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AutoUpdateConfig.h"
#include "PageUpdateHintCfg.h"
#include "..\Common\IniFileOperations.h"


// CPageUpdateHintCfg �Ի���

IMPLEMENT_DYNAMIC(CPageUpdateHintCfg, CPropertyPage)

CPageUpdateHintCfg::CPageUpdateHintCfg()
	: CPropertyPage(CPageUpdateHintCfg::IDD)
{

}

CPageUpdateHintCfg::~CPageUpdateHintCfg()
{
}

void CPageUpdateHintCfg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageUpdateHintCfg, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_ADD, &CPageUpdateHintCfg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_MOD, &CPageUpdateHintCfg::OnBnClickedBtnMod)
	ON_BN_CLICKED(IDC_BTN_DEL, &CPageUpdateHintCfg::OnBnClickedBtnDel)
	ON_BN_CLICKED(IDC_BTN_SAVETOFILE, &CPageUpdateHintCfg::OnBnClickedBtnSavetofile)
	ON_NOTIFY(NM_CLICK, IDC_LIST_LANG_DESCLIST, &CPageUpdateHintCfg::OnNMClickListLangDesclist)
END_MESSAGE_MAP()


// CPageUpdateHintCfg ��Ϣ�������

BOOL CPageUpdateHintCfg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ctrlLangDescList.InsertColumn(0, _T("����"), LVCFMT_LEFT, 100);
	m_ctrlLangDescList.InsertColumn(1, _T("����"), LVCFMT_LEFT, 320);
	m_ctrlLangDescList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	INT iLangCnt = g_objIniFileOperations.GetIniInt(IFO_SECTION_GENERAL, IFO_SG_LANG_CNT, 0);
	CString str, strItem;
	for (INT i=0; i<iLangCnt; i++)
	{
		str.Format(_T("%d"), i);
		if ((strItem = g_objIniFileOperations.GetIniString(IFO_SECTION_GENERAL, str, _T(""))) != _T(""))
		{
			strItem.Insert(0, str);
			m_ctrlComboBoxLangList.AddString(strItem);
		}
	}
	if (iLangCnt)
	{
		m_ctrlComboBoxLangList.SetCurSel(0);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CPageUpdateHintCfg::OnBnClickedBtnAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT iComboBoxSel = m_ctrlComboBoxLangList.GetCurSel();
	if (iComboBoxSel == LB_ERR)
	{
		MessageBox(_T("δѡ�����ԣ�"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (m_ctrlRichEditDesc.GetTextLength() == 0)
	{
		MessageBox(_T("δ��д������"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
		return;
	}
	CString str;
	m_ctrlComboBoxLangList.GetLBText(iComboBoxSel, str);
	if (m_mapLangIDDesc.find(_ttoi(str)) != m_mapLangIDDesc.end())
	{
		MessageBox(_T("�Ѵ��ڣ�����˫����Ŀ��ʹ���޸Ĺ��ܣ�"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
		return;
	}
	m_ctrlRichEditDesc.SetSel(0, -1);
	CString strDesc = m_ctrlRichEditDesc.GetSelText();
	strDesc.Replace(_T("\r"), _T("\\r\\n"));
	m_mapLangIDDesc.insert(pair<UINT, CString>(_ttoi(str), strDesc));

	INT iItem = m_ctrlLangDescList.GetItemCount();
	m_ctrlLangDescList.InsertItem(iItem, str);
	m_ctrlLangDescList.SetItemText(iItem, 1, strDesc);
	m_ctrlRichEditDesc.SetSel(0, -1);
	m_ctrlRichEditDesc.ReplaceSel(_T(""));
}

void CPageUpdateHintCfg::OnBnClickedBtnMod()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT iComboBoxSel = m_ctrlComboBoxLangList.GetCurSel();
	if (iComboBoxSel == LB_ERR)
	{
		MessageBox(_T("δѡ�����ԣ�"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
		return;
	}
	CString str;
	m_ctrlComboBoxLangList.GetLBText(iComboBoxSel, str);
	if (m_mapLangIDDesc.find(_ttoi(str)) == m_mapLangIDDesc.end())
	{
		MessageBox(_T("�����ڣ���ʹ����ӹ��ܣ�"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (m_ctrlRichEditDesc.GetTextLength() == 0)
	{
		MessageBox(_T("δ��д������"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
		return;
	}
	m_ctrlRichEditDesc.SetSel(0, -1);
	CString strDesc = m_ctrlRichEditDesc.GetSelText();
	strDesc.Replace(_T("\r"), _T("\\r\\n"));
	m_mapLangIDDesc.insert(pair<UINT, CString>(_ttoi(str), strDesc));

	INT iItemCnt = m_ctrlLangDescList.GetItemCount();
	for (INT i=0; i<iItemCnt; i++)
	{
		if (m_ctrlLangDescList.GetItemText(i, 0).CompareNoCase(str) == 0)
		{
			m_ctrlLangDescList.SetItemText(i, 1, strDesc);
			m_ctrlRichEditDesc.SetSel(0, -1);
			m_ctrlRichEditDesc.ReplaceSel(_T(""));
			m_mapLangIDDesc[_ttoi(str)] = strDesc;
			break;
		}
	}
}

void CPageUpdateHintCfg::OnBnClickedBtnDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT iListCtrlSel = (INT)m_ctrlLangDescList.GetFirstSelectedItemPosition() - 1;
	if (iListCtrlSel == LB_ERR)
	{
		MessageBox(_T("δѡ����Ҫɾ�����"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
		return;
	}
	CString strPrompt;
	strPrompt.Format(_T("�Ƿ�ȷ��ɾ�� %s �������"), m_ctrlLangDescList.GetItemText(iListCtrlSel, 0));
	if (MessageBox(strPrompt, _T("ѯ��"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		m_mapLangIDDesc.erase(m_mapLangIDDesc.find(_ttoi(m_ctrlLangDescList.GetItemText(iListCtrlSel, 0))));
		m_ctrlLangDescList.DeleteItem(iListCtrlSel);
	}
}

void CPageUpdateHintCfg::OnNMClickListLangDesclist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (pNMItemActivate->iItem == LB_ERR)
	{
		return;
	}
	INT iListCtrlSel = pNMItemActivate->iItem;
	CString strDesc = ((CMFCListCtrl *)GetDlgItem(IDC_LIST_LANG_DESCLIST))->GetItemText(iListCtrlSel, 1);
	strDesc.Replace(_T("\\r\\n"), _T("\r"));
	((CRichEditCtrl *)GetDlgItem(IDC_RICHEDIT2_DESC))->SetSel(0, -1);
	((CRichEditCtrl *)GetDlgItem(IDC_RICHEDIT2_DESC))->ReplaceSel(strDesc);
	CString strLang = ((CMFCListCtrl *)GetDlgItem(IDC_LIST_LANG_DESCLIST))->GetItemText(iListCtrlSel, 0);
	INT iComboBoxItemCnt = m_ctrlComboBoxLangList.GetCount();
	CString str;
	for (INT i=0; i<iComboBoxItemCnt; i++)
	{
		m_ctrlComboBoxLangList.GetLBText(i, str);
		if (str.CompareNoCase(strLang) == 0)
		{
			m_ctrlComboBoxLangList.SetCurSel(i);
			break;
		}
	}
	*pResult = 0;
}

void CPageUpdateHintCfg::OnBnClickedBtnSavetofile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strProductName;
	GetDlgItem(IDC_EDIT_PRODUCTNAME)->GetWindowText(strProductName);
	if (strProductName.IsEmpty())
	{
		MessageBox(_T("����д��Ʒ���ƣ�"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
		GotoDlgCtrl(GetDlgItem(IDC_EDIT_PRODUCTNAME));
		return;
	}
	if (m_mapLangIDDesc.size() == 0)
	{
		MessageBox(_T("���������һ������������"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
		return;
	}
	CFileDialog dlgSaveFile(FALSE, 
		_T(".xml"), 
		_T("UpdateHint.xml"), 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		_T("XML�ļ�(*.xml)|*.xml|�����ļ�(*.*)|*.*||"));

	INT structsize = 0; 
	DWORD dwVersion, dwWindowsMajorVersion, dwWindowsMinorVersion; 

	dwVersion = GetVersion(); 
	dwWindowsMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion))); 
	dwWindowsMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion))); 

	if (dwVersion < 0x80000000)
	{
		structsize = 88;
		// ��ʾ�µ��ļ��Ի��� 
	}
	else
	{
		structsize = 76;
		// ��ʾ�ϵ��ļ��Ի��� 
	}

	dlgSaveFile.m_ofn.lStructSize = structsize; 
	dlgSaveFile.m_ofn.lpstrTitle = _T("ѡ���ļ�����·��"); 

	if (dlgSaveFile.DoModal() == IDOK)
	{
		CFile fileUpdateHint;
		if (fileUpdateHint.Open(dlgSaveFile.GetPathName(), CFile::modeCreate | CFile::modeWrite))
		{
			USES_CONVERSION;
			fileUpdateHint.Write(XML_UH_HEADER, (UINT)strlen(XML_UH_HEADER));

			CHAR szText[512];
			CTime timeNow = CTime::GetCurrentTime();
#if  _MSC_VER >= 1400 // vs2005+
			sprintf_s(szText, 512, XML_UH_PRODUCT_HEADER, T2A(strProductName), T2A(timeNow.Format(_T("%Y-%m-%d  %H:%M:%S"))));
#else
			sprintf(szText, XML_UH_PRODUCT_HEADER, T2A(strProductName), T2A(timeNow.Format(_T("%Y-%m-%d  %H:%M:%S"))));
#endif
			fileUpdateHint.Write(szText, (UINT)strlen(szText));

			fileUpdateHint.Write(XML_UH_DESCRIPTION_HEADER, (UINT)strlen(XML_UH_DESCRIPTION_HEADER));
			CHAR szXMLStr[1024];
			for (map<UINT, CString>::iterator iter=m_mapLangIDDesc.begin(); iter!=m_mapLangIDDesc.end(); iter++)
			{
#if  _MSC_VER >= 1400 // vs2005+
				sprintf_s(szXMLStr, 1024, "\t\t\t<Lang%d>%s</Lang%d>\r\n", iter->first, T2A(iter->second), iter->first);
#else
				sprintf(szXMLStr, "\t\t\t<Lang%d>%s</Lang%d>\r\n", iter->first, T2A(iter->second), iter->first);
#endif
				fileUpdateHint.Write(szXMLStr, (UINT)strlen(szXMLStr));
			}

			fileUpdateHint.Write(XML_UH_DESCRIPTION_TAIL, (UINT)strlen(XML_UH_DESCRIPTION_TAIL));
			fileUpdateHint.Write(XML_UH_PRODUCT_TAIL, (UINT)strlen(XML_UH_PRODUCT_TAIL));
			fileUpdateHint.Write(XML_UH_TAIL, (UINT)strlen(XML_UH_TAIL));
			fileUpdateHint.Close();
			MessageBox(_T("����ɹ���"), _T("��ʾ"), MB_OK | MB_ICONINFORMATION);
		}
	}
}
