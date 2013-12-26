#include "RakNet\BitStream.h"
#include "Events.h"
#include "Global.h"

void OnLogin( void* packet)
{
  RakNet::Packet* pIn = (RakNet::Packet*)packet;
  RakNet::BitStream bsIn(pIn->data, pIn->length, false);
  RakNet::RakString username, password;
  bsIn.IgnoreBytes( sizeof(RakNet::MessageID));
  bsIn.Read( username);
  bsIn.Read( password);
  char sqlCmd[1024];
  sprintf( sqlCmd, "SELECT id,department,priority FROM account WHERE name='%s' AND password='%s'", username.C_String(), password.C_String());
  int count = g_globalData->database->QueryWithResult(sqlCmd);
  RakNet::BitStream bsOut;
  bsOut.Write( (RakNet::MessageID)RH_LOGIN);
  if( count == 0)
  {
    bsOut.Write( LR_ERROR);
    printf("%sµÇÂ¼Ê§°Ü\n", username.C_String());
  }
  else
  {
    g_globalData->database->FetchRow();
    bsOut.Write( LR_SUCCESS);
    bsOut.Write( g_globalData->database->GetResultInt(0));
    bsOut.Write( g_globalData->database->GetResultInt(1));
    bsOut.Write( g_globalData->database->GetResultInt(2));
    printf("%sµÇÂ¼³É¹¦.\n", username.C_String());
  }
  g_globalData->peer->Send( &bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, pIn->systemAddress, false);
  g_globalData->peer->DeallocatePacket( pIn);
}