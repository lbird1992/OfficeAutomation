#pragma once


// CSendMailDlg �Ի���

class CSendMailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSendMailDlg)

public:
	CSendMailDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSendMailDlg();

// �Ի�������
	enum { IDD = IDD_SENDMAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
