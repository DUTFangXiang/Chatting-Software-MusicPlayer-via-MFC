
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
//#include "Chat_Server.h"
//#include "MainFrm.h"
#include "MyHead.h"
//#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_MESSAGE(MSG_ACCEPT,OnMsgConnect)  //JJC：自己写的接受消息映射
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SIZE()
	ON_COMMAND(ID_Login, &CMainFrame::OnLogin)
	ON_COMMAND(ID_Logout, &CMainFrame::OnLogout)
	ON_UPDATE_COMMAND_UI(ID_Login, &CMainFrame::OnUpdateLogin)
	ON_UPDATE_COMMAND_UI(ID_Logout, &CMainFrame::OnUpdateLogout)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
	: m_isSplitter(false)
	, m_Greybutton(false)
{
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
}

CMainFrame::~CMainFrame()
{
	//m_pClient->Close();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);
	//JJC: 修改工具栏为自己所用
	/*if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))*/
    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MyTOOLBAR))
	
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
    //JJC：设置标题栏的图标  
    HICON m_hIcon = AfxGetApp()->LoadIcon(IDI_QQ1);  
    SetIcon(m_hIcon,TRUE);  
    SetIcon(m_hIcon,FALSE); 

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these five lines if you don't want the toolbar and menubar to be dockable
    m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar); 

	
	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Enable toolbar and docking window menu replacement
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// enable quick (Alt+drag) toolbar customization
	CMFCToolBar::EnableQuickCustomization();

  

	// enable menu personalization (most-recently used commands)
	// TODO: define your own basic commands, ensuring that each pulldown menu has at least one basic command.
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);

	lstBasicCommands.AddTail(ID_Login);
	lstBasicCommands.AddTail(ID_Logout);
	lstBasicCommands.AddTail(ID_FILE_SAVE_AS);
	
	CMFCToolBar::SetBasicCommands(lstBasicCommands);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


//JJC：建立三个客户端界面
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
    CRect cRect;   
	GetClientRect(&cRect);
	
	if(!m_wndSplitter.CreateStatic(this,1,2))
	   return false;
	//第二个窗口再分割
	if(!m_wndSplitter1.CreateStatic(&m_wndSplitter,2,1,
		WS_CHILD|WS_VISIBLE,m_wndSplitter.IdFromRowCol(0, 1))) // 
        return false; //将第0行0列再分开2行1列 
	//显示聊天内容
	if(!m_wndSplitter1.CreateView(0,0,RUNTIME_CLASS(CSecondDlg),   //CSecondDlg
		   CSize(cRect.Width()/3*2,cRect.Height()/2),pContext))    //CSize(cRect.Width()/3*2,cRect.Height()/2)
		return false; 
	//输入字区域
	if(!m_wndSplitter1.CreateView(1,0,RUNTIME_CLASS(CChat_ServerView),   //CthirdDlg
		   CSize(cRect.Width()/3*2,cRect.Height()/2),pContext))   
		return false;
		//显示聊天状态
	if(!m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CChatStatus), 
		   CSize(cRect.Width()/3,cRect.Height()),pContext))  
		return false; 
	//控制窗口大小时候修改对应的大小
	m_isSplitter = true;

	return true;
}
//设计窗口改变大小响应
void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWndEx::OnSize(nType, cx, cy);

   if((m_isSplitter)&&nType != SIZE_MINIMIZED)  
	{  
		CRect crFram;  
	    GetClientRect(&crFram); 
		m_wndSplitter.SetColumnInfo(0,crFram.Width()/3,10);
		m_wndSplitter.SetColumnInfo(1,crFram.Width()*2/3,10);
		//m_wndSplitter1.SetRowInfo(0,crFram.Height()/2,10);
		m_wndSplitter.RecalcLayout();
	 }
}
//JJC：按键控制登录和登出
void CMainFrame::OnLogin()
{
	CLOGIN login1;
	if( login1.DoModal() == IDOK)
	{    
		   CLOGIN::FlagRe = false;    //释放当前socket指针
		   CLOGIN::FlagConnect = true;//确定是否能连接
		   CLOGIN::FlagSend = false;  //确定能否发送
		   m_Greybutton =true;        //JJC：控制登录键变灰是否	
		   CLOGIN::FlagUpdate = true; //确定是否置连接按钮为灰
		   CLOGIN::Flagfirst= false;
		   //JJC：主界面要动态获得
           CChat_ServerDoc *pDoc=(CChat_ServerDoc *)CFrameWnd::GetActiveDocument();
		   pDoc->UpdateAllViews(NULL,12,NULL); 
           UpdateData(TRUE);   
           pDoc->OldNameDoc=pDoc->NameDoc; 
           pDoc->IPDoc= login1.m_IP;  
		   pDoc->NameDoc= login1.m_Name;
		   pDoc->PortDoc= login1.m_Port;
		   UpdateData(TRUE);		   
		   //JJC：更新文档，4消息
		   pDoc->UpdateAllViews(NULL,4,NULL); 
		   
	} 
}
void CMainFrame::OnLogout()
{   
	if(MessageBox(_T("确定要注销当前登录吗？"),_T("注销"),MB_ICONWARNING)==IDOK)
	{
	 m_Greybutton =false;
	 CLOGIN::FlagSend = false;
	 CLOGIN::FlagConnect = true;
	 CChatStatus::Flag_init =true;
	 CLOGIN::FlagRe = false;
     CLOGIN::FlagUpdate = true;
	 CLOGIN::Flagfirst= true;
	 UpdateData(TRUE);
	 CChat_ServerDoc *pDoc=(CChat_ServerDoc *)CFrameWnd::GetActiveDocument();
	  //JJC：更新文档，5消息
	 pDoc->UpdateAllViews(NULL,5,NULL); 

	 //关闭当前套接字
	// m_pClient1->Close(); 
	}
}
void CMainFrame::OnUpdateLogin(CCmdUI *pCmdUI)
{
	pCmdUI ->Enable(!m_Greybutton);
}
void CMainFrame::OnUpdateLogout(CCmdUI *pCmdUI)
{
	pCmdUI ->Enable(m_Greybutton);
}
//登录成功
LRESULT  CMainFrame ::OnMsgConnect(WPARAM wParam,LPARAM lParam)
{	
	/*CChat_ServerDoc *pDoc=(CChat_ServerDoc *)CFrameWnd::GetActiveDocument();
    pDoc->UpdateAllViews(NULL,11,NULL); 	*/
	return 0;
}