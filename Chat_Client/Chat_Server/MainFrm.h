
// MainFrm.h : interface of the CMainFrame class
//
#pragma once

#include "CustomSocket.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
    CSplitterWnd m_wndSplitter;    //JJC： 界面分页
	CSplitterWnd m_wndSplitter1;   //JJC：界面再分
    CustomSocket*	m_pClient1;     //JJC：socket
// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:  // control bar embedded members
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	bool m_isSplitter;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLogin();
	afx_msg void OnLogout();
	afx_msg void OnUpdateLogin(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLogout(CCmdUI *pCmdUI);
	bool m_Greybutton;
	afx_msg LRESULT OnMsgConnect(WPARAM,LPARAM);//自己写接受的消息映射函数

};


