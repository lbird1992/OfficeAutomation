// ScheduleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Office Automation Client.h"
#include "ScheduleDlg.h"
#include "afxdialogex.h"
#include "PacketType.h"
#include "AddWorkDlg.h"

// ScheduleDlg �Ի���

IMPLEMENT_DYNAMIC(ScheduleDlg, CDialogEx)

ScheduleDlg::ScheduleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ScheduleDlg::IDD, pParent)
{

}

ScheduleDlg::~ScheduleDlg()
{
}

void ScheduleDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_SCHEDULE_LSTWORK, m_lstWork);
}


BEGIN_MESSAGE_MAP(ScheduleDlg, CDialogEx)
  ON_BN_CLICKED(IDCANCEL, &ScheduleDlg::OnBnClickedCancel)
  ON_BN_CLICKED(IDC_SCHEDULE_EXIT, &ScheduleDlg::OnBnClickedScheduleExit)
  ON_BN_CLICKED(IDC_SCHEDULE_BTNHIDE, &ScheduleDlg::OnBnClickedScheduleBtnhide)
  ON_MESSAGE(WM_SHOWTASK,OnShowTask)
  ON_MESSAGE(WM_UPDATELIST, &ScheduleDlg::OnUpdateList)
  ON_WM_TIMER()
  ON_BN_CLICKED(IDC_SCHEDULE_BTNDELETEWORK, &ScheduleDlg::OnBnClickedScheduleBtndeletework)
  ON_BN_CLICKED(IDC_SCHEDULE_BTNTOADDWORK, &ScheduleDlg::OnBnClickedScheduleBtntoaddwork)
END_MESSAGE_MAP()


// ScheduleDlg ��Ϣ�������


void ScheduleDlg::OnBnClickedCancel()
{
  // TODO: �ڴ���ӿؼ�֪ͨ����������
  if( MessageBox( "��ѡ���ʹϵͳ��Ϊ���Ѿ�����������׼���°࣬�Ƿ�ȷ��", "��ʾ", MB_OKCANCEL) == IDCANCEL)
  {
    return;
  }
  // TODO�� �����°���Ϣ��������
  theApp.m_peer->Shutdown(300);
  CDialogEx::OnCancel();
  //RakNet::RakPeerInterface::DestroyInstance( theApp.m_peer);

}


void ScheduleDlg::OnBnClickedScheduleExit()
{
  // TODO: �ڴ���ӿؼ�֪ͨ����������
  OnBnClickedCancel();
}

void ScheduleDlg::OnBnClickedScheduleBtnhide()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	toTray();
}

void ScheduleDlg::toTray()
{
	NOTIFYICONDATA nid;  
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);  
	nid.hWnd=this->m_hWnd;  
	nid.uID=IDR_MAINFRAME;  
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;  
	nid.uCallbackMessage=WM_SHOWTASK;//�Զ������Ϣ����  
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));  
	strcpy(nid.szTip,"OA");//��Ϣ��ʾ��Ϊ��OA��  
	Shell_NotifyIcon(NIM_ADD,&nid);//�����������ͼ��  
	ShowWindow(SW_HIDE);//���������� 
}

LRESULT ScheduleDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{//wParam���յ���ͼ���ID����lParam���յ���������Ϊ 
	if(wParam != IDR_MAINFRAME) return 1;
	switch (lParam)
	{
	case WM_LBUTTONUP://���������ʾ������
		{
			this->ShowWindow(SW_SHOW);
			SetForegroundWindow();
			DeleteTray();
		}break;
	case WM_RBUTTONUP://�һ������˵�
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);//�õ����λ��
			CMenu menu;
			menu.CreatePopupMenu();
			menu.AppendMenu(MFT_STRING, IDR_SHOW, "��������");
			menu.AppendMenu(MFT_STRING, IDR_OTHER, "����");
			menu.AppendMenu(MFT_STRING, IDR_EXIT, "�˳�");
			SetForegroundWindow();
			EnableMenuItem(menu,IDR_OTHER,MF_GRAYED);//"����"�˵����
			//menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x,lpoint->y,this);//��ʾ�˵�
			int xx=TrackPopupMenu(menu,TPM_RETURNCMD,lpoint->x,lpoint->y,NULL,this->m_hWnd,NULL);//��ʾ�˵�����ȡѡ��ID
			if(xx==IDR_SHOW) 
			{
				this->ShowWindow(SW_SHOW);
				SetForegroundWindow();
				DeleteTray();
			}
			else if(xx==IDR_OTHER) {MessageBox("�����ˡ��������˵�","��ʾ",MB_OK);}
			else if(xx==IDR_EXIT) {OnBnClickedCancel();}
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}break;
	case WM_LBUTTONDBLCLK:
		{
			//˫��������
		}break;
	}
	return 0;
}

void ScheduleDlg::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy(nid.szTip,"OA");
	Shell_NotifyIcon(NIM_DELETE, &nid);
}


afx_msg LRESULT ScheduleDlg::OnUpdateList(WPARAM wParam, LPARAM lParam)
{
  m_lstWork.DeleteAllItems();

  for( int i=1; i<=m_timerCount; i++)
  {
    KillTimer(i);
  }

  for( map<string, pair<string,int> >::reverse_iterator iter = theApp.m_schedule.rbegin();
    iter != theApp.m_schedule.rend(); iter++)
  {
    int nRow = m_lstWork.InsertItem( 0, iter->first.c_str());
    m_lstWork.SetItemText(nRow, 1, iter->second.first.c_str());
    int year,month,day,hour,minute,second;
    sscanf( iter->first.c_str(), "%d-%d-%d %d:%d:%d", &year,&month,&day,&hour,&minute,&second);
    COleDateTime workTime( year, month, day, hour, minute, second);
    COleDateTime now = COleDateTime::GetCurrentTime();
    COleDateTimeSpan timeSpan = workTime - now;
    long expi_second = (timeSpan.GetTotalSeconds())*1000 - 2*60*1000;//��ǰ2���ӵ���
    SetTimer( ++m_timerCount, expi_second, 0);
  }

  return 0;
}


BOOL ScheduleDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  LONG lStyle; 
  lStyle = GetWindowLong(m_lstWork.m_hWnd, GWL_STYLE);// ��ȡ��ǰ����style 
  lStyle &= ~LVS_TYPEMASK; // �����ʾ��ʽλ 
  lStyle |= LVS_REPORT; // ����style 
  SetWindowLong(m_lstWork.m_hWnd, GWL_STYLE, lStyle);// ����style 
  DWORD dwStyle = m_lstWork.GetExtendedStyle(); 
  dwStyle |= LVS_EX_FULLROWSELECT;// ѡ��ĳ��ʹ���и�����ֻ������report ����listctrl �� 
  dwStyle |= LVS_EX_GRIDLINES;// �����ߣ�ֻ������report ����listctrl �� 
  m_lstWork.SetExtendedStyle(dwStyle); // ������չ��� 

  m_lstWork.InsertColumn( 0, "ʱ��", LVCFMT_LEFT, 125);
  m_lstWork.InsertColumn( 1, "����", LVCFMT_LEFT, 210);

  m_timerCount = 0;

  return TRUE;  // return TRUE unless you set the focus to a control
  // �쳣: OCX ����ҳӦ���� FALSE
}


void ScheduleDlg::OnTimer(UINT_PTR nIDEvent)
{
  // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
  map<string, pair<string,int> >::iterator iter = theApp.m_schedule.begin();//�ֵ�����С��һ���������ʱ��
  char hint[1024];
  sprintf( hint, "���ƻ��� %s ʱ���й�����%s���־����ʱ���Ѳ��������ӡ�", iter->first.c_str(), iter->second.first.c_str());
  int ID = iter->second.second;
  theApp.m_schedule.erase( iter);
  SendMessage( WM_UPDATELIST);
  
  RakNet::BitStream bsOut;
  bsOut.Write( (RakNet::MessageID)RH_SCHEDULE);
  bsOut.Write( SO_DONE);
  bsOut.Write( ID);
  theApp.m_peer->Send( &bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, theApp.m_serverAddress, false);

  MessageBox( hint, "��ʾ", MB_OK);


  CDialogEx::OnTimer(nIDEvent);
}


void ScheduleDlg::OnBnClickedScheduleBtndeletework()
{
  // TODO: �ڴ���ӿؼ�֪ͨ����������
  POSITION pos = m_lstWork.GetFirstSelectedItemPosition();
  if( pos == NULL)
  {
    MessageBox("����û��ѡ���κ�һ�С�", "����", MB_OK);
    return;
  }
  int nItem = m_lstWork.GetNextSelectedItem(pos);
  RakNet::BitStream bsOut;
  bsOut.Write( (RakNet::MessageID)RH_SCHEDULE);
  bsOut.Write( SO_DONE);
  string time = m_lstWork.GetItemText( nItem, 0).GetBuffer();
  map< string, pair<string,int> >::iterator iter = theApp.m_schedule.find( time);
  int ID = iter->second.second;
  bsOut.Write( ID);
  theApp.m_peer->Send( &bsOut,HIGH_PRIORITY, RELIABLE_ORDERED, 0, theApp.m_serverAddress, false);
  theApp.m_schedule.erase( iter);
  SendMessage( WM_UPDATELIST);
}


void ScheduleDlg::OnBnClickedScheduleBtntoaddwork()
{
  // TODO: �ڴ���ӿؼ�֪ͨ����������
  CAddWorkDlg addWorkDlg;
  addWorkDlg.DoModal();
}
