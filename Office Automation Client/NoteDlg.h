#pragma once


// CNoteDlg 对话框

class CNoteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNoteDlg)

public:
	CNoteDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNoteDlg();

// 对话框数据
	enum { IDD = IDD_NOTES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
