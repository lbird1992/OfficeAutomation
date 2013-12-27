//_WARSONG_GAMESHARED_DATABASE_
#include <stdlib.h>
#include <process.h>
#include "Database.h"
//#include "Log.h"

Database::Database()
{
  m_result = NULL;
  mysql_init( &m_mysqlHandle);

  //设置超时
  unsigned timeout = 5*60;
  mysql_options( &m_mysqlHandle, MYSQL_OPT_CONNECT_TIMEOUT, (char*)&timeout);
  //启动再连接
  my_bool reconnect = TRUE;
  mysql_options( &m_mysqlHandle, MYSQL_OPT_RECONNECT, (char*)&reconnect);

  mysql_options( &m_mysqlHandle, MYSQL_SET_CHARSET_NAME, "gb2312"); 

}

Database::~Database()
{
  Close();
}

bool Database::Connect( const char* host, const char* username, const char* password,
                       const char* dbname, unsigned port, const char* socket)
{
  if( mysql_real_connect( &m_mysqlHandle, host, username, password, dbname, port, socket, 0) == NULL )
  {
    //Log("无法连接到MYSQL服务器。错误代码:12");
    return false;
  }

  //设置允许多语句支持
  mysql_set_server_option( &m_mysqlHandle, MYSQL_OPTION_MULTI_STATEMENTS_ON);

  unsigned asyncThread;
  _beginthreadex( NULL, 0, _AsyncThread, this, 0, &asyncThread);

  return true;
}

void Database::Close()
{
  FreeResult();
  mysql_close(&m_mysqlHandle);
}

uint64_t Database::QueryWithResult( const char* sql)
{
  FreeResult();
  mysql_query( &m_mysqlHandle, sql);
  m_result = mysql_store_result( &m_mysqlHandle);
  if( m_result == NULL)
    return 0;
  else
    return mysql_num_rows( m_result);
}

bool Database::QueryWithoutResult( const char* sql)
{
  if( mysql_query( &m_mysqlHandle, sql) == 0)
    return true;
  else
    return false;
}

void Database::QueryWithoutResultAsync( const char* sql)
{
  m_queryQueueLock.Lock();
  m_queryQueue.push( sql);
  m_queryQueueLock.Unlock();
}

void Database::FreeResult()
{
  if( m_result != NULL)
    mysql_free_result( m_result);
  m_result = NULL;
}

void Database::FetchRow()
{
  m_row = mysql_fetch_row( m_result);
}

int Database::GetResultInt( int col)
{
  if( m_row == NULL)
    return 0;
  else
    return atoi( m_row[col]);
}

float Database::GetResultFloat( int col)
{
  if( m_row == NULL)
    return 0;
  else
    return atof( m_row[col]);
}

char* Database::GetResult( int col)
{
  return m_row[col];
}

unsigned WINAPI Database::_AsyncThread( void* pDatabase)
{
  Database* database = (Database*)pDatabase;
  std::string sql;
  while(1)
  {
    while( database->m_queryQueue.empty())
    {
      Sleep(1000);
    }
    database->m_queryQueueLock.Lock();
    sql = database->m_queryQueue.front();
    database->m_queryQueue.pop();
    database->m_queryQueueLock.Unlock();
    mysql_query( &database->m_mysqlHandle, sql.c_str());
  }
}