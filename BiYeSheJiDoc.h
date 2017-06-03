// BiYeSheJiDoc.h : interface of the CBiYeSheJiDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIYESHEJIDOC_H__1FDD1DF6_0CBE_4AE6_98F8_31F10EE787AB__INCLUDED_)
#define AFX_BIYESHEJIDOC_H__1FDD1DF6_0CBE_4AE6_98F8_31F10EE787AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBiYeSheJiDoc : public CDocument
{
protected: // create from serialization only
	CBiYeSheJiDoc();
	DECLARE_DYNCREATE(CBiYeSheJiDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBiYeSheJiDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CSize GetDocSize() const;
	CPalette* GetDocPalette() const;
	HDIB GetHDIB() const;
	BOOL SaveDocument(LPCTSTR lpszPathName);
	BOOL OpenDocument(LPCTSTR lpszPathName);
	BOOL InitDIBData();
	CPalette* m_palDIB;
	CSize m_sizeDoc;
	HDIB m_hDIB;
	BOOL ReadImgFile(CString sName);
	virtual ~CBiYeSheJiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBiYeSheJiDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIYESHEJIDOC_H__1FDD1DF6_0CBE_4AE6_98F8_31F10EE787AB__INCLUDED_)
