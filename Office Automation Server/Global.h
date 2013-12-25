#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "RakNet\RakPeerInterface.h"
#include "PacketType.h"

struct GlobalData
{
  RakNet::RakPeerInterface* peer;
};

extern GlobalData* g_globalData;

#endif