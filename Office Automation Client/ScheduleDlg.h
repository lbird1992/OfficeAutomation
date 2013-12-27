#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// ScheduleDlg 对话框

class ScheduleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ScheduleDlg)

public:
	ScheduleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ScheduleDlg();

// 对话框数据
	enum { IDD = IDD_SCHEDULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedCancel();
  CListCtrl m_lstWork;
  afx_msg void OnBnClickedScheduleExit();
};
