#pragma once

#include <string>
#include "RakNet\MessageIdentifiers.h"
#include "RakNet\RakNetTypes.h"
using std::string;

const string serverIP = "192.168.1.102";
const int serverPort = 35000;

enum RakNetHead
{
  RH_LOGIN = ID_USER_PACKET_ENUM + 1, //��¼
  RH_DEPARTMENT_INFORMATION, //�ɷ�������ͻ��˴��Ͳ�����Ϣ  RH + SUM(INT) + [ ID(INT) + NAME(STRING)]
  RH_SCHEDULE,
  
};

//RH_LOGIN RESULT
const int LR_SUCCESS = 1;
const int LR_ERROR = 2;//�û����������
const int LR_FAIL = 3;//����������

//RH_SCHEDULE option
const int SO_FIRST = 1;//��¼ʱ��ͻ��˴���ʱ��� + SUM(INT) + [ TIME + INTENT]
const int SO_NEW = 2;//�¼���ʱ��� USERID(INT) + TIME + INTENT
const int SO_DONE = 3;//ʱ������ + ID