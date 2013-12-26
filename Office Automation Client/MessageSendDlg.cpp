// MessageSendDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Office Automation Client.h"
#include "MessageSendDlg.h"
#include "afxdialogex.h"


// CMessageSendDlg 对话框

IMPLEMENT_DYNAMIC(CMessageSendDlg, CDialogEx)

CMessageSendDlg::CMessageSendDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMessageSendDlg::IDD, pParent)
{

}

CMessageSendDlg::~CMessageSendDlg()
{
}

void CMessageSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMessageSendDlg, CDialogEx)
END_MESSAGE_MAP()


// CMessageSendDlg 消息处理程序
