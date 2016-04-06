
// Chat_ServerDoc.cpp : implementation of the CChat_ServerDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Chat_Server.h"
#endif

#include "Chat_ServerDoc.h"
#include "LOGIN.h"
#include "SecondDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString  CChat_ServerDoc::Str[500] = {_T("")};
// CChat_ServerDoc

IMPLEMENT_DYNCREATE(CChat_ServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CChat_ServerDoc, CDocument)
	ON_COMMAND(ID_FILE_SAVE, &CChat_ServerDoc::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CChat_ServerDoc::OnFileSaveAs)
END_MESSAGE_MAP()

CChat_ServerDoc::CChat_ServerDoc()
{
	EditDocument = "";
    IPDoc = "";
	NameDoc = "";
	PortDoc = 0;
	for(int i=0 ; i<500;i++)
	   Str[i] = _T("");
}

CChat_ServerDoc::~CChat_ServerDoc()
{
}

BOOL CChat_ServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


// CChat_ServerDoc serialization

void CChat_ServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CChat_ServerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CChat_ServerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CChat_ServerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CChat_ServerDoc diagnostics

#ifdef _DEBUG
void CChat_ServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CChat_ServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CChat_ServerDoc commands


void CChat_ServerDoc::OnFileSave()
{
 CString str;
 SYSTEMTIME st;
 GetLocalTime(&st);
 str.Format(_T("%04d_%02d_%02d %02d_%02d_%02d"),
 st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);

 BOOL isOpen = FALSE;        //是否打开(否则为保存)  
 CString defaultDir = L"D:\\";   //默认打开的文件路径  
 CString fileName = str +L"Chat.txt";         //默认打开的文件名  
 CString filter = L"TXT File(*.txt)|*.txt|Doc File(*.doc; *.ppt; *.xls)|*.doc;*.ppt;*.xls|All Files(*.*)|*.*||"; 
 CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter, NULL);  
 openFileDlg.GetOFN().lpstrInitialDir =L"D:\\CHAT\\chat.txt";//defaultDir+ fileName;  
 CString filePath = defaultDir + "\\" + fileName; 
 INT_PTR result = openFileDlg.DoModal();  
 if(result == IDOK) {  
	filePath = openFileDlg.GetPathName(); }  
 //往文档里写入
 CFile file(filePath,CFile::modeWrite|CFile::modeCreate);
 if(!file)return;                     //没有打开什么也不做！
 for(int i=0;i< CSecondDlg::CountMessage;i++)
 {
   WORD unicode = 0xFEFF;  //这句重要
   file.Write(&unicode,2);  //这句重要
   file.Write(CChat_ServerDoc::Str[i] ,wcslen(CChat_ServerDoc::Str[i] )*sizeof(wchar_t));  //这句重要
   CString strEnter;
   strEnter="\r\n";
   file.Write(strEnter,4);
   }	 
 file.Close();                        
}

void CChat_ServerDoc::OnFileSaveAs()
{
	CString str;
 SYSTEMTIME st;
 GetLocalTime(&st);
 str.Format(_T("%04d_%02d_%02d %02d_%02d_%02d"),
 st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);

 BOOL isOpen = FALSE;        //是否打开(否则为保存)  
 CString defaultDir = L"D:\\";   //默认打开的文件路径  
 CString fileName = str +L"Chat.txt";         //默认打开的文件名  
 CString filter = L"TXT File(*.txt)|*.txt|Doc File(*.doc; *.ppt; *.xls)|*.doc;*.ppt;*.xls|All Files(*.*)|*.*||"; 
 CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter, NULL);  
 openFileDlg.GetOFN().lpstrInitialDir =L"D:\\CHAT\\chat.txt";//defaultDir+ fileName;  
 CString filePath = defaultDir + "\\" + fileName; 
 INT_PTR result = openFileDlg.DoModal();  
 if(result == IDOK) {  
	filePath = openFileDlg.GetPathName(); }  
 //往文档里写入
 CFile file(filePath,CFile::modeWrite|CFile::modeCreate);
 if(!file)return;                     //没有打开什么也不做！
 for(int i=0;i< CSecondDlg::CountMessage;i++)
 {
   //将数据保存为正常的中文
   WORD unicode = 0xFEFF;  
   file.Write(&unicode,2);  
   file.Write(CChat_ServerDoc::Str[i] ,wcslen(CChat_ServerDoc::Str[i] )*sizeof(wchar_t));  
   CString strEnter;
   strEnter="\r\n";
   file.Write(strEnter,4);
	   }	 
 file.Close();   
}
