
#include "stdafx.h"
#include "Chat_Server.h"
#include "CthirdDlg.h"
#include "LOGIN.h"

// CChatStatus
//控制第3个窗口中显示“客户端状态”
bool CChatStatus::Flag_init = true;

IMPLEMENT_DYNCREATE(CChatStatus, CFormView)

CChatStatus::CChatStatus()
	: CFormView(CChatStatus::IDD)
{

}

CChatStatus::~CChatStatus()
{
}

void CChatStatus::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ChatStatus);
}

BEGIN_MESSAGE_MAP(CChatStatus, CFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CChatStatus diagnostics

#ifdef _DEBUG
void CChatStatus::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CChatStatus::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CChatStatus message handlers
//JJC：更新第三窗口的数据和状态
void CChatStatus::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	//
	if( (CChatStatus::Flag_init ==true)&&(CLOGIN::FlagSend == false))
	{
	   //JJC：清空界面
	   m_ChatStatus.ResetContent();
	   m_ChatStatus.AddString(_T("                        "));
	   m_ChatStatus.AddString(_T("                   客户端状态        "));
	   m_ChatStatus.AddString(_T("*****************************"));
	   m_ChatStatus.AddString(_T("                        "));
	   m_ChatStatus.AddString(_T("当前登录状态：172.0.0.1 "));
	   m_ChatStatus.AddString(_T("端口：5555 "));
	   m_ChatStatus.AddString(_T("客户：姜佳成 "));	   
	   m_ChatStatus.AddString(_T("***系统提示：请先连接服务器****"));
	   m_ChatStatus.AddString(_T("                        "));
	   m_ChatStatus.AddString(_T("可点击登录菜单更改登录IP等信息"));
	   m_ChatStatus.AddString(_T("                        "));

	   CChatStatus::Flag_init = false;
	}

	if((CLOGIN::FlagSend == false)&&(lHint == 5))
	{
	  CChat_ServerDoc* pDoc = GetDocument();
	    ASSERT_VALID(pDoc);
	  m_ChatStatus.AddString(pDoc->NameDoc + _T("：  退出当前会话"));
	  m_ChatStatus.AddString(_T("                        "));
	
	 }

	if((CLOGIN::FlagSend == false)&&(lHint == 2))
	{
	    m_ChatStatus.AddString(_T("*****************************"));
	    m_ChatStatus.AddString(_T("******系统提示：请先连接******"));
		m_ChatStatus.AddString(_T("可点击登录菜单更改登录IP等信息"));
		m_ChatStatus.AddString(_T("*****************************"));
		m_ChatStatus.AddString(_T("                        "));
	 }

	if((CLOGIN::FlagSend == false)&&(lHint == 3))
	{
	    m_ChatStatus.AddString(_T("*****************************"));
	    m_ChatStatus.AddString(_T("****登录失败，请重新登录*****"));
		m_ChatStatus.AddString(_T("                        "));
	 }
	//登录时候消息提醒
	if(lHint == 11)
	{
	    m_ChatStatus.AddString(_T("****您已经成功登录*****"));
		m_ChatStatus.AddString(_T("                        "));
        CChat_ServerDoc* pDoc = GetDocument();
	    ASSERT_VALID(pDoc);
		m_ChatStatus.AddString(pDoc->NameDoc + _T("：  has just joined the talk"));
	 }
	//登录时候消息提醒
	if(lHint == 12)
	{
        CChat_ServerDoc* pDoc = GetDocument();
	    ASSERT_VALID(pDoc);
		m_ChatStatus.AddString(pDoc->NameDoc + _T("：  退出当前会话"));
	    m_ChatStatus.AddString(_T("                        "));
	 }
	//登录时候消息提醒
	if(lHint == 13)
	{
        CChat_ServerDoc* pDoc = GetDocument();
	    ASSERT_VALID(pDoc);
		m_ChatStatus.AddString(pDoc->NameDoc + _T("：  加入当前会话"));
	    m_ChatStatus.AddString(_T("                        "));
	 }

	if(lHint == 4)
	{		 
		CChat_ServerDoc* pDoc = GetDocument();
	    ASSERT_VALID(pDoc);
		m_ChatStatus.AddString(_T("您当前信息为：")+pDoc->IPDoc+_T("网络"));
		m_ChatStatus.AddString(_T("                       "));
		CString cs;
		cs.Format(_T("%d"),pDoc->PortDoc);
		m_ChatStatus.AddString(_T("端口号：")+cs+_T("     登录人：")+pDoc->NameDoc);
		m_ChatStatus.AddString(_T("                       "));
	}
	else
	{
		Invalidate();
	}
}


