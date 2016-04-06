#ifndef __MYHEAD_H__
#define __MYHEAD_H__

#define MSG_ACCEPT		WM_USER+1
#define MSG_RECEIVE  	WM_USER+2

CString int2Cstr(int m_int);
CString getTIME();


class CMYserverApp;
class CMYserverDoc;
class CMYserverView;
class CMainFrame;
class CCustomSocket;
class CClientSock;
//class CMUSIC;


#include <afxpriv.h>
#include "MainFrm.h"
#include "MYserver.h"
#include "MYserverView.h"
#include "MYserverDoc.h"
#include "CustomSocket.h"
//#include "MUSIC.h"

#endif