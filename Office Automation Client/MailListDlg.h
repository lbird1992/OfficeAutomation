#pragma once


// CMailListDlg �Ի���

class CMailListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMailListDlg)

public:
	CMailListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMailListDlg();

// �Ի�������
	enum { IDD = IDD_MAILLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
