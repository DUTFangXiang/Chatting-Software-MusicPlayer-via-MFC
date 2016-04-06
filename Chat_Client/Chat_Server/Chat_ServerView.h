
// Chat_ServerView.h : interface of the CChat_ServerView class
//

#pragma once

#include "resource.h"
#include "CustomSocket.h"
//#include "MyHead.h"

class CChat_ServerView : public CFormView
{
protected: // create from serialization only
	CChat_ServerView();
	DECLARE_DYNCREATE(CChat_ServerView)

public:
	enum{ IDD = IDD_CHAT };

// Attributes
public:
	CChat_ServerDoc* GetDocument() const;
	//CRichEditCtrl* m_pEdit;         //±‡º≠øÚ
// Operations
public:

// Overrides
public:
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CChat_ServerView();
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedFont();
	CFont m_font;
	afx_msg void OnBnClickedClear();
	CEdit m_EDIT1;
	COLORREF color;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedSend();
	CString m_EditNovel;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CToolTipCtrl m_ctrlTT;   //JJC£∫…Ë÷√Ã· æ
	//CustomSocket* m_pClient;
	CustomSocket m_pClient;
	afx_msg void OnBnClickedButton1();
	CButton m_Connect;
	void OnRcv();
};

#ifndef _DEBUG  // debug version in Chat_ServerView.cpp
inline CChat_ServerDoc* CChat_ServerView::GetDocument() const
   { return reinterpret_cast<CChat_ServerDoc*>(m_pDocument); }
#endif

