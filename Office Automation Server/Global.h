#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <map>
#include "RakNet\RakPeerInterface.h"
#include "PacketType.h"
#include "Database.h"
#include "ThreadPool.h"
using std::map;

struct GlobalData
{
  RakNet::RakPeerInterface* peer;
  Database* database;
  ThreadLock databaseLock;
  map<int, RakNet::SystemAddress> addressMap;
  ThreadPool threadPool;
};

extern GlobalData* g_globalData;

#endif