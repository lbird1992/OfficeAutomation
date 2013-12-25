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

  uint64_t QueryWithResult( const char* sql);//ͬ���н����ѯ ���ؽ������
  bool QueryWithoutResult( const char* sql);//ͬ���޽����ѯ�������Ƿ�ִ�гɹ�
  void QueryWithoutResultAsync( const char* sql);//�첽�޽����ѯ
  void FreeResult();

  static unsigned WINAPI _AsyncThread( void* pDatabase);

  void FetchRow();//������ƽ�����һ��
  int GetResultInt( int col);
  float GetResultFloat( int col);
  char* GetResult( int col);

private:
  MYSQL m_mysqlHandle;
  MYSQL_RES* m_result;//�����
  MYSQL_ROW m_row;
  std::queue< std::string> m_queryQueue;
  //ThreadLock m_queryQueueLock;
};

#endif