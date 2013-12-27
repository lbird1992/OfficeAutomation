//_WARSONG_GAMESHARED_THREADPOOL_
#include "ThreadPool.h"
//#include "Log.h"

ThreadPool::ThreadPool()
{
  m_threadPool = NULL;
  m_threadPool = CreateThreadpool(NULL);
  if( m_threadPool == NULL)
  {
    //Log("�̳߳ش���ʧ��.�������:13");
    exit(13);
  }
  if( SetThreadpoolThreadMinimum( m_threadPool, THREAD_SUM_MIN) == false) 
  {
    //Log("�̳߳���С�߳�������ʧ��.�������:14");
  }
  SetThreadpoolThreadMaximum( m_threadPool, THREAD_SUM_MAX);
}

ThreadPool::~ThreadPool()
{
  //CloseThreadpool( m_threadPool);
}

void ThreadPool::RunFunction( PTP_SIMPLE_CALLBACK pFunction, PVOID pvContext)
{
  TrySubmitThreadpoolCallback( pFunction, pvContext, NULL);
}