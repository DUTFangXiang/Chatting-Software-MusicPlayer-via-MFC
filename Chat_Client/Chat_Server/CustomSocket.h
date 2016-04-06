#pragma once

//#include "Chat_ServerView.h"
// CustomSocket command target

class CustomSocket : public CAsyncSocket
{
public:
	//CChat_ServerView* m_pView;//JJC£ºÖ÷½çÃæ
	CustomSocket();
	virtual ~CustomSocket();
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	//CChat_ServerDoc* GetDocument(){return (CChat_ServerDoc*)m_pDocument ;}
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


