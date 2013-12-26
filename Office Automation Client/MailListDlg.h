#pragma once


// CMailListDlg 对话框

class CMailListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMailListDlg)

public:
	CMailListDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMailListDlg();

// 对话框数据
	enum { IDD = IDD_MAILLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
