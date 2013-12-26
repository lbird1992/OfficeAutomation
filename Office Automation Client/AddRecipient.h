#pragma once


// CAddRecipient 对话框

class CAddRecipient : public CDialogEx
{
	DECLARE_DYNAMIC(CAddRecipient)

public:
	CAddRecipient(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddRecipient();

// 对话框数据
	enum { IDD = IDD_ADDRECIPIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
