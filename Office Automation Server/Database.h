#ifndef _WARSONG_SHARED_DATABASE_
#define _WARSONG_SHARED_DATABASE_

#include <Windows.h>
#include <queue>
#include <string>
#include <stdint.h>
#include <mysql.h>
//#include "ThreadLock.h"

class Database
{
public:
  Database();
  ~Database();

  bool Connect( const char* host, const char* username, const char* password, 
                const char* dbname, unsigned port, const char* socket);
  void Close();

  uint64_t QueryWithResult( const char* sql);//同步有结果查询 返回结果行数
  bool QueryWithoutResult( const char* sql);//同步无结果查询，返回是否执行成功
  void QueryWithoutResultAsync( const char* sql);//异步无结果查询
  void FreeResult();

  static unsigned WINAPI _AsyncThread( void* pDatabase);

  void FetchRow();//将光标推进到下一行
  int GetResultInt( int col);
  float GetResultFloat( int col);
  char* GetResult( int col);

private:
  MYSQL m_mysqlHandle;
  MYSQL_RES* m_result;//结果集
  MYSQL_ROW m_row;
  std::queue< std::string> m_queryQueue;
  //ThreadLock m_queryQueueLock;
};

#endif