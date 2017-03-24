
#include "stdafx.h"
#include "Chat_Server.h"
#include "CthirdDlg.h"
#include "LOGIN.h"

// CChatStatus
//���Ƶ�3����������ʾ���ͻ���״̬��
bool CChatStatus::Flag_init = true;

IMPLEMENT_DYNCREATE(CChatStatus, CFormView)

CChatStatus::CChatStatus()
	: CFormView(CChatStatus::IDD)
{

}

CChatStatus::~CChatStatus()
{
}

void CChatStatus::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ChatStatus);
}

BEGIN_MESSAGE_MAP(CChatStatus, CFormView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CChatStatus diagnostics

#ifdef _DEBUG
void CChatStatus::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CChatStatus::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CChatStatus message handlers
//JJC�����µ������ڵ����ݺ�״̬
void CChatStatus::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	//
	if( (CChatStatus::Flag_init ==true)&&(CLOGIN::FlagSend == false))
	{
	   //JJC����ս���
	   m_ChatStatus.ResetContent();
	   m_ChatStatus.AddString(_T("                        "));
	   m_ChatStatus.AddString(_T("                   �ͻ���״̬        "));
	   m_ChatStatus.AddString(_T("*****************************"));
	   m_ChatStatus.AddString(_T("                        "));
	   m_ChatStatus.AddString(_T("��ǰ��¼״̬��172.0.0.1 "));
	   m_ChatStatus.AddString(_T("�˿ڣ�5555 "));
	   m_ChatStatus.AddString(_T("�ͻ������ѳ� "));	   
	   m_ChatStatus.AddString(_T("***ϵͳ��ʾ���������ӷ�����****"));
	   m_ChatStatus.AddString(_T("                        "));
	   m_ChatStatus.AddString(_T("�ɵ����¼�˵����ĵ�¼IP����Ϣ"));
	   m_ChatStatus.AddString(_T("                        "));

	   CChatStatus::Flag_init = false;
	}

	if((CLOGIN::FlagSend == false)&&(lHint == 5))
	{
	  CChat_ServerDoc* pDoc = GetDocument();
	    ASSERT_VALID(pDoc);
	  m_ChatStatus.AddString(pDoc->NameDoc + _T("��  �˳���ǰ�Ự"));
	  m_ChatStatus.AddString(_T("                        "));
	
	 }

	if((CLOGIN::FlagSend == false)&&(lHint == 2))
	{
	    m_ChatStatus.AddString(_T("*****************************"));
	    m_ChatStatus.AddString(_T("******ϵͳ��ʾ����������******"));
		m_ChatStatus.AddString(_T("�ɵ����¼�˵����ĵ�¼IP����Ϣ"));
		m_ChatStatus.AddString(_T("*****************************"));
		m_ChatStatus.AddString(_T("                        "));
	 }

	if((CLOGIN::FlagSend == false)&&(lHint == 3))
	{
	    m_ChatStatus.AddString(_T("*****************************"));
	    m_ChatStatus.AddString(_T("****��¼ʧ�ܣ������µ�¼*****"));
		m_ChatStatus.AddString(_T("                        "));
	 }
	//��¼ʱ����Ϣ����
	if(lHint == 11)
	{
	    m_ChatStatus.AddString(_T("****���Ѿ��ɹ���¼*****"));
		m_ChatStatus.AddString(_T("                        "));
        CChat_ServerDoc* pDoc = GetDocument();
	    ASSERT_VALID(pDoc);
		m_ChatStatus.AddString(pDoc->NameDoc + _T("��  has just joined the talk"));
	 }
	//��¼ʱ����Ϣ����
	if(lHint == 12)
	{
        CChat_ServerDoc* pDoc = GetDocument();
	    ASSERT_VALID(pDoc);
		m_ChatStatus.AddString(pDoc->NameDoc + _T("��  �˳���ǰ�Ự"));
	    m_ChatStatus.AddString(_T("                        "));
	 }
	//��¼ʱ����Ϣ����
	if(lHint == 13)
	{
        CChat_ServerDoc* pDoc = GetDocument();
	    ASSERT_VALID(pDoc);
		m_ChatStatus.AddString(pDoc->NameDoc + _T("��  ���뵱ǰ�Ự"));
	    m_ChatStatus.AddString(_T("                        "));
	 }

	if(lHint == 4)
	{		 
		CChat_ServerDoc* pDoc = GetDocument();
	    ASSERT_VALID(pDoc);
		m_ChatStatus.AddString(_T("����ǰ��ϢΪ��")+pDoc->IPDoc+_T("����"));
		m_ChatStatus.AddString(_T("                       "));
		CString cs;
		cs.Format(_T("%d"),pDoc->PortDoc);
		m_ChatStatus.AddString(_T("�˿ںţ�")+cs+_T("     ��¼�ˣ�")+pDoc->NameDoc);
		m_ChatStatus.AddString(_T("                       "));
	}
	else
	{
		Invalidate();
	}
}


