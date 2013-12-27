#pragma once
#include "afxwin.h"
#include "afxcmn.h"


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
};
