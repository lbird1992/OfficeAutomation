
// Office Automation ClientDlg.h : 头文件
//

#pragma once


// COfficeAutomationClientDlg 对话框
class COfficeAutomationClientDlg : public CDialogEx
{
// 构造
public:
	COfficeAutomationClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_OFFICEAUTOMATIONCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedOk();
//  CString password;
  CString m_name;
  CString m_password;
  afx_msg void OnBnClickedLoginExit();
  afx_msg void OnBnClickedLoginLogin();
//  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  virtual BOOL PreTranslateMessage(MSG* pMsg);
};
