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

  //system("ipconfig");
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
      if( packet->data[0] == RH_LOGIN)
        OnLogin(packet);
    }
    Sleep(200);
  }

}