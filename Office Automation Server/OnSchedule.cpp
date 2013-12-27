#include "RakNet\BitStream.h"
#include "Global.h"
#include "Events.h"

void WINAPI OnSchedule( PTP_CALLBACK_INSTANCE pInstance, void* packet)
{
  RakNet::Packet* pIn = (RakNet::Packet*)packet;
  RakNet::BitStream bsIn(pIn->data, pIn->length, false);
  bsIn.IgnoreBytes( sizeof(RakNet::MessageID));
  int option;
  bsIn.Read( option);
  if( option == SO_DONE)
  {
    int ID;
    bsIn.Read(ID);
    char sqlCmd[1024];
    sprintf( sqlCmd, "UPDATE schedule SET isDone=1 WHERE id=%d", ID);
    g_globalData->databaseLock.Lock();
    g_globalData->database->QueryWithoutResult(sqlCmd);
    g_globalData->databaseLock.Unlock();
  }
  g_globalData->peer->DeallocatePacket( pIn);
}