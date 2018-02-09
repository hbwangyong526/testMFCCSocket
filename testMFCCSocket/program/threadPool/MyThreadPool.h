#pragma once
#include "MyTask.h"
#include <list>
#include <process.h>
class CMyThreadPool;
struct ThreadItem
{
	HANDLE hThreadHandle;       //线程句柄
	UINT  dwThreadID;          //线程ID
	BOOL   bThreadFlag;         //线程运行标识
	CMyThreadPool* pThreadPool;   //属于哪个线程池
	ThreadItem()
	{
		hThreadHandle=NULL;
		dwThreadID=0;
		bThreadFlag=FALSE;
		pThreadPool=NULL;
	}
};

class CMyThreadPool
{
public:
	//CMyThreadPool();
	CMyThreadPool(int nThreadCount=5);
	virtual ~CMyThreadPool();
	static UINT WINAPI ThreadFunc(LPVOID lpParameter = NULL);
public:
	void schedule(CTask* pTask);
	std::list<ThreadItem*>* GetThreadItemList() {return m_pThreadItemList;};
	std::list<CTask*>*      GetTaskList() {return m_pTaskList;};
	void               StopAllThread();
	void               AdjustSize(int nThreadCount);  //动态调整线程池规模
protected:
	//static 
private:
	BOOL m_bthreadflag;   
	int m_nThreadCount;    //线程池中线程的个数
	HANDLE m_hsemaphore;
	std::list<ThreadItem*>*  m_pThreadItemList;
	std::list<CTask*>*       m_pTaskList;
	CRITICAL_SECTION    m_csThreadQueue;
	CRITICAL_SECTION    m_csTaskQueue;

	//Schedule 函数定义

public:
	template<typename ReturnType>
	void schedule(ReturnType Func())
	{
		CTask * pTask = new CMyTask<ReturnType>(Func);
		EnterCriticalSection(&m_csTaskQueue);
		if (m_pTaskList)
		{
			m_pTaskList->push_back(pTask);
		}
		ReleaseSemaphore(this->m_hsemaphore,1,NULL);
		LeaveCriticalSection(&m_csTaskQueue);
	}
public:
	template <typename ReturnType, typename P0>
	void schedule(ReturnType Func(P0 p0),P0 p0)
	{
		CTask * pTask = new CMyTask<ReturnType,P0>(Func, p0);
		EnterCriticalSection(&m_csTaskQueue);
		if (m_pTaskList)
		{
			m_pTaskList->push_back(pTask);
		}
		ReleaseSemaphore(this->m_hsemaphore,1,NULL);
		LeaveCriticalSection(&m_csTaskQueue);
	}
	template <typename ReturnType, typename P0, typename P1>
	void schedule(ReturnType Func(P0 p0, P1 p1),P0 p0, P1 p1) 
	{
		CTask * pTask = new CMyTask<ReturnType,P0,P1>(Func, p0, p1);
		EnterCriticalSection(&m_csTaskQueue);
		if (m_pTaskList)
		{
			m_pTaskList->push_back(pTask);                        
		}
		ReleaseSemaphore(this->m_hsemaphore,1,NULL); 
		LeaveCriticalSection(&m_csTaskQueue);
	}
	template <typename ReturnType, typename P0, typename P1,typename P2>
	void schedule(ReturnType Func(P0 p0, P1 p1, P2 p2),P0 p0, P1 p1, P2 p2)
	{
		CTask * pTask = new CMyTask<ReturnType,P0,P1,P2>(Func, p0, p1, p2);
		EnterCriticalSection(&m_csTaskQueue);
		if (m_pTaskList)
		{
			m_pTaskList->push_back(pTask);
		}
		ReleaseSemaphore(this->m_hsemaphore,1,NULL);
		LeaveCriticalSection(&m_csTaskQueue);
	}
	template <typename ReturnType, typename P0, typename P1,typename P2, typename P3>
	void schedule(ReturnType Func(P0 p0, P1 p1, P2 p2, P3 p3),P0 p0, P1 p1, P2 p2, P3 p3)
	{
		CTask * pTask = new CMyTask<ReturnType,P0,P1,P2,P3>(Func, p0, p1, p2, p3);
		EnterCriticalSection(&m_csTaskQueue);
		if (m_pTaskList)
		{
			m_pTaskList->push_back(pTask);
		}
		ReleaseSemaphore(this->m_hsemaphore,1,NULL);
		LeaveCriticalSection(&m_csTaskQueue);
	}
	template <typename ReturnType, typename P0, typename P1,typename P2, typename P3\
	,typename P4>
	void schedule(ReturnType Func(P0 p0, P1 p1, P2 p2, P3 p3,P4 p4)\
	,P0 p0, P1 p1, P2 p2, P3 p3,P4 p4)
	{
		CTask * pTask = new CMyTask<ReturnType,P0,P1,P2,P3,P4>(Func, p0, p1, p2, p3, p4);
		EnterCriticalSection(&m_csTaskQueue);
		if (m_pTaskList)
		{
			m_pTaskList->push_back(pTask);
		}
		ReleaseSemaphore(this->m_hsemaphore,1,NULL);
		LeaveCriticalSection(&m_csTaskQueue);
	}
	template <typename ReturnType, typename P0, typename P1,typename P2, typename P3\
		,typename P4, typename P5>
	void schedule(ReturnType Func(P0 p0, P1 p1, P2 p2, P3 p3,P4 p4, P5 p5)\
	,P0 p0, P1 p1, P2 p2, P3 p3,P4 p4, P5 p5)
	{
		CTask * pTask = new CMyTask<ReturnType,P0,P1,P2,P3,P4,P5>(Func, p0, p1, p2, p3, p4, p5);
		EnterCriticalSection(&m_csTaskQueue);
		if (m_pTaskList)
		{
			m_pTaskList->push_back(pTask);
		}
		ReleaseSemaphore(this->m_hsemaphore,1,NULL);
		LeaveCriticalSection(&m_csTaskQueue);
	}
	template <typename ReturnType, typename P0, typename P1,typename P2, typename P3\
	,typename P4, typename P5, typename P6>
	void schedule(ReturnType Func(P0 p0, P1 p1, P2 p2, P3 p3,P4 p4, P5 p5, P6 p6),\
	P0 p0, P1 p1, P2 p2, P3 p3,P4 p4, P5 p5, P6 p6)
	{
		CTask * pTask = new CMyTask<ReturnType,P0,P1,P2,P3,P4,P5,P6>(Func, p0, p1, p2, p3, p4, p5, p6);
		EnterCriticalSection(&m_csTaskQueue);
		if (m_pTaskList)
		{
			m_pTaskList->push_back(pTask);
		}
		ReleaseSemaphore(this->m_hsemaphore,1,NULL);
		LeaveCriticalSection(&m_csTaskQueue);
	}
	template <typename ReturnType, typename P0, typename P1,typename P2, typename P3\
	,typename P4, typename P5, typename P6,typename P7>
	void schedule(ReturnType Func(P0 p0, P1 p1, P2 p2, P3 p3,P4 p4, P5 p5, P6 p6, P7 p7),\
	P0 p0, P1 p1, P2 p2, P3 p3,P4 p4, P5 p5, P6 p6, P7 p7)
	{
		CTask * pTask = new CMyTask<ReturnType,P0,P1,P2,P3,P4,P5,P6,P7>(Func, p0, p1, p2, p3, p4, p5, p6,p7);
		EnterCriticalSection(&m_csTaskQueue);
		if (m_pTaskList)
		{
			m_pTaskList->push_back(pTask);
		}
		ReleaseSemaphore(this->m_hsemaphore,1,NULL);
		LeaveCriticalSection(&m_csTaskQueue);
	}
};

