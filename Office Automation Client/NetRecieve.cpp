#include "stdafx.h"
#include "Office Automation Client.h"

unsigned WINAPI COfficeAutomationClientApp::NetRecieveThread( void* pOfficeAutomationClientApp)
{
  COfficeAutomationClientApp* app = (COfficeAutomationClientApp*)pOfficeAutomationClientApp;

  RakNet::Packet* packet;

  while(1)
  {
    for( packet = app->m_peer->Receive(); !packet; packet = app->m_peer->Receive() )
      Sleep(200);

    if( packet->data[0] == ID_CONNECTION_LOST || packet->data[0] == ID_DISCONNECTION_NOTIFICATION)
    {
      MessageBox( NULL, "与服务器失去连接", "错误", MB_OK);
      app->Exit();
    }
    //else if(...)

    app->m_peer->DeallocatePacket( packet);
  }

  return 0;
}