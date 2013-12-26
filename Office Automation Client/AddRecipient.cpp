// AddRecipient.cpp : 实现文件
//

#include "stdafx.h"
#include "Office Automation Client.h"
#include "AddRecipient.h"
#include "afxdialogex.h"


// CAddRecipient 对话框

IMPLEMENT_DYNAMIC(CAddRecipient, CDialogEx)

CAddRecipient::CAddRecipient(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddRecipient::IDD, pParent)
{

}

CAddRecipient::~CAddRecipient()
{
}

void CAddRecipient::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddRecipient, CDialogEx)
END_MESSAGE_MAP()


// CAddRecipient 消息处理程序
