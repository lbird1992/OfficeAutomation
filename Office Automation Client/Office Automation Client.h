
// Office Automation Client.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#include "stdafx.h"

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// COfficeAutomationClientApp:
// �йش����ʵ�֣������ Office Automation Client.cpp
//

class COfficeAutomationClientApp : public CWinApp
{
public:
	COfficeAutomationClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

  RakNet::RakPeerInterface* m_peer;
  RakNet::SystemAddress m_serverAddress;

  static unsigned WINAPI NetRecieveThread( void* pOfficeAutomationClientApp);
  void Exit();
};

extern COfficeAutomationClientApp theApp;