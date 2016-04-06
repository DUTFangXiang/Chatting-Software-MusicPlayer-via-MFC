#pragma once

#include "Chat_ServerDoc.h "
//#include "CustomSocket.h"
// CChatStatus form view

class CChatStatus : public CFormView
{
	DECLARE_DYNCREATE(CChatStatus)

protected:
	CChatStatus();           // protected constructor used by dynamic creation
	virtual ~CChatStatus();

public:
	enum { IDD = IDD_ChatStatus };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CChat_ServerDoc* GetDocument(){return (CChat_ServerDoc*)m_pDocument;}
	CListBox m_ChatStatus;
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	static bool Flag_init;
};


