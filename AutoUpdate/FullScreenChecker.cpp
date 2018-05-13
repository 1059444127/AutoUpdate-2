#include "StdAfx.h"
#include "FullScreenChecker.h"

CFullScreenChecker::CFullScreenChecker(void)
{
	// ���ֻ��һ����Ļ��ֱ�����
	if (GetSystemMetrics(SM_CMONITORS) == 1)
	{
		m_vecCRect.push_back(
			CRect(0, 
			0, 
			GetSystemMetrics(SM_CXSCREEN), 
			GetSystemMetrics(SM_CYSCREEN)
			));
	}
	// ������������Ļ����
	else
	{
		EnumDisplayMonitors(NULL, NULL, &CFullScreenChecker::MonitorEnumProc, (LPARAM)(vector<CRect> *)&m_vecCRect);
	}
}

CFullScreenChecker::~CFullScreenChecker(void)
{
}

BOOL CALLBACK CFullScreenChecker::MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)   
{
	vector<CRect> *pvecCRect = (vector<CRect> *)dwData;
	pvecCRect->push_back(*lprcMonitor);
	return TRUE;
}

BOOL CFullScreenChecker::IsRectInRect(LPRECT lprcInner, LPRECT lprcOuter)
{
	// �жϾ����Ƿ��ھ����ڲ�
	return lprcOuter->top <= lprcInner->top 
		&& lprcOuter->bottom >= lprcInner->bottom 
		&& lprcOuter->left <= lprcInner->left 
		&& lprcOuter->right >= lprcInner->right;
}

void CFullScreenChecker::GetWindowRealtimeRect(HWND hWnd, CRect &rect)
{
	WINDOWPLACEMENT wp;
	::GetWindowPlacement(hWnd, &wp);

	// ����������
	if (wp.flags != WPF_RESTORETOMAXIMIZED)
	{
		rect = wp.rcNormalPosition;
		// ̮������Ե����
		rect.DeflateRect(GetWindowBorderSize(hWnd, FCS_GWBS_XBORDER), GetWindowBorderSize(hWnd, FCS_GWBS_YBORDER));
	}
	// �����
	else
	{
		// �õ���������С������Ļ��Сȥ��������
		CRect rtWorkArea;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rtWorkArea, 0);
		rect = rtWorkArea;
	}
}

INT CFullScreenChecker::GetWindowBorderSize(HWND hWnd, INT iIndex)
{
#ifndef SM_CXPADDEDBORDER
#define SM_CXPADDEDBORDER		92
#endif
	OSVERSIONINFO ovi = {sizeof(OSVERSIONINFO)};
	GetVersionEx(&ovi);
	// �Ƿ���vista���ϰ汾
	BOOL bIsAboveVista = (ovi.dwMajorVersion >= 6);
	// �õ����ڷ��
	DWORD dwStyle = ::GetWindowLong(hWnd, GWL_STYLE);
	// ����ǿɱ��С
	if (dwStyle & WS_THICKFRAME)
	{
		switch (iIndex)
		{
		case FCS_GWBS_XBORDER:
			return ::GetSystemMetrics(SM_CXSIZEFRAME) + ::GetSystemMetrics(SM_CXBORDER) + (bIsAboveVista ? GetSystemMetrics(SM_CXPADDEDBORDER) : 0) - ((dwStyle & WS_CAPTION) ? 1 : 2);
		case FCS_GWBS_YBORDER:
			return ::GetSystemMetrics(SM_CYSIZEFRAME) + ::GetSystemMetrics(SM_CYBORDER) + (bIsAboveVista ? GetSystemMetrics(SM_CXPADDEDBORDER) : 0) - ((dwStyle & WS_CAPTION) ? 1 : 2);
		}
	}
	// �����ϸС�б����������ǶԻ���ܱ߿��б�����
	if (dwStyle & WS_DLGFRAME)
	{
		switch (iIndex)
		{
		case FCS_GWBS_XBORDER:
			return ::GetSystemMetrics(SM_CXDLGFRAME) + ::GetSystemMetrics(SM_CXBORDER)+ (bIsAboveVista ? GetSystemMetrics(SM_CXPADDEDBORDER) : 0) - 1;
		case FCS_GWBS_YBORDER:
			return ::GetSystemMetrics(SM_CYDLGFRAME) + ::GetSystemMetrics(SM_CYBORDER)+ (bIsAboveVista ? GetSystemMetrics(SM_CXPADDEDBORDER) : 0) - 1;
		}
	}
	// �����ϸС�ޱ�����
	if (dwStyle & WS_BORDER)
	{
		return 1;
	}
	// �Ի���ܱ߿��ޱ�����
	if (dwStyle & DS_MODALFRAME)
	{
		switch (iIndex)
		{
		case FCS_GWBS_XBORDER:
			return ::GetSystemMetrics(SM_CXDLGFRAME);
		case FCS_GWBS_YBORDER:
			return ::GetSystemMetrics(SM_CYDLGFRAME);
		}
	}
	// ����Ϊ�ޱ߿�
	return 0;
}

// �����û��Ƿ���ʹ��ȫ�����
// ����Ƿ���ȫ��ģʽ��������
BOOL CFullScreenChecker::IsFullScreen()
{
	HWND hWndTop = ::GetForegroundWindow();

	CGlobal::OutputDebugString(_T("CFullScreenChecker::IsFullScreen"));

	return _SubIsFullScreen(hWndTop);
}

// ����Ƿ���ȫ��ģʽ_�ݹ��Ӻ�����������
BOOL CFullScreenChecker::_SubIsFullScreen(HWND hWnd)
{
	if (hWnd == NULL)
	{
		return FALSE;
	}

	if (!::IsWindowVisible(hWnd))
	{
		return _SubIsFullScreen(::GetParent(hWnd));
	}

	CRect rtWnd;
	GetWindowRealtimeRect(hWnd, rtWnd);

	return IsRectInRect(rtWnd, 
		CRect(0, 
		0, 
		GetSystemMetrics(SM_CXSCREEN), 
		GetSystemMetrics(SM_CYSCREEN)
		)) || _SubIsFullScreen(::GetParent(hWnd));
}

// ����Ƿ���ȫ��ģʽ��������
// �������ΪҪ������Ļ�е��Ӿ���
BOOL CFullScreenChecker::IsFullScreen(CRect rtSrcWnd)
{
	HWND hWndTop = ::GetForegroundWindow();

	CGlobal::OutputDebugString(_T("CFullScreenChecker::IsFullScreen"));

	return _SubIsFullScreen(hWndTop, rtSrcWnd);
}

// ����Ƿ���ȫ��ģʽ_�ݹ��Ӻ�����������
BOOL CFullScreenChecker::_SubIsFullScreen(HWND hWnd, CRect rtSrcWnd)
{
	if (hWnd == NULL)
	{
		return FALSE;
	}

	if (!::IsWindowVisible(hWnd))
	{
		return _SubIsFullScreen(::GetParent(hWnd), rtSrcWnd);
	}

	CRect rtWnd;
	GetWindowRealtimeRect(hWnd, rtWnd);

	CRect rtScreen(0, 
		0, 
		GetSystemMetrics(SM_CXSCREEN), 
		GetSystemMetrics(SM_CYSCREEN)
		);

	// �ҵ��Ի������ڵ���Ļ����
	UINT i;
	for (i=0; i<m_vecCRect.size(); i++)
	{
		if (IsRectInRect(rtSrcWnd, m_vecCRect[i]))
		{
			rtScreen = m_vecCRect[i];
			break;
		}
	}

	ASSERT(i == 0 || i >= m_vecCRect.size());

	return IsRectInRect(rtScreen, rtWnd) || _SubIsFullScreen(::GetParent(hWnd), rtSrcWnd);
}