#pragma once


// CAddWorkDlg �Ի���

class CAddWorkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddWorkDlg)

public:
	CAddWorkDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddWorkDlg();

// �Ի�������
	enum { IDD = IDD_ADDWORK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
