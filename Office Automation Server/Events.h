#ifndef _EVENTS_H_
#define _EVENTS_H_

#include "ThreadPool.h"

void WINAPI OnLogin( PTP_CALLBACK_INSTANCE pInstance, void* packet);
void WINAPI OnSchedule( PTP_CALLBACK_INSTANCE pInstance, void* packet);

#endif