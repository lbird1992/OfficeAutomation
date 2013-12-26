#pragma once


// CFileDlg 对话框

class CFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileDlg)

public:
	CFileDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFileDlg();

// 对话框数据
	enum { IDD = IDD_FILES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
