#pragma once


// CNoteDlg �Ի���

class CNoteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNoteDlg)

public:
	CNoteDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNoteDlg();

// �Ի�������
	enum { IDD = IDD_NOTES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
