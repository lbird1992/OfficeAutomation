#ifndef _WARSONG_SHARED_THREADPOOL_
#define _WARSONG_SHARED_THREADPOOL_

#include <Windows.h>
#include <process.h>

const int THREAD_SUM_MAX = 8;
const int THREAD_SUM_MIN = 8;

class ThreadPool
{
public:
  ThreadPool();
  ~ThreadPool();

  //需要线程池执行的函数需要如下定义
  //void(VOID) WINAPI FunctionName( PTP_CALLBACK_INSTANCE pInstance, PVOID pvContext);
  void RunFunction( PTP_SIMPLE_CALLBACK pFunction, PVOID pvContext);
private:
  PTP_POOL m_threadPool;
};

#endif