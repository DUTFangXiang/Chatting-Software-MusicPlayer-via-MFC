
// MYserverView.cpp : implementation of the CMYserverView class
//

#include "stdafx.h"
#include "MyHead.h"
#include "MYserverView.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
//#ifndef SHARED_HANDLERS
//#include "MYserver.h"
//#endif
//
//#include "MYserverDoc.h"
//#include "MYserverView.h"
//
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

bool CMYserverView::FlagSend =false;
int CMYserverView::NUMpeople=0;

// CMYserverView

IMPLEMENT_DYNCREATE(CMYserverView, CFormView)

BEGIN_MESSAGE_MAP(CMYserverView, CFormView)
	ON_MESSAGE(MSG_ACCEPT,OnMsgConnect)  //JJC：自己写的接受消息映射
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON1, &CMYserverView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CMYserverView::OnBnClickedButton4)
	ON_COMMAND(ID_REPORT, &CMYserverView::OnReport)
	ON_COMMAND(ID_STOPLISTEN, &CMYserverView::OnStoplisten)
	ON_UPDATE_COMMAND_UI(ID_REPORT, &CMYserverView::OnUpdateReport)
	ON_UPDATE_COMMAND_UI(ID_STOPLISTEN, &CMYserverView::OnUpdateStoplisten)
	ON_BN_CLICKED(IDC_BUTTON2, &CMYserverView::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CMYserverView::OnBnClickedButton3)
END_MESSAGE_MAP()

// CMYserverView construction/destruction

CMYserverView::CMYserverView()
	: CFormView(CMYserverView::IDD)
{
	m_PORT = 5555;
	m_Greybutton=false;
	m_EDITSEND = _T("按Enter键发送");
}

CMYserverView::~CMYserverView()
{
}

void CMYserverView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_PORT);
	DDV_MinMaxInt(pDX, m_PORT, 5000, 10000);
	DDX_Control(pDX, IDC_LIST1, m_ListChat);
	DDX_Text(pDX, IDC_EDIT3, m_EDITSEND);
	DDX_Control(pDX, IDC_EDIT3, m_EDITSEND1);
}

BOOL CMYserverView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMYserverView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	//开启定时
	SetTimer(1,300,NULL);
}

void CMYserverView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMYserverView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMYserverView diagnostics

#ifdef _DEBUG
void CMYserverView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMYserverView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMYserverDoc* CMYserverView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMYserverDoc)));
	return (CMYserverDoc*)m_pDocument;
}
#endif //_DEBUG

/********JJC：开启监听**************/
/************************************/
void CMYserverView::OnBnClickedButton1()
{  
	m_ListChat.ResetContent();
	if(m_pListener.m_hSocket !=INVALID_SOCKET)
	   m_pListener.Close();
	else
	{
		 if(! m_pListener.Create(m_PORT,SOCK_STREAM,FD_READ |
			       FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE))
		  {
			m_ListChat.AddString(_T("")); 
		    m_ListChat.AddString(_T("端口被占用，请重新建立服务器"));
			m_ListChat.AddString(_T("")); 
			m_pListener.Close(); 
			return;
		  }
		 else
		  {
			m_ListChat.AddString(_T(""));
		    m_ListChat.AddString(_T("您已经成功创建服务器"));
			m_ListChat.AddString(_T(""));
		  }
		 if(!m_pListener.Listen())//如果监听失败  
		  {  
			int nErrorCode =m_pListener.GetLastError();    //检测错误信息  
			if(nErrorCode !=WSAEWOULDBLOCK)             //如果不是线程阻塞  
			{  
			  m_ListChat.AddString(_T("")); 
		      m_ListChat.AddString(_T("Socket监听出错!"));
			  m_ListChat.AddString(_T("")); 
			  m_pListener.Close(); 
			  PostQuitMessage(0);
			  return;
			 } 
		   } 
		 else
		 {
		    m_ListChat.AddString(_T("已经启动监听，端口号： ")+int2Cstr(m_PORT));
		    m_ListChat.AddString(_T(""));
			GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	        GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);	
			/*OnUpdateReport(CCmdUI *pCmdUI)
            OnUpdateStoplisten(CCmdUI *pCmdUI)*/
		  }
	 }
}
/********JJC：关闭Socket**************/
/**************************************/
void CMYserverView::OnBnClickedButton4()
{
	CMYserverView::FlagSend = false;
	m_ListChat.ResetContent();
	USES_CONVERSION;
	if( CMYserverView::NUMpeople !=0)
	{
      LPSTR str1 = T2A(_T("1234567892服务器断开连接！"));
      m_Sender ->Send(str1,strlen(str1));
	  }
	m_pListener.Close();
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
}

/*****JJC：int转换为CString类型*****/
/************************************/
CString int2Cstr(int m_int)
{
	CString cs;
	cs.Format(_T("%d"),m_int);
	return cs;
  }
//接收消息
LRESULT  CMYserverView ::OnMsgConnect(WPARAM wParam,LPARAM lParam)
{
	return 0;
}
void CMYserverView::OnStau(CClientSock* pConn2)
{
	m_Sender = pConn2;

 }
//收到数据原数据返回
void CMYserverView::OnRcv(CClientSock* pConn)
{
	if (NULL != pConn)
	{
		char rcvBuf[513] = {0};
		int nRcved = 0;
		nRcved = pConn->Receive(rcvBuf,512,0);
		CString cs(rcvBuf);
		if(cs.Mid(0,10)==_T("1234567891"))
		{
		  m_ListChat.AddString(cs.Mid(10,cs.GetLength()-10));
		  m_ListChat.AddString(_T(""));
		  CMYserverView::FlagSend = true; //将发送至true
		  CMYserverView::NUMpeople++;
		 }
		else if(cs.Mid(0,10)==_T("1234567890"))
		{
		  m_ListChat.AddString(cs.Mid(10,cs.GetLength()-10));
		  m_ListChat.AddString(_T(""));
		  CMYserverView::NUMpeople--;
		  pConn->Close();
		  
		  if(CMYserverView::NUMpeople <= 0)
		       CMYserverView::FlagSend = false;
		}
		else
		{
		  m_ListChat.AddString(cs);
		  m_ListChat.AddString(_T(""));
		  CMYserverView::FlagSend = true; 
		  }
	}
}
void CMYserverView::OnSendMy(CClientSock* pConn1)
{
  if(CMYserverView::FlagSend == true)
  {
  CString str = ::getTIME();
  CString SendStr = _T("大工服务器：") + str + m_EDITSEND;  
  m_ListChat.AddString(SendStr);
  m_ListChat.AddString(_T(""));
  OnBnClickedClear(); 
  USES_CONVERSION;
  LPSTR str1 = T2A( SendStr );
  pConn1->Send(str1,strlen(str1));
   }
 }
//JJC：菜单中监听
void CMYserverView::OnReport()
{
	m_Greybutton =true;
	OnBnClickedButton1();
}
//JJC：菜单中停止监听
void CMYserverView::OnStoplisten()
{
	m_Greybutton =false;
	OnBnClickedButton4();
}
void CMYserverView::OnUpdateReport(CCmdUI *pCmdUI)
{
	 pCmdUI ->Enable(!m_Greybutton);
}
void CMYserverView::OnUpdateStoplisten(CCmdUI *pCmdUI)
{
	 pCmdUI ->Enable(m_Greybutton);
}
//JJC：发送
void CMYserverView::OnBnClickedButton2()
{
  if(CMYserverView::FlagSend == true)
  {
   UpdateData(TRUE);
   if( m_EDITSEND.Compare(_T("")) == 0 )
   { MessageBox(_T("您不可以发送为空"),_T("提示"),MB_OK|MB_ICONWARNING);}
   else
   { 
      m_Sender->AsyncSelect(FD_WRITE);  
    }
  }
  else
  {  MessageBox(_T("等待客户端连接才可以发送"),_T("提示"),MB_OK|MB_ICONWARNING);}
}
//JJC：Enter键重载为发送
BOOL CMYserverView::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
	  if (  GetDlgItem(IDC_EDIT3) == GetFocus())        //JJC：当且仅当鼠标在编辑框中
		{
          switch(pMsg->wParam)
		   {
		     case VK_RETURN:
				 { OnBnClickedButton2();   return true;}	//JJC：响应“发送”按钮
		   } }	}
	return CFormView::PreTranslateMessage(pMsg);
}
//JJC： 获得时间
CString getTIME()
{
   	CString str;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str.Format(_T("（%04d-%02d-%02d %02d:%02d:%02d）"),
		st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);	
	return str;
}
//JJC：清空按钮
void CMYserverView::OnBnClickedClear()
{
	m_EDITSEND1.SetSel(0, -1);
    m_EDITSEND1.Clear();   //清空数据
    m_EDITSEND1.GetFocus();//再次获得焦点
}

void CMYserverView::OnTimer(UINT_PTR nIDEvent)
{
	CMainFrame* pMain=(CMainFrame*)AfxGetMainWnd();
	pMain->m_wndStatusBar.SetPaneInfo(0,ID_SEPARATOR,SBPS_NORMAL,200);
	pMain->m_wndStatusBar.SetPaneInfo(1,ID_SEPARATOR,SBPS_NORMAL,200);
	pMain->m_wndStatusBar.SetPaneInfo(2,ID_SEPARATOR,SBPS_NORMAL,200);
	CString str = ::getTIME();
	pMain->m_wndStatusBar.SetPaneText(1,str);  //m_wndStatusBar定义是protected里面，需要修改
	                                           //1是状态栏下面第二块显示
	CString cs;
	cs.Format(_T("%d"),CMYserverView::NUMpeople);
	pMain->m_wndStatusBar.SetPaneText(2,_T("当前连接人数：")+cs);
	CFormView::OnTimer(nIDEvent);
	//用于保存作用
	CMYserverDoc* pDoc = ( CMYserverDoc*) GetDocument();	
	int nSel = m_ListChat.GetCount();	
    CClientSock::CountMessage = nSel;         
    for( int i=0; i< nSel; i++ ){
       m_ListChat.GetText(i ,pDoc->Str[i]);
		 }
}
//音乐播放器按钮
void CMYserverView::OnBnClickedButton3()
{
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	p ->OnMusic();
}
