
// MYserverDoc.h : interface of the CMYserverDoc class
//


#pragma once


class CMYserverDoc : public CDocument
{
protected: // create from serialization only
	CMYserverDoc();
	DECLARE_DYNCREATE(CMYserverDoc)

// Attributes
public:

// Operations
public:
	unsigned int PortDoc;
	CString IPDoc;
	static CString  Str[500];
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
	virtual ~CMYserverDoc();
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
};
