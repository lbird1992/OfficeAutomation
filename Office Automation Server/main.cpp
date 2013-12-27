#include "Global.h"
#include "Database.h"
#include "Events.h"

GlobalData* g_globalData;

int main()
{
  system("ipconfig");
  g_globalData = new GlobalData();
  g_globalData->database = new Database();
  bool isConnect = g_globalData->database->Connect( "127.0.0.1", "root", "root", "oa", 3306, NULL);
  if( isConnect == false)
  {
    printf("�������ݿ�ʧ��\n");
    system("pause");
    return 0;
  }
  printf("�������ݿ�ɹ�\n");
  
  g_globalData->peer = RakNet::RakPeerInterface::GetInstance();
  RakNet::Packet* packet;
  RakNet::SocketDescriptor sd( serverPort, 0);
  g_globalData->peer->Startup( 100, &sd, 1);
  g_globalData->peer->SetMaximumIncomingConnections(100);

  while(1)
  {
    for( packet = g_globalData->peer->Receive(); packet; packet = g_globalData->peer->Receive())
    {
      if( packet->data[0] == ID_NEW_INCOMING_CONNECTION)
      {
        printf("�����µ�����.\n");
        g_globalData->peer->DeallocatePacket( packet);
      }
      else if( packet->data[0] == ID_DISCONNECTION_NOTIFICATION || packet->data[0] == ID_CONNECTION_LOST)
      {
        printf("ʧȥһ���ͻ��˵�����.\n");
        g_globalData->peer->DeallocatePacket( packet);
      }
      else if( packet->data[0] == RH_LOGIN)
      {
        g_globalData->threadPool.RunFunction( OnLogin, packet);
      }
    }
    Sleep(200);
  }

}