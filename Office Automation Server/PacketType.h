#pragma once

#include <string>
#include "RakNet\MessageIdentifiers.h"
#include "RakNet\RakNetTypes.h"
using std::string;

const string serverIP = "192.168.1.102";
const int serverPort = 35000;

enum RakNetHead
{
  RH_LOGIN = ID_USER_PACKET_ENUM + 1, //登录
  RH_DEPARTMENT_INFORMATION, //由服务器向客户端传送部门信息  RH + SUM(INT) + [ ID(INT) + NAME(STRING)]
  RH_SCHEDULE,
  
};

//RH_LOGIN RESULT
const int LR_SUCCESS = 1;
const int LR_ERROR = 2;//用户名密码错误
const int LR_FAIL = 3;//服务器出错

//RH_SCHEDULE option
const int SO_FIRST = 1;//登录时向客户端传送时间表 + SUM(INT) + [ TIME + INTENT]
const int SO_NEW = 2;//新加入时间表 USERID(INT) + TIME + INTENT
const int SO_DONE = 3;//时间表过期 + ID