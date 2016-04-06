
// Chat_ServerView.cpp : implementation of the CChat_ServerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
//#ifndef SHARED_HANDLERS
//#include "Chat_Server.h"
//#endif

//#include "Chat_ServerDoc.h"
//#include "Chat_ServerView.h"
#include "MyHead.h"
#include "Chat_ServerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CChat_ServerView

IMPLEMENT_DYNCREATE(CChat_ServerView, CFormView)

BEGIN_MESSAGE_MAP(CChat_ServerView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_FONT, &CChat_ServerView::OnBnClickedFont)
	ON_BN_CLICKED(IDC_CLEAR, &CChat_ServerView::OnBnClickedClear)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SEND, &CChat_ServerView::OnBnClickedSend)
	ON_BN_CLICKED(IDC_BUTTON1, &CChat_ServerView::OnBnClickedButton1)
END_MESSAGE_MAP()

// CChat_ServerView construction/destruction

CChat_ServerView::CChat_ServerView()
	: CFormView(CChat_ServerView::IDD)
{
	//m_EditNovel = _T("");
}

CChat_ServerView::~CChat_ServerView()
{
	m_pClient.Close();
}

void CChat_ServerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_EDIT1);
	DDX_Text(pDX, IDC_EDIT1, m_EditNovel);
	DDX_Control(pDX, IDC_CLEAR, m_Connect);
}

//BOOL CChat_ServerView::PreCreateWindow(CREATESTRUCT& cs)
//{
//	// TODO: Modify the Window class or styles here by modifying
//	//  the CREATESTRUCT cs
//
//	return CFormView::PreCreateWindow(cs);
//}
void CChat_ServerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	//J：给控件提示
	EnableToolTips(TRUE);//enable use it
    m_ctrlTT.Create(this);
    m_ctrlTT.Activate(TRUE);
    m_ctrlTT.SetTipTextColor(RGB(255,255,0)); //font color
    m_ctrlTT.SetDelayTime(300);               //delay time
    m_ctrlTT.AddTool(GetDlgItem(IDC_SEND),_T("按Enter键发送"));
	m_ctrlTT.AddTool(GetDlgItem(IDC_CLEAR),_T("按Delete键清空"));
	m_ctrlTT.AddTool(GetDlgItem(IDC_FONT),_T("修改编辑框字体"));
}

void CChat_ServerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CChat_ServerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}
// CChat_ServerView diagnostics

#ifdef _DEBUG
void CChat_ServerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CChat_ServerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CChat_ServerDoc* CChat_ServerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChat_ServerDoc)));
	return (CChat_ServerDoc*)m_pDocument;
}
#endif //_DEBUG
//设立定时器1
int CChat_ServerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetTimer(1,500,NULL);
	return 0;
}
//JJC：状态栏显示时间
void CChat_ServerView::OnTimer(UINT_PTR nIDEvent)
{   
	CMainFrame* pMain=(CMainFrame*)AfxGetMainWnd();
	pMain->m_wndStatusBar.SetPaneInfo(0,ID_SEPARATOR,SBPS_NORMAL,300);
	pMain->m_wndStatusBar.SetPaneInfo(1,ID_SEPARATOR,SBPS_NORMAL,300);
	CString str = ::getTIME();
	pMain->m_wndStatusBar.SetPaneText(1,str); 
	//发送连接的消息
	if((CLOGIN::FlagUpdate == true)&&(CLOGIN::FlagRe == false)&&(m_pClient!=INVALID_SOCKET))
	{
	  CLOGIN::FlagRe = true;
	  CLOGIN::FlagSend = false;
	  CChat_ServerDoc* pDoc =( CChat_ServerDoc*) GetDocument();	     
	  CString cs("");
	  //char str[600]={0};
	  cs= _T("1234567890")+pDoc->OldNameDoc +getTIME()+ _T("： 退出当前会话");
	  USES_CONVERSION;
      LPSTR str = T2A(cs);
	  m_pClient.Send(str,strlen(str));
	  //释放指针
	  m_pClient.Close();
	 }
	if((CLOGIN::FlagSend == false)&&(CLOGIN::FlagConnect == true)&&(m_pClient!=INVALID_SOCKET))
	{
      CLOGIN::FlagUpdate = false;
	  CLOGIN::FlagConnect = false;
	  CLOGIN::FlagSend = true;
	  CChat_ServerDoc* pDoc =( CChat_ServerDoc*) GetDocument();
	  pDoc->UpdateAllViews(NULL,13,NULL); 
	  CString cs("");
	  //char str[600]={0};
	  cs=_T("1234567891")+ pDoc->NameDoc + getTIME()+_T("： 加入当前会话");
	  USES_CONVERSION;
      LPSTR str1 = T2A(cs);
	  m_pClient.Send(str1,strlen(str1));
	  }

	CFormView::OnTimer(nIDEvent);
}
//接收到的数据
void CChat_ServerView::OnRcv()
{
   char rcvBuf[513] = {0};
   int nRcved = 0;
   nRcved = m_pClient.Receive(rcvBuf,512,0);
   CString cs(rcvBuf);
   if(cs)
   {
	if(cs.Mid(0,10) == _T("1234567892") )
	  {
		MessageBox(_T("服务器已下线"),_T("提示"),MB_OK|MB_ICONWARNING);
		CLOGIN::FlagUpdate = true;
	   }
	else
	  {
		CChat_ServerDoc* pDoc =( CChat_ServerDoc*) GetDocument();
		pDoc->EditDocument=cs;
		UpdateData();
		pDoc->UpdateAllViews(NULL,15,NULL);
	    }
    }
  }
//JJC：响应修改字体
void CChat_ServerView::OnBnClickedFont()
{	
	CFontDialog fontDlg;   
	if (IDOK == fontDlg.DoModal())     // 显示字体对话框   
    {   
        // 如果m_font已经关联了一个字体资源对象，则释放它   
        if (m_font.m_hObject)   
        {   
            m_font.DeleteObject();   
        }   
        // 使用选定字体的LOGFONT创建新的字体   
        m_font.CreateFontIndirect(fontDlg.m_cf.lpLogFont);   
        // 获取编辑框IDC_FONT_EDIT的CWnd指针，并设置其字体   
        GetDlgItem(IDC_EDIT1)->SetFont(&m_font);  
		color = fontDlg.GetColor();   //获得选择的颜色 
	 } 	 
}
//JJC：连接按钮
void CChat_ServerView::OnBnClickedClear()
{
  if((CLOGIN::FlagUpdate == true))
  {
	CLOGIN::FlagUpdate = false;
	if(m_pClient) m_pClient.Close();
    CChat_ServerDoc* pDoc =( CChat_ServerDoc*) GetDocument();  	
	pDoc->IPDoc=_T("127.0.0.1");
	pDoc->PortDoc=5555;		
	if(CLOGIN::Flagfirst== true)
	{   		
	   pDoc->NameDoc=_T("姜佳成");
	}
	CLOGIN::Flagfirst= false;
	UpdateData(TRUE);
	//m_pClient=new CustomSocket;
	m_pClient.Create();
	m_pClient.Bind(3354,_T("localhost"));
	m_pClient.Connect(pDoc->IPDoc,pDoc->PortDoc);
   }
  else
    MessageBox(_T("当前已进入连接状态，请重新登录再连接"),_T("提示"),MB_OK|MB_ICONWARNING);
 }

//JJC：改变编辑框中文字颜色
HBRUSH CChat_ServerView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	 if(nCtlColor == CTLCOLOR_EDIT)  
        pDC->SetTextColor(color); //初始化颜色 
	return hbr;
}
//JJC：发送按钮响应发送数据到DOC里面
void CChat_ServerView::OnBnClickedSend()
{
  if(CLOGIN::FlagSend == true)
  {
   UpdateData(TRUE);
   if(m_EditNovel.Compare(_T("")) == 0 )
   { MessageBox(_T("您不可以发送为空"),_T("提示"),MB_OK|MB_ICONWARNING);}
   else
   { CChat_ServerDoc* pDoc =( CChat_ServerDoc*) GetDocument();
     UpdateData(TRUE);
     CString str = ::getTIME();
	 pDoc->EditDocument= pDoc->NameDoc+ _T("：") + str + m_EditNovel;  //结合时间+文档  将编辑框中内容保存到文档EditDocument中
     OnBnClickedButton1();         
     pDoc->UpdateAllViews(NULL,1,NULL); 
   	 USES_CONVERSION;
     LPSTR str1 = T2A( pDoc->EditDocument );
	 m_pClient.Send(str1,strlen(str1));}
    }
   else
   {
	CChat_ServerDoc* pDoc =( CChat_ServerDoc*) GetDocument();
	pDoc->UpdateAllViews(NULL,2,NULL);
    MessageBox(_T("请先点击连接，未能成功连接请修改登录"),_T("提示"),MB_OK|MB_ICONWARNING);
     }
}
//JJC：Enter键重载为发送
BOOL CChat_ServerView::PreTranslateMessage(MSG* pMsg)
{
	m_ctrlTT.RelayEvent(pMsg);   //响应控件提示

	if(pMsg->message == WM_KEYDOWN)
	{
	  if (  GetDlgItem(IDC_EDIT1) == GetFocus())        //JJC：当且仅当鼠标在编辑框中
		{
          switch(pMsg->wParam)
		   {
		     case VK_RETURN:
				 { OnBnClickedSend();   return true;}	//JJC：响应“发送”按钮
		  }	}
	}
	return CFormView::PreTranslateMessage(pMsg);
}
//JJC： 获得时间
CString getTIME()
{
	//获取时间
   	CString str;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str.Format(_T("（%04d-%02d-%02d %02d:%02d:%02d）"),
		st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	
	return str;
}
//JJC：清空功能
void CChat_ServerView::OnBnClickedButton1()
{
	m_EDIT1.SetSel(0, -1);
    m_EDIT1.Clear();   //清空数据
    m_EDIT1.GetFocus();//再次获得焦点
}
