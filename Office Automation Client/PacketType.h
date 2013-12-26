#pragma once

#include <string>
#include "RakNet\MessageIdentifiers.h"
#include "RakNet\RakNetTypes.h"
using std::string;

//const string serverIP = "192.168.1.103";
const string serverIP = "127.0.0.1";
const int serverPort = 35000;

enum RakNetHead
{
  RH_LOGIN = ID_USER_PACKET_ENUM + 1, //登录
};

//RH_LOGIN RESULT
const int LR_SUCCESS = 1;
const int LR_ERROR = 2;//用户名密码错误
const int LR_FAIL = 3;//服务器出错