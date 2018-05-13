// Thread.h: interface for the CThread class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __MG_THREAD_H__
#define __MG_THREAD_H__

class CThread
{
public:
	CThread();
	virtual ~CThread();

public:
	bool StartThread(void);
	void WaitForStop(void);

	static DWORD WINAPI InitThreadProc(PVOID pObj)
	{
		return	((CThread *)pObj)->ThreadProc();
	}
	
	unsigned long ThreadProc(void);

protected:
	virtual void ThreadProcMain(void) = 0;

protected:
	DWORD	m_dwThreadID;		// �̱߳�ʶ
	HANDLE	m_hThread;			// �߳̾��
	HANDLE	m_evStop;
};

#endif
