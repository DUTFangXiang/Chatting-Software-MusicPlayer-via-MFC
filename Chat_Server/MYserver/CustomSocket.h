#pragma once

// CCustomSocket command target

class CCustomSocket : public CAsyncSocket
{
public:
	CCustomSocket();
	virtual ~CCustomSocket();
	virtual void OnAccept(int nErrorCode);
	//¼ÇÂ¼¶Ë¿ÚºÅÓëIP
	UINT PortNum;
	CString IPDrr;
	virtual void OnSend(int nErrorCode);
};



// CClientSock command target

class CClientSock : public CAsyncSocket
{
public:
	CClientSock();
	virtual ~CClientSock();
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	static int CountMessage;

};


