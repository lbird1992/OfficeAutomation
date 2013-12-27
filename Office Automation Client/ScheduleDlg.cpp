// ScheduleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Office Automation Client.h"
#include "ScheduleDlg.h"
#include "afxdialogex.h"
#include "PacketType.h"
#include "AddWorkDlg.h"

// ScheduleDlg 对话框

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


// ScheduleDlg 消息处理程序


void ScheduleDlg::OnBnClickedCancel()
{
  // TODO: 在此添加控件通知处理程序代码
  if( MessageBox( "此选项会使系统认为您已经结束工作，准备下班，是否确定", "提示", MB_OKCANCEL) == IDCANCEL)
  {
    return;
  }
  // TODO： 发送下班信息到服务器
  theApp.m_peer->Shutdown(300);
  CDialogEx::OnCancel();
  //RakNet::RakPeerInterface::DestroyInstance( theApp.m_peer);

}


void ScheduleDlg::OnBnClickedScheduleExit()
{
  // TODO: 在此添加控件通知处理程序代码
  OnBnClickedCancel();
}

void ScheduleDlg::OnBnClickedScheduleBtnhide()
{
	// TODO: 在此添加控件通知处理程序代码
	toTray();
}

void ScheduleDlg::toTray()
{
	NOTIFYICONDATA nid;  
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);  
	nid.hWnd=this->m_hWnd;  
	nid.uID=IDR_MAINFRAME;  
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;  
	nid.uCallbackMessage=WM_SHOWTASK;//自定义的消息名称  
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));  
	strcpy(nid.szTip,"OA");//信息提示条为“OA”  
	Shell_NotifyIcon(NIM_ADD,&nid);//在托盘区添加图标  
	ShowWindow(SW_HIDE);//隐藏主窗口 
}

LRESULT ScheduleDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{//wParam接收的是图标的ID，而lParam接收的是鼠标的行为 
	if(wParam != IDR_MAINFRAME) return 1;
	switch (lParam)
	{
	case WM_LBUTTONUP://左键单击显示主界面
		{
			this->ShowWindow(SW_SHOW);
			SetForegroundWindow();
			DeleteTray();
		}break;
	case WM_RBUTTONUP://右击弹出菜单
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);//得到鼠标位置
			CMenu menu;
			menu.CreatePopupMenu();
			menu.AppendMenu(MFT_STRING, IDR_SHOW, "打开主界面");
			menu.AppendMenu(MFT_STRING, IDR_OTHER, "其他");
			menu.AppendMenu(MFT_STRING, IDR_EXIT, "退出");
			SetForegroundWindow();
			EnableMenuItem(menu,IDR_OTHER,MF_GRAYED);//"其他"菜单变灰
			//menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x,lpoint->y,this);//显示菜单
			int xx=TrackPopupMenu(menu,TPM_RETURNCMD,lpoint->x,lpoint->y,NULL,this->m_hWnd,NULL);//显示菜单并获取选项ID
			if(xx==IDR_SHOW) 
			{
				this->ShowWindow(SW_SHOW);
				SetForegroundWindow();
				DeleteTray();
			}
			else if(xx==IDR_OTHER) {MessageBox("你点击了“其他”菜单","提示",MB_OK);}
			else if(xx==IDR_EXIT) {OnBnClickedCancel();}
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}break;
	case WM_LBUTTONDBLCLK:
		{
			//双击不处理
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
    long expi_second = (timeSpan.GetTotalSeconds())*1000 - 2*60*1000;//提前2分钟弹窗
    SetTimer( ++m_timerCount, expi_second, 0);
  }

  return 0;
}


BOOL ScheduleDlg::OnInitDialog()
{
  CDialogEx::OnInitDialog();

  LONG lStyle; 
  lStyle = GetWindowLong(m_lstWork.m_hWnd, GWL_STYLE);// 获取当前窗口style 
  lStyle &= ~LVS_TYPEMASK; // 清除显示方式位 
  lStyle |= LVS_REPORT; // 设置style 
  SetWindowLong(m_lstWork.m_hWnd, GWL_STYLE, lStyle);// 设置style 
  DWORD dwStyle = m_lstWork.GetExtendedStyle(); 
  dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
  dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
  m_lstWork.SetExtendedStyle(dwStyle); // 设置扩展风格 

  m_lstWork.InsertColumn( 0, "时间", LVCFMT_LEFT, 125);
  m_lstWork.InsertColumn( 1, "内容", LVCFMT_LEFT, 210);

  m_timerCount = 0;

  return TRUE;  // return TRUE unless you set the focus to a control
  // 异常: OCX 属性页应返回 FALSE
}


void ScheduleDlg::OnTimer(UINT_PTR nIDEvent)
{
  // TODO: 在此添加消息处理程序代码和/或调用默认值
  map<string, pair<string,int> >::iterator iter = theApp.m_schedule.begin();//字典序最小的一定是最近的时间
  char hint[1024];
  sprintf( hint, "您计划在 %s 时进行工作：%s。现距离该时间已不足两分钟。", iter->first.c_str(), iter->second.first.c_str());
  int ID = iter->second.second;
  theApp.m_schedule.erase( iter);
  SendMessage( WM_UPDATELIST);
  
  RakNet::BitStream bsOut;
  bsOut.Write( (RakNet::MessageID)RH_SCHEDULE);
  bsOut.Write( SO_DONE);
  bsOut.Write( ID);
  theApp.m_peer->Send( &bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, theApp.m_serverAddress, false);

  MessageBox( hint, "提示", MB_OK);


  CDialogEx::OnTimer(nIDEvent);
}


void ScheduleDlg::OnBnClickedScheduleBtndeletework()
{
  // TODO: 在此添加控件通知处理程序代码
  POSITION pos = m_lstWork.GetFirstSelectedItemPosition();
  if( pos == NULL)
  {
    MessageBox("您并没有选中任何一行。", "错误", MB_OK);
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
  // TODO: 在此添加控件通知处理程序代码
  CAddWorkDlg addWorkDlg;
  addWorkDlg.DoModal();
}
