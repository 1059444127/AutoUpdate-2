#pragma once

/*!
	\class CDigitGrouping
	\brief ���ַ�����
	\details ���ڽ������ַ�������
*/
class CDigitGrouping
{
public:
	//! ���캯��
	CDigitGrouping(void);
	//! ��������
	~CDigitGrouping(void);

	/*!	\fn CString DigitGrouping(LPCTSTR lpszString)
		\brief ���ַ��麯��
		\details �������ַ��� ��: \a lpszString = _T("1234567890"), �����\a lpszString = _T("1,234,567,890").
		\param[in] lpszString	�����ַ���
		\retval	CString	���ط�����ַ���
	*/
	static CString DigitGrouping(LPCTSTR lpszString);
};