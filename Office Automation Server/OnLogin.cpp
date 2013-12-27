#include "RakNet\BitStream.h"
#include "Events.h"
#include "Global.h"

void WINAPI OnLogin( PTP_CALLBACK_INSTANCE pInstance, void* packet)
{
  RakNet::Packet* pIn = (RakNet::Packet*)packet;
  RakNet::BitStream bsIn(pIn->data, pIn->length, false);
  RakNet::RakString username, password;
  bsIn.IgnoreBytes( sizeof(RakNet::MessageID));
  bsIn.Read( username);
  bsIn.Read( password);
  int ID;
  char sqlCmd[1024];
  sprintf( sqlCmd, "SELECT id,department,priority FROM account WHERE name='%s' AND password='%s'", username.C_String(), password.C_String());
  g_globalData->databaseLock.Lock();
  int count = g_globalData->database->QueryWithResult(sqlCmd);
  RakNet::BitStream bsOut;
  bsOut.Write( (RakNet::MessageID)RH_LOGIN);
  if( count == 0)
  {
    bsOut.Write( LR_ERROR);
    printf("%s登录失败\n", username.C_String());
  }
  else
  {
    g_globalData->database->FetchRow();
    bsOut.Write( LR_SUCCESS);
    ID = g_globalData->database->GetResultInt(0);
    bsOut.Write( ID);
    bsOut.Write( g_globalData->database->GetResultInt(1));//department
    bsOut.Write( g_globalData->database->GetResultInt(2));//priority
    printf("%s登录成功.\n", username.C_String());
    g_globalData->addressMap[ID] = pIn->systemAddress;
  }
  g_globalData->database->FreeResult();
  g_globalData->databaseLock.Unlock();
  g_globalData->peer->Send( &bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, pIn->systemAddress, false);
  g_globalData->peer->DeallocatePacket( pIn);

  if( count != 0)
  {
    //写入上班时间
    g_globalData->databaseLock.Lock();
    sprintf( sqlCmd, "INSERT INTO attendance SET user=%d,type=1", ID);
    g_globalData->database->QueryWithoutResult( sqlCmd);
    g_globalData->databaseLock.Unlock();

    //发送各部门名称
    sprintf( sqlCmd, "SELECT ID,department_name FROM department");
    g_globalData->databaseLock.Lock();
    count = g_globalData->database->QueryWithResult( sqlCmd);
    RakNet::BitStream departmentInformation;
    departmentInformation.Write( (RakNet::MessageID)RH_DEPARTMENT_INFORMATION);
    departmentInformation.Write( count);
    for( int i=0; i<count; i++)
    {
      g_globalData->database->FetchRow();
      departmentInformation.Write( g_globalData->database->GetResultInt(0));//department_id
      RakNet::RakString departmentName( g_globalData->database->GetResult(1));
      departmentInformation.Write( departmentName);
    }
    g_globalData->peer->Send( &departmentInformation, HIGH_PRIORITY, RELIABLE_ORDERED, 0, pIn->systemAddress, false);
    g_globalData->database->FreeResult();
    g_globalData->databaseLock.Unlock();

    //发送时间安排
    sprintf( sqlCmd, "SELECT time,intent,ID FROM schedule WHERE user_id=%d AND isDone=0", ID);
    g_globalData->databaseLock.Lock();
    count = g_globalData->database->QueryWithResult( sqlCmd);
    RakNet::BitStream schedule;
    schedule.Write( (RakNet::MessageID)RH_SCHEDULE);
    schedule.Write( SO_NEW);
    schedule.Write( count);
    for( int i=0; i<count; i++)
    {
      g_globalData->database->FetchRow();
      schedule.Write( g_globalData->database->GetResultInt(2));//ID
      RakNet::RakString time( g_globalData->database->GetResult(0));
      RakNet::RakString intent( g_globalData->database->GetResult(1));
      schedule.Write( time);
      schedule.Write( intent);
    }
    g_globalData->peer->Send( &schedule, HIGH_PRIORITY, RELIABLE_ORDERED, 0, pIn->systemAddress, false);
    g_globalData->database->FreeResult();
    g_globalData->databaseLock.Unlock();
  }
}