// MailListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Office Automation Client.h"
#include "MailListDlg.h"
#include "afxdialogex.h"


// CMailListDlg 对话框

IMPLEMENT_DYNAMIC(CMailListDlg, CDialogEx)

CMailListDlg::CMailListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMailListDlg::IDD, pParent)
{

}

CMailListDlg::~CMailListDlg()
{
}

void CMailListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMailListDlg, CDialogEx)
END_MESSAGE_MAP()


// CMailListDlg 消息处理程序
