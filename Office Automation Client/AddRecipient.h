#pragma once


// CAddRecipient �Ի���

class CAddRecipient : public CDialogEx
{
	DECLARE_DYNAMIC(CAddRecipient)

public:
	CAddRecipient(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddRecipient();

// �Ի�������
	enum { IDD = IDD_ADDRECIPIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
