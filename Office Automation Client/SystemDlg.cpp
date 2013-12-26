// SystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Office Automation Client.h"
#include "SystemDlg.h"
#include "afxdialogex.h"


// CSystemDlg 对话框

IMPLEMENT_DYNAMIC(CSystemDlg, CDialogEx)

CSystemDlg::CSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSystemDlg::IDD, pParent)
{

}

CSystemDlg::~CSystemDlg()
{
}

void CSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSystemDlg, CDialogEx)
END_MESSAGE_MAP()


// CSystemDlg 消息处理程序
