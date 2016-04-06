
#ifndef __MYHEAD_H__
#define __MYHEAD_H__

	#define MSG_ACCEPT		WM_USER+1
	#define MSG_CONNECT     WM_USER+2

	
	class CChat_ServerApp;
	class CChat_ServerDoc;
	class CChat_ServerView;
	class CMainFrame;
	class CSecondDlg;
	class CustomSocket;
	class CChatStatus;
	class CLOGIN;

	#include <afxpriv.h>
	#include "resource.h"
	#include "CustomSocket.h"
	#include "LOGIN.h"          // JJC： 头文件都放这里
	#include "MainFrm.h"
	#include "Chat_Server.h"
	#include "Chat_ServerView.h"
	#include "Chat_ServerDoc.h"
	#include "SecondDlg.h"
	#include "CthirdDlg.h"


#endif