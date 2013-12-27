#pragma once
#include "afxwin.h"
#include "afxcmn.h"


#define WM_SHOWTASK (WM_USER +1)
#define WM_UPDATELIST (WM_SHOWTASK+1)
#define IDR_SHOW 11
#define IDR_OTHER 12
#define IDR_EXIT 13

// ScheduleDlg �Ի���

class ScheduleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ScheduleDlg)

public:
	ScheduleDlg(CWnd* pParent = NULL);   // ��׼���캯��
	void toTray();//��С��������
	void DeleteTray();//ɾ������ͼ��
	virtual ~ScheduleDlg();

// �Ի�������
	enum { IDD = IDD_SCHEDULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedCancel();
  afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam) ;//ͼ��ָ�
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
