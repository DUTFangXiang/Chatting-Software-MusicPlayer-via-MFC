
// Chat_ServerDoc.h : interface of the CChat_ServerDoc class
//


#pragma once


class CChat_ServerDoc : public CDocument
{
protected: // create from serialization only
	CChat_ServerDoc();
	DECLARE_DYNCREATE(CChat_ServerDoc)

// Attributes
public:
	CString EditDocument;   //JJC：Document中保存的数据
	CString IPDoc;
	CString NameDoc;
	int     PortDoc;
	CString OldNameDoc;

	static CString  Str[500];
	//CTypedPtrList<CObList,CString> m_List;
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CChat_ServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
};
