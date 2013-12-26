// AddWorkDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Office Automation Client.h"
#include "AddWorkDlg.h"
#include "afxdialogex.h"


// CAddWorkDlg 对话框

IMPLEMENT_DYNAMIC(CAddWorkDlg, CDialogEx)

CAddWorkDlg::CAddWorkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddWorkDlg::IDD, pParent)
{

}

CAddWorkDlg::~CAddWorkDlg()
{
}

void CAddWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddWorkDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddWorkDlg 消息处理程序
