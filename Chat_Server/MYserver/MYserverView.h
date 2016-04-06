
// MYserverView.h : interface of the CMYserverView class
//

#pragma once

#include "resource.h"
#include "CustomSocket.h"

class CMYserverView : public CFormView
{
protected: // create from serialization only
	CMYserverView();
	DECLARE_DYNCREATE(CMYserverView)

public:
	enum{ IDD = IDD_MYSERVER_FORM };

// Attributes
public:
	CMYserverDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CMYserverView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
//	CString m_PORT;
	int m_PORT;
	CCustomSocket m_pListener;
	CClientSock* m_Sender;
	afx_msg void OnBnClickedButton1();
	CListBox m_ListChat;
	afx_msg LRESULT OnMsgConnect(WPARAM,LPARAM);//自己写接受的消息映射函数

	void OnRcv(CClientSock* pConn);
    void OnSendMy(CClientSock* pConn1);
	void OnStau(CClientSock* pConn2);

	afx_msg void OnBnClickedButton4();
	afx_msg void OnReport();
	afx_msg void OnStoplisten();
	afx_msg void OnUpdateReport(CCmdUI *pCmdUI);
	bool m_Greybutton; //菜单变灰
	afx_msg void OnUpdateStoplisten(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedButton2();
	void OnBnClickedClear();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CString m_EDITSEND;
	static bool FlagSend;
	static int NUMpeople;
	CEdit m_EDITSEND1;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton3();
};

#ifndef _DEBUG  // debug version in MYserverView.cpp
inline CMYserverDoc* CMYserverView::GetDocument() const
   { return reinterpret_cast<CMYserverDoc*>(m_pDocument); }
#endif

