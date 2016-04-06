// LOGIN.cpp : implementation file
//

#include "stdafx.h"
#include "Chat_Server.h"
#include "LOGIN.h"
#include "afxdialogex.h"


// 确定是否可以发送
bool CLOGIN::FlagSend = false;
//确定是否显示已连接
bool CLOGIN::FlagConnect = true; 
bool CLOGIN::FlagUpdate = true;
bool CLOGIN::FlagRe = true;
bool CLOGIN::Flagfirst=true;

IMPLEMENT_DYNAMIC(CLOGIN, CDialogEx)

CLOGIN::CLOGIN(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLOGIN::IDD, pParent)
{

	m_IP = _T("172.0.0.1");
	m_Name = _T("姜佳成");
	m_Port = 5555;
	
}

CLOGIN::~CLOGIN()
{
}

void CLOGIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IP, m_IP);
	DDV_MaxChars(pDX, m_IP, 20);
	DDX_Text(pDX, IDC_Name, m_Name);
	DDX_Text(pDX, IDC_Port, m_Port);
	DDX_Control(pDX, IDC_USER, m_ImageUSER);
}


BEGIN_MESSAGE_MAP(CLOGIN, CDialogEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()



