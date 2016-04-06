
#include "resource.h"
#include <mmsystem.h>
#pragma   comment(lib,"Winmm.lib")


// CMUSIC dialog
class CMUSIC : public CDialogEx
{
	DECLARE_DYNAMIC(CMUSIC)

public:
	CMUSIC(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMUSIC();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CListBox m_ListMusic;
	afx_msg void OnBnClickedButton2();
	static UINT m_nSerialNo;
	static CString LISTsong[100];
	static CString LISTpath[100];

	DWORD MCIOpen( const CString &strPath);
	DWORD MCIGetLength(DWORD *dwLength);
	DWORD MCIPause();
	DWORD MCIPlay();
	bool  MCIIsOpened();
	DWORD MCIGetPos(DWORD *dwPos);
	BOOL MCIIsPlaying();
	DWORD m_dwLength;
	bool  is_opened;
	int nSerialNo ;
	DWORD len;
	MCIDEVICEID m_wID;
	int OLDnSerialNo;
	bool  is_playing;
	
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CSliderCtrl m_progress;
	CString m_TimeEDIT;
	afx_msg void OnClose();
};
