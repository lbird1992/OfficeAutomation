// ScheduleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Office Automation Client.h"
#include "ScheduleDlg.h"
#include "afxdialogex.h"

#define WM_SHOWTASK (WM_USER +1)
#define IDR_SHOW 11
#define IDR_OTHER 12
#define IDR_EXIT 13

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
  ON_BN_CLICKED(IDC_SCHEDULE_EXIT, &ScheduleDlg::OnBnClickedScheduleExit)
  ON_BN_CLICKED(IDC_SCHEDULE_BTNHIDE, &ScheduleDlg::OnBnClickedScheduleBtnhide)
  ON_MESSAGE(WM_SHOWTASK,OnShowTask)
END_MESSAGE_MAP()


// ScheduleDlg ��Ϣ�������


void ScheduleDlg::OnBnClickedCancel()
{
  // TODO: �ڴ���ӿؼ�֪ͨ����������
  if( MessageBox( "��ѡ���ʹϵͳ��Ϊ���Ѿ�����������׼���°࣬�Ƿ�ȷ��", "��ʾ", MB_OKCANCEL) == IDCANCEL)
  {
    return;
  }
  // TODO�� �����°���Ϣ��������
  CDialogEx::OnCancel();
}


void ScheduleDlg::OnBnClickedScheduleExit()
{
  // TODO: �ڴ���ӿؼ�֪ͨ����������
  OnBnClickedCancel();
}


void ScheduleDlg::OnBnClickedScheduleBtnhide()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	toTray();
}

void ScheduleDlg::toTray()
{
	NOTIFYICONDATA nid;  
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);  
	nid.hWnd=this->m_hWnd;  
	nid.uID=IDR_MAINFRAME;  
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ;  
	nid.uCallbackMessage=WM_SHOWTASK;//�Զ������Ϣ����  
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));  
	strcpy(nid.szTip,"OA");//��Ϣ��ʾ��Ϊ��OA��  
	Shell_NotifyIcon(NIM_ADD,&nid);//�����������ͼ��  
	ShowWindow(SW_HIDE);//���������� 
}

LRESULT ScheduleDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{//wParam���յ���ͼ���ID����lParam���յ���������Ϊ 
	if(wParam != IDR_MAINFRAME) return 1;
	switch (lParam)
	{
	case WM_LBUTTONUP://���������ʾ������
		{
			this->ShowWindow(SW_SHOW);
			SetForegroundWindow();
			DeleteTray();
		}break;
	case WM_RBUTTONUP://�һ������˵�
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);//�õ����λ��
			CMenu menu;
			menu.CreatePopupMenu();
			menu.AppendMenu(MFT_STRING, IDR_SHOW, "��������");
			menu.AppendMenu(MFT_STRING, IDR_OTHER, "����");
			menu.AppendMenu(MFT_STRING, IDR_EXIT, "�˳�");
			SetForegroundWindow();
			EnableMenuItem(menu,IDR_OTHER,MF_GRAYED);//"����"�˵����
			//menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x,lpoint->y,this);//��ʾ�˵�
			int xx=TrackPopupMenu(menu,TPM_RETURNCMD,lpoint->x,lpoint->y,NULL,this->m_hWnd,NULL);//��ʾ�˵�����ȡѡ��ID
			if(xx==IDR_SHOW) 
			{
				this->ShowWindow(SW_SHOW);
				SetForegroundWindow();
				DeleteTray();
			}
			else if(xx==IDR_OTHER) {MessageBox("�����ˡ��������˵�","��ʾ",MB_OK);}
			else if(xx==IDR_EXIT) {OnBnClickedCancel();}
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}break;
	case WM_LBUTTONDBLCLK:
		{
			//˫��������
		}break;
	}
	return 0;
}

void ScheduleDlg::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy(nid.szTip,"OA");
	Shell_NotifyIcon(NIM_DELETE, &nid);
}
