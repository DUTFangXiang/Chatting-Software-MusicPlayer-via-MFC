// MUSIC.cpp : implementation file
//

#include "stdafx.h"
#include "MYserver.h"
#include "MUSIC.h"
//#include "MyHead.h"
#include "afxdialogex.h"
//#include "MUSIC.h"


UINT CMUSIC ::m_nSerialNo=0;
CString  CMUSIC::LISTsong[100] = {_T("")};
CString  CMUSIC::LISTpath[100] = {_T("")};
// CMUSIC dialog

IMPLEMENT_DYNAMIC(CMUSIC, CDialogEx)

CMUSIC::CMUSIC(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMUSIC::IDD, pParent)
{
	m_wID                 = NULL;
	m_dwLength            = 0;
	OLDnSerialNo          = -1;
	m_TimeEDIT = _T("00:00/00:00");
	is_opened    = false;     //决定歌曲是否打开
	nSerialNo = 0;
	is_playing= false;
}

CMUSIC::~CMUSIC()
{
}

void CMUSIC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ListMusic);
	DDX_Control(pDX, IDC_SLIDER1, m_progress);
	DDX_Text(pDX, IDC_EDIT2, m_TimeEDIT);
}

BEGIN_MESSAGE_MAP(CMUSIC, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMUSIC::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMUSIC::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// 导入歌曲
void CMUSIC::OnBnClickedButton1()
{   
	//将列表框位置设到0
	m_ListMusic.SetCurSel(0);
	BOOL isOpen = TRUE;            //是否打开(否则为保存) 
	char pBuf[MAX_PATH];                           //存放路径的变量
	//LPTSTR pBuf[] = new LPTSTR[MAX_PATH];
    GetCurrentDirectory(MAX_PATH,(LPTSTR)pBuf);            //获取程序的当前目录
	//CString cspath = CString(pBuf);
    CString defaultDir;       // = cspath;  //默认打开的文件路径   
	defaultDir.Format( _T("%s"), pBuf );
    CString filter = L"*.mp3|*.mp3|*.wma|*.wma||"; 
    CFileDialog dlg1(isOpen, defaultDir, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter, this); 
	dlg1.m_ofn.lpstrInitialDir = defaultDir;  
	//CFileDialog dlg1(false,"mp3",NULL,NULL,"*.mp3|*.mp3|*.wma|*.wma||");//构造对话框
	if(IDOK == dlg1.DoModal())//调用此功能公开Windows常用文件对话框并允许用户浏览文件和目录并输入文件名
	{
		CString local_name,local_path;
		local_name = dlg1.GetFileTitle();
		local_path = dlg1.GetPathName();
	    m_nSerialNo = m_ListMusic.GetCount();
		LISTsong[m_nSerialNo] = local_name;
		LISTpath[m_nSerialNo] = local_path ;

		CString str,strOne;	
	    str.Format(_T("%03d"),m_nSerialNo+1);
		m_ListMusic.AddString(str+_T("  ")+local_name);
	}
	else
		return;
	// TODO: Add your control notification handler code here
}
//JJC：播放音乐，对应播放暂停/按键
void CMUSIC::OnBnClickedButton2()
{   
  int nIndex=m_ListMusic.GetCurSel();
  if(nIndex <0)
    {  MessageBox(_T("请先在歌曲单中选中歌曲"),_T("提示"),MB_ICONWARNING);
		return;	    }
  CString strItem;
  m_ListMusic.GetText(nIndex,strItem);
  USES_CONVERSION;
  LPSTR str1 = T2A( strItem.Mid(0,3));
  nSerialNo= atoi(str1);
  //如果歌曲没打开
  if((is_opened == false)&&(nSerialNo != OLDnSerialNo))
	{
	   OLDnSerialNo = nSerialNo;             
	   DWORD dwReturn=	MCIOpen(LISTpath[nSerialNo-1]);
	   is_opened = MCIIsOpened();
	   MCIGetLength(&len);
	   if(is_opened == false)
		{
			MessageBox(_T("你播放的歌曲不存在"),_T("提示"),MB_ICONWARNING);
			return;
			 }
	   else
	   {
		    is_playing = true;
	        MCIPlay();
	        SetTimer(3,100,NULL);
	        }
   }
 else
   {
	 if(nSerialNo != OLDnSerialNo)
	 {
	   MCI_GENERIC_PARMS mciGP;
       mciSendCommand(m_wID, MCI_CLOSE, MCI_NOTIFY|MCI_WAIT,(DWORD)(LPVOID)&mciGP);
       m_wID = NULL;
	   OLDnSerialNo = nSerialNo;             
	   DWORD dwReturn=	MCIOpen(LISTpath[nSerialNo-1]);
	   is_opened = MCIIsOpened();
	   MCIGetLength(&len);
	   if(is_opened == false)
		{
			MessageBox(_T("你播放的歌曲不存在"),_T("提示"),MB_ICONWARNING);
			return;
			 }
	   else
	   {
		    is_playing = true;
	        MCIPlay();
	        SetTimer(3,100,NULL);
	        }
	  }
	 //暂停
	 else if(is_playing)
	   {
		  is_playing = false;
	      MCIPause();
		  KillTimer(3);
	    }
	 //播放
	 else
		{
		  is_playing = true;
		  MCIPlay();
		  SetTimer(3,100,NULL);		  		  
		}
	}	 
 }
//JJC：打开歌曲
DWORD  CMUSIC::MCIOpen( const CString &strPath)
{
   MCI_OPEN_PARMS mciOP;
   DWORD dwReturn;
   ASSERT(m_wID == NULL);
  //由mci判断文件类型
  mciOP.lpstrDeviceType=NULL;
  mciOP.lpstrElementName=strPath;
  dwReturn=mciSendCommand(NULL, MCI_OPEN, 
	        MCI_OPEN_ELEMENT | MCI_WAIT | MCI_OPEN_SHAREABLE,(DWORD)(LPVOID)&mciOP);
  if (dwReturn==0)
  {
	m_wID=mciOP.wDeviceID;
   if (this->MCIGetLength(&m_dwLength)!=0)
       m_dwLength=0;
    }
  else
    m_wID=NULL;
  return dwReturn;
}
//JJC：获得歌曲长度
DWORD CMUSIC::MCIGetLength(DWORD *dwLength)	
{
	MCI_STATUS_PARMS mciSP;
    mciSP.dwItem=MCI_STATUS_LENGTH;
    DWORD dwReturn=mciSendCommand(m_wID, MCI_STATUS, MCI_STATUS_ITEM,
    (DWORD)(LPVOID)&mciSP);
    if (dwReturn==0)
       *dwLength=mciSP.dwReturn/1000;
    return dwReturn;
}
//用mci命令询问有否文件打开
bool CMUSIC::MCIIsOpened()
{
	MCI_STATUS_PARMS mciSP;
	mciSP.dwItem=MCI_STATUS_MODE;
	DWORD dwReturn=mciSendCommand(m_wID, MCI_STATUS, MCI_STATUS_ITEM,(DWORD)(LPVOID)&mciSP);
	if (dwReturn==(DWORD)0)
	if (mciSP.dwReturn==MCI_MODE_OPEN ||mciSP.dwReturn==MCI_MODE_PLAY ||
			mciSP.dwReturn==MCI_MODE_PAUSE ||mciSP.dwReturn==MCI_MODE_STOP||mciSP.dwReturn==MCI_MODE_SEEK)
		return true;
	return false;
}
//播放命令
DWORD CMUSIC::MCIPlay()

{
	MCI_PLAY_PARMS mciPP;
	
	return mciSendCommand(m_wID, MCI_PLAY, MCI_NOTIFY,(DWORD)(LPVOID)&mciPP);
}
//暂停命令
DWORD CMUSIC::MCIPause()
{
  MCI_GENERIC_PARMS mciGP;
  KillTimer(0);
  return mciSendCommand(m_wID, MCI_PAUSE, MCI_NOTIFY|MCI_WAIT,(DWORD)(LPVOID)&mciGP);
}
//JJC：获取当前歌曲时间的位置
DWORD CMUSIC::MCIGetPos(DWORD *dwPos)
{
	MCI_STATUS_PARMS mciSP;
	mciSP.dwItem=MCI_STATUS_POSITION;
	DWORD dwReturn=mciSendCommand(m_wID, MCI_STATUS, MCI_STATUS_ITEM,(DWORD)(LPVOID)&mciSP);
	if (dwReturn==0)
		*dwPos=mciSP.dwReturn/1000;
	return dwReturn;
}
//JJC：定时器打开
void CMUSIC::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 3){
	DWORD curlen;
	if(!MCIIsOpened() || !MCIIsPlaying())
		return;
	if(0 == MCIGetPos(&curlen))
		{
			m_TimeEDIT.Format(_T("%d:%d/%d:%d"),curlen / 60,curlen % 60,len/ 60,len % 60);
			m_progress.SetRange(0,len);
     		m_progress.SetPos(curlen) ;
			if(curlen == len)
				 MCIPause();
		}
	}
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
	CDialogEx::OnTimer(nIDEvent);
}
//用mci命令询问是否正在播放
BOOL CMUSIC::MCIIsPlaying()
{
	MCI_STATUS_PARMS mciSP;
	mciSP.dwItem=MCI_STATUS_MODE;
	DWORD dwReturn=mciSendCommand(m_wID, MCI_STATUS, MCI_STATUS_ITEM,
	(DWORD)(LPVOID)&mciSP);
	if (dwReturn==0)
	if (mciSP.dwReturn==MCI_MODE_PLAY)
	return true;

	return false;
}
//关闭歌曲
void CMUSIC::OnClose()
{
   if(nSerialNo)
   {
     MCI_GENERIC_PARMS mciGP;
     mciSendCommand(m_wID, MCI_CLOSE, MCI_NOTIFY|MCI_WAIT,(DWORD)(LPVOID)&mciGP);
     m_wID = NULL;
     }
	CDialogEx::OnClose();
}
