// ScheduleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Office Automation Client.h"
#include "ScheduleDlg.h"
#include "afxdialogex.h"


// ScheduleDlg �Ի���

IMPLEMENT_DYNAMIC(ScheduleDlg, CDialogEx)

ScheduleDlg::ScheduleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ScheduleDlg::IDD, pParent)
{

}

ScheduleDlg::~ScheduleDlg()
{
}

void ScheduleDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_SCHEDULE_LSTWORK, m_lstWork);
}


BEGIN_MESSAGE_MAP(ScheduleDlg, CDialogEx)
  ON_BN_CLICKED(IDCANCEL, &ScheduleDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// ScheduleDlg ��Ϣ��������


void ScheduleDlg::OnBnClickedCancel()
{
  // TODO: �ڴ����ӿؼ�֪ͨ�����������
  if( MessageBox( "��ѡ���ʹϵͳ��Ϊ���Ѿ�����������׼���°࣬�Ƿ�ȷ��", "��ʾ", MB_OKCANCEL) == IDCANCEL)
  {
    return;
  }
  // TODO�� �����°���Ϣ��������
  CDialogEx::OnCancel();
}