
// Office Automation Client.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Office Automation Client.h"
#include "Office Automation ClientDlg.h"
#include "PacketType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COfficeAutomationClientApp

BEGIN_MESSAGE_MAP(COfficeAutomationClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// COfficeAutomationClientApp ����

COfficeAutomationClientApp::COfficeAutomationClientApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
  RakNet::SocketDescriptor sd;
  RakNet::Packet* packet;
  m_peer = RakNet::RakPeerInterface::GetInstance();
  m_peer->Startup( 1, &sd, 1);
  bool rs = (m_peer->Connect( serverIP.c_str(), serverPort, 0, 0)
    == RakNet::CONNECTION_ATTEMPT_STARTED);
  if( !rs)
  {
    MessageBox( NULL, "���ӷ�����ʧ��", "����", MB_OK);
    exit(0);
  }

  int isConn = 0;
	while(1)
  {
    packet = m_peer->Receive();
    if( packet)
    {
      if( packet->data[0] == ID_CONNECTION_REQUEST_ACCEPTED)
      {
        m_serverAddress = packet->systemAddress;
        m_peer->DeallocatePacket( packet);
        break;
      }
      else
        m_peer->DeallocatePacket( packet);
    }
    else
      ++isConn;
    if( isConn >= 5)
    {
      MessageBox( NULL, "���ӷ�������ʱ", "����", MB_OK);
      exit(0);
    }
    Sleep(300);
  }

  _beginthreadex( NULL, 0, NetRecieveThread, this, 0, NULL);
}


// Ψһ��һ�� COfficeAutomationClientApp ����

COfficeAutomationClientApp theApp;


// COfficeAutomationClientApp ��ʼ��

BOOL COfficeAutomationClientApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	COfficeAutomationClientDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

void COfficeAutomationClientApp::Exit()
{
  exit(0);
}
