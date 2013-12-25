
// Office Automation Client.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#include "stdafx.h"

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// COfficeAutomationClientApp:
// 有关此类的实现，请参阅 Office Automation Client.cpp
//

class COfficeAutomationClientApp : public CWinApp
{
public:
	COfficeAutomationClientApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()

  RakNet::RakPeerInterface* m_peer;
  RakNet::SystemAddress m_serverAddress;

  static unsigned WINAPI NetRecieveThread( void* pOfficeAutomationClientApp);
  void Exit();
};

extern COfficeAutomationClientApp theApp;