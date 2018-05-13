#pragma once

/*!
	\class CIniFileOperations
	\brief �����ļ�������
	\details ���������ļ�����
*/
class CIniFileOperations
{
public:
	//! ���캯��
	CIniFileOperations(void);
	//! ��������
	~CIniFileOperations(void);

	/*!	\fn INT GetIniInt(LPCTSTR lpszSection, LPCTSTR lpszKey, INT iDefault)
		\brief ��ȡ����ֵ
		\param[in] lpszSection		����
		\param[in] lpszKey			����
		\param[in] iDefault			����ȡʧ��ʹ�õ�Ĭ��ֵ
		\retval INT					��ȡ��������ֵ
	*/
	INT GetIniInt(LPCTSTR lpszSection, LPCTSTR lpszKey, INT iDefault);
	/*!	\fn void WriteIniInt(LPCTSTR lpszSection, LPCTSTR lpszKey, INT iIn)
		\brief д������ֵ
		\param[in] lpszSection		����
		\param[in] lpszKey			����
		\param[in] iIn				��д���ֵ
	*/
	void WriteIniInt(LPCTSTR lpszSection, LPCTSTR lpszKey, INT iIn);

	/*!	\fn CString GetIniString(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpDefault)
		\brief ��ȡ�ַ���ֵ
		\param[in] lpszSection		����
		\param[in] lpszKey			����
		\param[in] lpDefault		����ȡʧ��ʹ�õ�Ĭ��ֵ
		\retval CString				��ȡ�����ַ���ֵ
	*/
	CString GetIniString(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpDefault);
	/*!	\fn void WriteIniString(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpString)
		\brief д���ַ���ֵ
		\param[in] lpszSection		����
		\param[in] lpszKey			����
		\param[in] lpString			��д����ַ���ֵ
	*/
	void WriteIniString(LPCTSTR lpszSection, LPCTSTR lpszKey, LPCTSTR lpString);

	/*!	\fn BOOL GetIniStruct(LPCTSTR lpszSection, LPCTSTR lpszKey, LPVOID lpStruct, UINT uSizeStruct)
		\brief ��ȡ�ṹֵ
		\param[in] lpszSection		����
		\param[in] lpszKey			����
		\param[in] lpStruct			���ڴ洢�Ŀռ��ָ��
		\param[in] uSizeStruct		�ṹ��С
		\retval BOOL				�Ƿ��ȡ�ɹ�(�ɹ�����\b TRUE, ʧ�ܷ���\b FALSE)
	*/
	BOOL GetIniStruct(LPCTSTR lpszSection, LPCTSTR lpszKey, LPVOID lpStruct, UINT uSizeStruct);
	/*!	\fn void WriteIniStruct(LPCTSTR lpszSection, LPCTSTR lpszKey, LPVOID lpStruct, UINT uSizeStruct)
		\brief д��ṹֵ
		\param[in] lpszSection		����
		\param[in] lpszKey			����
		\param[in] lpStruct			��Ŵ�д��Ľṹ�ռ��ָ��
		\param[in] uSizeStruct		�ṹ��С
	*/
	void WriteIniStruct(LPCTSTR lpszSection, LPCTSTR lpszKey, LPVOID lpStruct, UINT uSizeStruct);

protected:
	//! Ini�����ļ�·��
	CString m_strIniFilePath;
};

//! ȫ�������ļ���������
extern CIniFileOperations g_objIniFileOperations;
