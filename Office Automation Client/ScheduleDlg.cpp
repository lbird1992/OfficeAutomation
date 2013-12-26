// ScheduleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Office Automation Client.h"
#include "ScheduleDlg.h"
#include "afxdialogex.h"

#define WM_SHOWTASK (WM_USER +1)
#define IDR_SHOW 11
#define IDR_OTHER 12
#define IDR_EXIT 13

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
  CDialogEx::OnCancel();
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
