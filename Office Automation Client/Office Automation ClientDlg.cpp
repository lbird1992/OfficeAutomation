
// Office Automation ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Office Automation Client.h"
#include "Office Automation ClientDlg.h"
#include "afxdialogex.h"
#include "RakNet\BitStream.h"
#include "PacketType.h"


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
  theApp.m_peer->Shutdown(0);
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
      char tmp[256];
      sprintf( tmp, "%d", theApp.m_ID);
      MessageBox(tmp);
      theApp.m_peer->DeallocatePacket( packet);
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
