#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "RakNet\RakPeerInterface.h"
#include "PacketType.h"
#include "Database.h"

struct GlobalData
{
  RakNet::RakPeerInterface* peer;
  Database* database;
};

extern GlobalData* g_globalData;

#endif