// CustomSocket.cpp : implementation file
//

#include "stdafx.h"
#include "MyHead.h"
#include "CustomSocket.h"


// CCustomSocket
int CClientSock::CountMessage=0;//统计信息数目的

CCustomSocket::CCustomSocket()
{
}

CCustomSocket::~CCustomSocket()
{
}


void CCustomSocket::OnAccept(int nErrorCode)
{
   if(nErrorCode == 0 )
   {
		CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
		CMYserverView* pNewView = (CMYserverView *)p->GetActiveView();
		pNewView ->m_ListChat.AddString(_T("有客户端已连接"));
		pNewView ->m_ListChat.AddString(_T(""));
		//pNewView ->SendMessage(MSG_RECEIVE ,0,0);
		CClientSock* pNewConn = new CClientSock;
		CString strAddr("");
		CString strip("");
		UINT nPort=0;
		if(Accept(*pNewConn))
		{
			pNewConn->AsyncSelect(FD_READ);
			pNewConn->GetPeerName(strAddr,nPort);
		}
		strip.Format(_T("%d"),nPort);
		pNewView ->m_ListChat.AddString(strAddr+_T("  ： ")+strip);
		pNewView ->m_ListChat.AddString(_T(""));
   }
   else
   {  }
   CAsyncSocket::OnAccept(nErrorCode);
}

// CClientSock

CClientSock::CClientSock()
{
}

CClientSock::~CClientSock()
{
}


// CClientSock member functions


void CClientSock::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CAsyncSocket::OnConnect(nErrorCode);
}

void CClientSock::OnReceive(int nErrorCode)
{
	if(nErrorCode == 0)
	{
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
    CMYserverView* pNewView = (CMYserverView *)p->GetActiveView();
	pNewView->OnRcv(this);
	pNewView->OnStau(this);
	}
	CAsyncSocket::OnReceive(nErrorCode);
}


void CClientSock::OnSend(int nErrorCode)
{
        //发送数据  
	if(nErrorCode == 0)
	{
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
    CMYserverView* pNewView = (CMYserverView *)p->GetActiveView();
	pNewView->OnSendMy(this);
	AsyncSelect(FD_READ);
	//pNewView ->SendMessage(MSG_RECEIVE ,0,0);
	//    Send(m_szBuffer,m_nLength,0);  
	}  
	CAsyncSocket::OnSend(nErrorCode);
}


void CCustomSocket::OnSend(int nErrorCode)
{


	CAsyncSocket::OnSend(nErrorCode);
}
