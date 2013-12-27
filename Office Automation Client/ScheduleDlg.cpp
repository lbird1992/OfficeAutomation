// ScheduleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Office Automation Client.h"
#include "ScheduleDlg.h"
#include "afxdialogex.h"


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
