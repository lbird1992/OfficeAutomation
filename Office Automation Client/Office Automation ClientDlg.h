
// Office Automation ClientDlg.h : ͷ�ļ�
//

#pragma once


// COfficeAutomationClientDlg �Ի���
class COfficeAutomationClientDlg : public CDialogEx
{
// ����
public:
	COfficeAutomationClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OFFICEAUTOMATIONCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
