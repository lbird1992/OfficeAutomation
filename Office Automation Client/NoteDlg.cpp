// NoteDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Office Automation Client.h"
#include "NoteDlg.h"
#include "afxdialogex.h"


// CNoteDlg 对话框

IMPLEMENT_DYNAMIC(CNoteDlg, CDialogEx)

CNoteDlg::CNoteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNoteDlg::IDD, pParent)
{

}

CNoteDlg::~CNoteDlg()
{
}

void CNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNoteDlg, CDialogEx)
END_MESSAGE_MAP()


// CNoteDlg 消息处理程序
