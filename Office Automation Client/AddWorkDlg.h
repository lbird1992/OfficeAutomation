#pragma once


// CAddWorkDlg 对话框

class CAddWorkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddWorkDlg)

public:
	CAddWorkDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddWorkDlg();

// 对话框数据
	enum { IDD = IDD_ADDWORK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
