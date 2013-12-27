#pragma once
#include "afxwin.h"
#include "afxcmn.h"


#define WM_SHOWTASK (WM_USER +1)
#define WM_UPDATELIST (WM_SHOWTASK+1)
#define IDR_SHOW 11
#define IDR_OTHER 12
#define IDR_EXIT 13

// ScheduleDlg 对话框

class ScheduleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ScheduleDlg)

public:
	ScheduleDlg(CWnd* pParent = NULL);   // 标准构造函数
	void toTray();//最小化到托盘
	void DeleteTray();//删除托盘图标
	virtual ~ScheduleDlg();

// 对话框数据
	enum { IDD = IDD_SCHEDULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedCancel();
  afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam) ;//图标恢复
  CListCtrl m_lstWork;
  afx_msg void OnBnClickedScheduleExit();
  afx_msg void OnBnClickedScheduleBtnhide();
protected:
  afx_msg LRESULT OnUpdateList(WPARAM wParam, LPARAM lParam);
  int m_timerCount;
public:
  virtual BOOL OnInitDialog();
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  afx_msg void OnBnClickedScheduleBtndeletework();
  afx_msg void OnBnClickedScheduleBtntoaddwork();
};
