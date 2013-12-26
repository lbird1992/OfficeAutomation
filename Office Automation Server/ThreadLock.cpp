//_WARSONG_GAMESHARED_THREADLOCK_
#include "ThreadLock.h"

ThreadLock::ThreadLock()
{
  InitializeCriticalSection( &m_lock);
  m_isLock = false;
}

ThreadLock::~ThreadLock()
{
  DeleteCriticalSection( &m_lock);
}

void ThreadLock::Lock()
{
  EnterCriticalSection( &m_lock);
  m_isLock = true;
}

void ThreadLock::Unlock()
{
  LeaveCriticalSection( &m_lock);
  m_isLock = false;
}

bool ThreadLock::IsLock()
{
  return m_isLock;
}

ReadWriteLock::ReadWriteLock()
{
  InitializeSRWLock( &m_lock);
}

ReadWriteLock::~ReadWriteLock()
{
}

void ReadWriteLock::ReadLock()
{
  AcquireSRWLockShared( &m_lock);
}

void ReadWriteLock::ReadUnlock()
{
  ReleaseSRWLockShared( &m_lock);
}

void ReadWriteLock::WriteLock()
{
  AcquireSRWLockExclusive( &m_lock);
}

void ReadWriteLock::WriteUnlock()
{
  ReleaseSRWLockExclusive( &m_lock);
}