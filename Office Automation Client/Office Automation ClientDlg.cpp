
// Office Automation ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Office Automation Client.h"
#include "Office Automation ClientDlg.h"
#include "afxdialogex.h"
#include "RakNet\BitStream.h"
#include "PacketType.h"
#include "ScheduleDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COfficeAutomationClientDlg �Ի���



COfficeAutomationClientDlg::COfficeAutomationClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COfficeAutomationClientDlg::IDD, pParent)
  , m_name(_T(""))
  , m_password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COfficeAutomationClientDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  //  DDX_Text(pDX, IDC_LOGIN_EDTPASSWORD, password);
  //  DDV_MaxChars(pDX, password, 20);
  DDX_Text(pDX, IDC_LOGIN_NAME, m_name);
  DDX_Text(pDX, IDC_LOGIN_EDTPASSWORD, m_password);
	DDV_MaxChars(pDX, m_password, 20);
}

BEGIN_MESSAGE_MAP(COfficeAutomationClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDOK, &COfficeAutomationClientDlg::OnBnClickedOk)
  ON_BN_CLICKED(IDC_LOGIN_EXIT, &COfficeAutomationClientDlg::OnBnClickedLoginExit)
  ON_BN_CLICKED(IDC_LOGIN_LOGIN, &COfficeAutomationClientDlg::OnBnClickedLoginLogin)
//  ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// COfficeAutomationClientDlg ��Ϣ�������

BOOL COfficeAutomationClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
  RakNet::SocketDescriptor sd;
  RakNet::Packet* packet;
  theApp.m_peer = RakNet::RakPeerInterface::GetInstance();
  theApp.m_peer->Startup( 1, &sd, 1);
  bool rs = (theApp.m_peer->Connect( serverIP.c_str(), serverPort, 0, 0)
    == RakNet::CONNECTION_ATTEMPT_STARTED);
  if( !rs)
  {
    MessageBox("���ӷ�����ʧ��", "����", MB_OK);
    RakNet::RakPeerInterface::DestroyInstance( theApp.m_peer);
    CDialogEx::OnCancel();
  }

  int isConn = 0;
	while(1)
  {
    packet = theApp.m_peer->Receive();
    if( packet)
    {
      if( packet->data[0] == ID_CONNECTION_REQUEST_ACCEPTED)
      {
        theApp.m_serverAddress = packet->systemAddress;
        theApp.m_peer->DeallocatePacket( packet);
        break;
      }
      else if( packet->data[0] == ID_NO_FREE_INCOMING_CONNECTIONS)
			{
				MessageBox("�������������������Ժ�����", "����", MB_OK);
        theApp.m_peer->Shutdown(300);
        CDialogEx::OnCancel();
			}
			else if(  packet->data[0] == ID_CONNECTION_ATTEMPT_FAILED)
			{
				MessageBox("���ӷ�����ʧ��", "����", MB_OK);
        theApp.m_peer->Shutdown(300);
        CDialogEx::OnCancel();
			}
      else if( packet->data[0] == ID_ALREADY_CONNECTED)
      {
        MessageBox( "�Ѿ����ڵ�������������", "����", MB_OK);
        theApp.m_peer->Shutdown(300);
        CDialogEx::OnCancel();
      }
      else
        theApp.m_peer->DeallocatePacket( packet);
    }
    else
      ++isConn;
    if( isConn >= 35)
    {
      MessageBox( "���ӷ�������ʱ", "����", MB_OK);
      theApp.m_peer->Shutdown(300);
      CDialogEx::OnCancel();
      break;
    }
    Sleep(100);
  }

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COfficeAutomationClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR COfficeAutomationClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COfficeAutomationClientDlg::OnBnClickedOk()
{
  // TODO: �ڴ���ӿؼ�֪ͨ����������
}

void COfficeAutomationClientDlg::OnBnClickedLoginExit()
{
  // TODO: �ڴ���ӿؼ�֪ͨ����������
  theApp.m_peer->Shutdown(300);
  exit(0);
}


void COfficeAutomationClientDlg::OnBnClickedLoginLogin()
{
  // TODO: �ڴ���ӿؼ�֪ͨ����������
  UpdateData( true);
  RakNet::BitStream out;
  out.Write( (RakNet::MessageID)RH_LOGIN);
  out.Write( RakNet::RakString(m_name.GetBuffer()));
  out.Write( RakNet::RakString(m_password.GetBuffer()));
  theApp.m_peer->Send( &out, HIGH_PRIORITY, RELIABLE_ORDERED, 0, theApp.m_serverAddress, false);

  RakNet::Packet* packet;
  for( packet = theApp.m_peer->Receive(); !packet; packet = theApp.m_peer->Receive())
    Sleep(100);
  //����
  if( packet->data[0] == ID_DISCONNECTION_NOTIFICATION ||
    packet->data[0] == ID_CONNECTION_LOST)
  {
    MessageBox("�������ʧȥ���ӡ�", "����", MB_OK);
    exit(0);
  }
  if( packet->data[0] == RH_LOGIN)
  {
    RakNet::BitStream bsIn( packet->data, packet->length, false);
    bsIn.IgnoreBytes( sizeof(RakNet::MessageID));
    int result;
    bsIn.Read( result);
    if( result == LR_SUCCESS)
    {
      bsIn.Read( theApp.m_ID);
      bsIn.Read( theApp.m_department);
      bsIn.Read( theApp.m_priority);
      theApp.m_peer->DeallocatePacket( packet);
      _beginthreadex( NULL, 0, COfficeAutomationClientApp::NetRecieveThread, &theApp, 0, NULL);
      CDialogEx::OnOK();
      ScheduleDlg scheduleDlg;
      scheduleDlg.DoModal();
    }
    else if( result == LR_ERROR)
    {
      MessageBox("�û����������", "����", MB_OK);
      theApp.m_peer->DeallocatePacket( packet);
    }
    else
    {
      MessageBox("����������", "����", MB_OK);
      theApp.m_peer->DeallocatePacket( packet);
    }
  }
}


//void COfficeAutomationClientDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//  // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//  CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}


BOOL COfficeAutomationClientDlg::PreTranslateMessage(MSG* pMsg)
{
  // TODO: �ڴ����ר�ô����/����û���
  if( pMsg->message == WM_KEYDOWN)
  {
    if( pMsg->wParam == VK_RETURN)
    {
      OnBnClickedLoginLogin();
      return TRUE;
    }
  }

  return CDialogEx::PreTranslateMessage(pMsg);
}
