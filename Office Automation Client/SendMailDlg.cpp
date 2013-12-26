// SendMailDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Office Automation Client.h"
#include "SendMailDlg.h"
#include "afxdialogex.h"


// CSendMailDlg 对话框

IMPLEMENT_DYNAMIC(CSendMailDlg, CDialogEx)

CSendMailDlg::CSendMailDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSendMailDlg::IDD, pParent)
{

}

CSendMailDlg::~CSendMailDlg()
{
}

void CSendMailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSendMailDlg, CDialogEx)
END_MESSAGE_MAP()


// CSendMailDlg 消息处理程序
