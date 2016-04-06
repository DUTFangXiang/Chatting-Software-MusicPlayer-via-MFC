#pragma once

#include "resource.h"
// CLOGIN dialog
CString getTIME();

class CLOGIN : public CDialogEx
{
	DECLARE_DYNAMIC(CLOGIN)

public:
	CLOGIN(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLOGIN();

// Dialog Data
	enum { IDD = IDD_LoginON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_IP;
	CString m_Name;
	int m_Port;
	static bool FlagSend;
	static bool FlagConnect;
	static bool FlagUpdate;
	static bool FlagRe;
	static bool Flagfirst;
	CStatic m_ImageUSER;
};
