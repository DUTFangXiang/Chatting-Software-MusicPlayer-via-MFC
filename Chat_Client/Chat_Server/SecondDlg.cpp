// SecondDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Chat_Server.h"
#include "SecondDlg.h"
#include "Chat_ServerDoc.h"


// CSecondDlg
 int CSecondDlg::CountMessage=1;

IMPLEMENT_DYNCREATE(CSecondDlg, CFormView)

CSecondDlg::CSecondDlg()
	: CFormView(CSecondDlg::IDD)
{

}

CSecondDlg::~CSecondDlg()
{
}

void CSecondDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ListChat, m_ListChat);
}

BEGIN_MESSAGE_MAP(CSecondDlg, CFormView)

END_MESSAGE_MAP()


// CSecondDlg diagnostics

#ifdef _DEBUG
void CSecondDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSecondDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


//JJC：在列表中显示对应的字符串
void CSecondDlg::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{  
	if(lHint==1)
	{
		CChat_ServerDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		m_ListChat.AddString(pDoc->EditDocument);
		m_ListChat.AddString(_T(" "));

		//用于保存作用
	    int nSel = m_ListChat.GetCount();	
	    CSecondDlg::CountMessage = nSel;         
        for( int i=0; i< nSel; i++ ){
          m_ListChat.GetText(i ,pDoc->Str[i]);
		 }
		pDoc->UpdateAllViews(NULL); 
	}
	//登录时候消息提醒
	if(lHint == 15)
	{
        CChat_ServerDoc* pDoc = GetDocument();
	    ASSERT_VALID(pDoc);
		m_ListChat.AddString(pDoc->EditDocument );
	    m_ListChat.AddString(_T(" "));
				//用于保存作用
	    int nSel1 = m_ListChat.GetCount();	
	    CSecondDlg::CountMessage = nSel1;         
        for( int i=0; i< nSel1; i++ ){
          m_ListChat.GetText(i ,pDoc->Str[i]);
		 }
		pDoc->UpdateAllViews(NULL); 
	 }
	else
	{
		Invalidate();
	}	
 }



