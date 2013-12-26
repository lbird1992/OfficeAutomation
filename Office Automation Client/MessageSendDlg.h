#pragma once


// CMessageSendDlg 对话框

class CMessageSendDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMessageSendDlg)

public:
	CMessageSendDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMessageSendDlg();

// 对话框数据
	enum { IDD = IDD_SENDMESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
