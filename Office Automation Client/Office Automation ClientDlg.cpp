
// Office Automation ClientDlg.cpp : 实现文件
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


// COfficeAutomationClientDlg 对话框



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


// COfficeAutomationClientDlg 消息处理程序

BOOL COfficeAutomationClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
  RakNet::SocketDescriptor sd;
  RakNet::Packet* packet;
  theApp.m_peer = RakNet::RakPeerInterface::GetInstance();
  theApp.m_peer->Startup( 1, &sd, 1);
  bool rs = (theApp.m_peer->Connect( serverIP.c_str(), serverPort, 0, 0)
    == RakNet::CONNECTION_ATTEMPT_STARTED);
  if( !rs)
  {
    MessageBox("连接服务器失败", "错误", MB_OK);
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
				MessageBox("服务器人数已满，请稍后再试", "错误", MB_OK);
        theApp.m_peer->Shutdown(300);
        CDialogEx::OnCancel();
			}
			else if(  packet->data[0] == ID_CONNECTION_ATTEMPT_FAILED)
			{
				MessageBox("连接服务器失败", "错误", MB_OK);
        theApp.m_peer->Shutdown(300);
        CDialogEx::OnCancel();
			}
      else if( packet->data[0] == ID_ALREADY_CONNECTED)
      {
        MessageBox( "已经存在到服务器的连接", "错误", MB_OK);
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
      MessageBox( "连接服务器超时", "错误", MB_OK);
      theApp.m_peer->Shutdown(300);
      CDialogEx::OnCancel();
      break;
    }
    Sleep(100);
  }

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COfficeAutomationClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR COfficeAutomationClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COfficeAutomationClientDlg::OnBnClickedOk()
{
  // TODO: 在此添加控件通知处理程序代码
}

void COfficeAutomationClientDlg::OnBnClickedLoginExit()
{
  // TODO: 在此添加控件通知处理程序代码
  theApp.m_peer->Shutdown(300);
  exit(0);
}


void COfficeAutomationClientDlg::OnBnClickedLoginLogin()
{
  // TODO: 在此添加控件通知处理程序代码
  UpdateData( true);
  RakNet::BitStream out;
  out.Write( (RakNet::MessageID)RH_LOGIN);
  out.Write( RakNet::RakString(m_name.GetBuffer()));
  out.Write( RakNet::RakString(m_password.GetBuffer()));
  theApp.m_peer->Send( &out, HIGH_PRIORITY, RELIABLE_ORDERED, 0, theApp.m_serverAddress, false);

  RakNet::Packet* packet;
  for( packet = theApp.m_peer->Receive(); !packet; packet = theApp.m_peer->Receive())
    Sleep(100);
  //返回
  if( packet->data[0] == ID_DISCONNECTION_NOTIFICATION ||
    packet->data[0] == ID_CONNECTION_LOST)
  {
    MessageBox("与服务器失去连接。", "错误", MB_OK);
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
      theApp.m_scheduleDlg.DoModal();
    }
    else if( result == LR_ERROR)
    {
      MessageBox("用户名密码错误。", "错误", MB_OK);
      theApp.m_peer->DeallocatePacket( packet);
    }
    else
    {
      MessageBox("服务器出错。", "错误", MB_OK);
      theApp.m_peer->DeallocatePacket( packet);
    }
  }
}


//void COfficeAutomationClientDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//  // TODO: 在此添加消息处理程序代码和/或调用默认值
//
//  CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}


BOOL COfficeAutomationClientDlg::PreTranslateMessage(MSG* pMsg)
{
  // TODO: 在此添加专用代码和/或调用基类
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
