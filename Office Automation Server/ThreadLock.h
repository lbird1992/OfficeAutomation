#ifndef _WARSONG_SHARED_THREADLOCK_
#define _WARSONG_SHARED_THREADLOCK_

#include <Windows.h>

class ThreadLock
{
public:
  ThreadLock();
  ~ThreadLock();
  void Lock();
  void Unlock();
  bool IsLock();
private:
  CRITICAL_SECTION m_lock;
  bool m_isLock;
};

class ReadWriteLock
{
public:
  ReadWriteLock();
  ~ReadWriteLock();
  void ReadLock();
  void ReadUnlock();
  void WriteLock();
  void WriteUnlock();
private:
  SRWLOCK m_lock;
};

#endif