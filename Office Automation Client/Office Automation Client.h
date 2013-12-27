
// Office Automation Client.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#include "stdafx.h"
#include <map>
#include <string>
using std::map;
using std::string;
using std::pair;

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "ScheduleDlg.h"

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

public:
  RakNet::RakPeerInterface* m_peer;
  RakNet::SystemAddress m_serverAddress;
  int m_ID;
  int m_department;
  int m_priority;

  map<int, string> m_departmentName;
  map<string, pair<string,int> > m_schedule;
  string m_note;

  ScheduleDlg m_scheduleDlg;

  static unsigned WINAPI NetRecieveThread( void* pOfficeAutomationClientApp);
  void Exit();
};

extern COfficeAutomationClientApp theApp;