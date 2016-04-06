// CustomSocket.cpp : implementation file
//

#include "stdafx.h"
#include "MyHead.h"
#include "CustomSocket.h"
//#include "Chat_Server.h"
//#include "CustomSocket.h"

// CustomSocket

CustomSocket::CustomSocket()
{
}

CustomSocket::~CustomSocket()
{
}


// CustomSocket member functions
void CustomSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	/*CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	p->SendMessage(MSG_ACCEPT,0,0);*/
	CAsyncSocket::OnAccept(nErrorCode);
}


void CustomSocket::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	//AfxMessageBox(_T("连接成功"));
	/*CLOGIN::FlagSend = true;
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	p->SendMessage(MSG_ACCEPT,0,0);*/

	CAsyncSocket::OnConnect(nErrorCode);

}


void CustomSocket::OnSend(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CAsyncSocket::OnSend(nErrorCode);
}


void CustomSocket::OnReceive(int nErrorCode)
{
	/*CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	p->SendMessage(MSG_ACCEPT,0,0);*/
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
		CChat_ServerView* pNewView = (CChat_ServerView *)p->GetActiveView();
	pNewView ->OnRcv();
	CAsyncSocket::OnReceive(nErrorCode);
}
