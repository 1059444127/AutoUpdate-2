#pragma once

#include <vector>
using namespace std;

#define FCS_GWBS_XBORDER			0
#define FCS_GWBS_YBORDER			1

class CFullScreenChecker
{
public:
	CFullScreenChecker(void);
	virtual ~CFullScreenChecker(void);

	// ����Ƿ���ȫ��ģʽ��������
	BOOL IsFullScreen();

	// ����Ƿ���ȫ��ģʽ��������
	BOOL IsFullScreen(CRect rtSrcWnd);

protected:
	// ����Ƿ���ȫ��ģʽ_�ݹ��Ӻ�����������
	BOOL _SubIsFullScreen(HWND hWnd);

	// ����Ƿ���ȫ��ģʽ_�ݹ��Ӻ�����������
	BOOL _SubIsFullScreen(HWND hWnd, CRect rtSrcWnd);

	// �жϾ����Ƿ��ھ����ڲ�
	BOOL IsRectInRect(LPRECT lprcInner, LPRECT lprcOuter);

	// ��ʾ��ö�ٻص�
	static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);

	// �õ�����ʵ�ʾ��δ�С
	void GetWindowRealtimeRect(HWND hWnd, CRect &rect);

	// �õ����ڱ߿�֧��Vista���ϲ���ϵͳ�ı߿���䣩
	INT GetWindowBorderSize(HWND hWnd, INT iIndex);

	// ������ʾ����������
	vector<CRect> m_vecCRect;
};
