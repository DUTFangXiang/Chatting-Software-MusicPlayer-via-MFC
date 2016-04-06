#pragma once

#include "Chat_ServerDoc.h "

// CSecondDlg form view

class CSecondDlg : public CFormView
{
	DECLARE_DYNCREATE(CSecondDlg)

protected:
	CSecondDlg();           // protected constructor used by dynamic creation
	virtual ~CSecondDlg();

public:
	enum { IDD = IDD_AllChat };
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
	CListBox m_ListChat;
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	CChat_ServerDoc* GetDocument(){return (CChat_ServerDoc*)m_pDocument;}
	static int CountMessage;
};
