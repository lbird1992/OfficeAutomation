#pragma once


// CMessageSendDlg �Ի���

class CMessageSendDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMessageSendDlg)

public:
	CMessageSendDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMessageSendDlg();

// �Ի�������
	enum { IDD = IDD_SENDMESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
