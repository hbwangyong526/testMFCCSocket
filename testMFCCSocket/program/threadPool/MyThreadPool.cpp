#include "StdAfx.h"
#include "MyThreadPool.h"

CMyThreadPool::CMyThreadPool(int nThreadCount/* =5 */)
{
	this->m_nThreadCount=nThreadCount; 
	m_bthreadflag = TRUE;
	m_hsemaphore = CreateSemaphore(NULL, 0, 5000, NULL);
	InitializeCriticalSection(&m_csThreadQueue);
	InitializeCriticalSection(&m_csTaskQueue);
	m_pThreadItemList=new std::list<ThreadItem*>;
	m_pTaskList=new std::list<CTask*>;
	EnterCriticalSection(&m_csThreadQueue);
	for (int i=0;i<m_nThreadCount;i++)
	{
		ThreadItem* pItem=new ThreadItem();
		if (pItem)
		{
			pItem->pThreadPool=this;
			pItem->bThreadFlag=TRUE;
			pItem->hThreadHandle= (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, (LPVOID)pItem, 0, &pItem->dwThreadID);
	//		printf("创建线程 threadid:%d\n",pItem->dwThreadID);
			m_pThreadItemList->push_back(pItem);
		}
	}
	LeaveCriticalSection(&m_csThreadQueue);
}

UINT WINAPI CMyThreadPool::ThreadFunc(LPVOID lpParameter /* = NULL */)
{
	//CMyThreadPool* pmyThreadPool = (CMyThreadPool*) lpParameter;
	ThreadItem *pItem = (ThreadItem*) lpParameter;
	CTask * m_pTask = NULL;
	while(pItem->bThreadFlag)
	{
		WaitForSingleObject(pItem->pThreadPool->m_hsemaphore, INFINITE);
		EnterCriticalSection(&pItem->pThreadPool->m_csTaskQueue);
		m_pTask = pItem->pThreadPool->m_pTaskList->front();
		if(m_pTask)
		{
			pItem->pThreadPool->m_pTaskList->pop_front();
		}
		LeaveCriticalSection(&pItem->pThreadPool->m_csTaskQueue);
		m_pTask->Run();
		delete m_pTask;
	}
	return NULL;
}

void CMyThreadPool::StopAllThread()
{
	EnterCriticalSection(&m_csThreadQueue);
	while (!m_pThreadItemList->empty())
	{		
		ThreadItem* pThreadItem=m_pThreadItemList->front();
		if (pThreadItem)
		{
			//TRACE("结束线程 %d\n",pThreadItem->dwThreadID);
			printf("结束线程 %d\n",pThreadItem->dwThreadID);
			pThreadItem->bThreadFlag=FALSE;
			WaitForSingleObject(pThreadItem->hThreadHandle,INFINITE);
			m_pThreadItemList->pop_front();
			delete(pThreadItem);			
		}		
	}
	LeaveCriticalSection(&m_csThreadQueue);
}


void CMyThreadPool::schedule(CTask* pTask)
{	
	EnterCriticalSection(&m_csTaskQueue);
	if (m_pTaskList)
	{
		m_pTaskList->push_back(pTask);
	}
	ReleaseSemaphore(this->m_hsemaphore,1,NULL);
	LeaveCriticalSection(&m_csTaskQueue);
}

CMyThreadPool::~CMyThreadPool()
{
	StopAllThread();
	DeleteCriticalSection(&m_csThreadQueue);
	DeleteCriticalSection(&m_csTaskQueue);
	delete m_pTaskList;
	delete m_pThreadItemList;
}
