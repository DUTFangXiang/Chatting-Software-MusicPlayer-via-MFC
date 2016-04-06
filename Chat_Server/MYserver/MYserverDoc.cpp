
// MYserverDoc.cpp : implementation of the CMYserverDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MYserver.h"
#endif
#include "CustomSocket.h"
#include "MYserverDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CMYserverDoc
CString  CMYserverDoc::Str[500] = {_T("")};

IMPLEMENT_DYNCREATE(CMYserverDoc, CDocument)

BEGIN_MESSAGE_MAP(CMYserverDoc, CDocument)
	ON_COMMAND(ID_FILE_SAVE, &CMYserverDoc::OnFileSave)
END_MESSAGE_MAP()


// CMYserverDoc construction/destruction

CMYserverDoc::CMYserverDoc()
{
   PortDoc=5555;
   IPDoc=_T("172.0.0.1");

}

CMYserverDoc::~CMYserverDoc()
{
}

BOOL CMYserverDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMYserverDoc serialization

void CMYserverDoc::Serialize(CArchive& ar)
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
void CMYserverDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMYserverDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMYserverDoc::SetSearchContent(const CString& value)
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

// CMYserverDoc diagnostics

#ifdef _DEBUG
void CMYserverDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMYserverDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMYserverDoc commands


void CMYserverDoc::OnFileSave()
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
 for(int i=0;i< CClientSock::CountMessage;i++)
 {
   WORD unicode = 0xFEFF;  //这句重要
   file.Write(&unicode,2);  //这句重要
   file.Write(CMYserverDoc::Str[i] ,wcslen(CMYserverDoc::Str[i] )*sizeof(wchar_t));  //这句重要
   CString strEnter;
   strEnter="\r\n";
   file.Write(strEnter,4);
   }	 
 file.Close();   
}
