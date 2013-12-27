#include "Global.h"
#include "Database.h"
#include "Events.h"
#include "winsock2.h"

#pragma comment(lib,"ws2_32.lib")

GlobalData* g_globalData;

int main()
{
	/*Hui 获取当前服务器IP*/
	WSADATA wsaData; 
	char name[155]; 
	char *ip; 
	PHOSTENT hostinfo; 
	if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 ) 
	{ 
		if( gethostname ( name, sizeof(name)) == 0) 
		{ 
			if((hostinfo = gethostbyname(name)) != NULL) 
			{ 
				ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list); 
				printf("当前服务器IP:%s\n", ip); 
			} 
		} 
		WSACleanup( ); 
	}
	/*END*/

  g_globalData = new GlobalData();
  g_globalData->database = new Database();
  bool isConnect = g_globalData->database->Connect( "127.0.0.1", "root", "root", "oa", 3306, NULL);
  if( isConnect == false)
  {
    printf("连接数据库失败\n");
    system("pause");
    return 0;
  }
  printf("连接数据库成功\n");
  
  g_globalData->peer = RakNet::RakPeerInterface::GetInstance();
  RakNet::Packet* packet;
  RakNet::SocketDescriptor sd( serverPort, 0);
  g_globalData->peer->Startup( 100, &sd, 1);
  g_globalData->peer->SetMaximumIncomingConnections(100);

	printf("服务器已开启\n");

  while(1)
  {
    for( packet = g_globalData->peer->Receive(); packet; packet = g_globalData->peer->Receive())
    {
      if( packet->data[0] == ID_DISCONNECTION_NOTIFICATION || packet->data[0] == ID_CONNECTION_LOST)
      {
        printf("失去一个客户端的连接.\n");
        for( map<int,RakNet::SystemAddress>::iterator iter = g_globalData->addressMap.begin();
          iter != g_globalData->addressMap.end(); )
        {
          if( iter->second == packet->systemAddress)
          {
            char sqlCmd[1024];
            sprintf(sqlCmd, "INSERT INTO attendance SET user=%d,type=2", iter->first);
            g_globalData->databaseLock.Lock();
            g_globalData->database->QueryWithoutResult( sqlCmd);
            g_globalData->databaseLock.Unlock();
            g_globalData->addressMap.erase( iter);
            break;
          }
          else
            iter++;
        }
        g_globalData->peer->DeallocatePacket( packet);
      }
      else if( packet->data[0] == RH_LOGIN)
      {
        g_globalData->threadPool.RunFunction( OnLogin, packet);
      }
      else if( packet->data[0] == RH_SCHEDULE)
      {
        g_globalData->threadPool.RunFunction( OnSchedule, packet);
      }
      else
      {
        g_globalData->peer->DeallocatePacket( packet);
      }
    }
    Sleep(200);
  }

}