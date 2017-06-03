// BiYeSheJiDoc.cpp : implementation of the CBiYeSheJiDoc class
//

#include "stdafx.h"
#include "BiYeSheJi.h"

#include "BiYeSheJiDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBiYeSheJiDoc

IMPLEMENT_DYNCREATE(CBiYeSheJiDoc, CDocument)

BEGIN_MESSAGE_MAP(CBiYeSheJiDoc, CDocument)
	//{{AFX_MSG_MAP(CBiYeSheJiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBiYeSheJiDoc construction/destruction

CBiYeSheJiDoc::CBiYeSheJiDoc()
{
	// TODO: add one-time construction code here

}

CBiYeSheJiDoc::~CBiYeSheJiDoc()
{
}

BOOL CBiYeSheJiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBiYeSheJiDoc serialization

void CBiYeSheJiDoc::Serialize(CArchive& ar)
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

/////////////////////////////////////////////////////////////////////////////
// CBiYeSheJiDoc diagnostics

#ifdef _DEBUG
void CBiYeSheJiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBiYeSheJiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBiYeSheJiDoc commands

BOOL CBiYeSheJiDoc::ReadImgFile(CString sName)
{
    if (m_hDIB != NULL)
	{
		::GlobalFree((HGLOBAL) m_hDIB);
		m_hDIB=NULL;
	}	
	if (m_palDIB != NULL)
	{
		delete m_palDIB;
		m_palDIB=NULL;
	}

	// replace calls to Serialize with ReadDIBFile function
	CFile nFile;
	if(!nFile.Open(sName,CFile::modeRead))
		return false;
	m_hDIB = ReadDIBFile(nFile);
	nFile.Close();
	InitDIBData();

	if (m_hDIB == NULL)
		return FALSE;
	return TRUE;
}

BOOL CBiYeSheJiDoc::InitDIBData()
{
    if (m_palDIB != NULL)
	{
		delete m_palDIB;
		m_palDIB = NULL;
	}
	if (m_hDIB == NULL)
	{
		return FALSE;
	}
	m_palDIB = new CPalette;
	if (m_palDIB == NULL)
	{
		// we must be really low on memory
		::GlobalFree((HGLOBAL) m_hDIB);
		m_hDIB = NULL;
		return FALSE;
	}

	if (::CreateDIBPalette(m_hDIB, m_palDIB) == NULL)
	{
		// DIB may not have a palette
		delete m_palDIB;
		m_palDIB = NULL;
	}

	return TRUE;
}

BOOL CBiYeSheJiDoc::OpenDocument(LPCTSTR lpszPathName)
{
    if (OpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	BOOL b = ReadImgFile(lpszPathName);
	if(b)
	{
		LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);
		m_sizeDoc.cx = (int) ::DIBWidth(lpDIB);         // Size of DIB - x
		m_sizeDoc.cy = (int) ::DIBHeight(lpDIB);        // Size of DIB - y
		::GlobalUnlock((HGLOBAL) m_hDIB);
	}
	POSITION pos;
	pos = GetFirstViewPosition();
	while(pos != NULL)
	{
		CScrollView * pView = (CScrollView *)GetNextView(pos);
		if(pView != NULL)
		{
			pView->SetScrollSizes(MM_TEXT, m_sizeDoc);

		}
	}
	return b;
}

BOOL CBiYeSheJiDoc::SaveDocument(LPCTSTR lpszPathName)
{
    CFile nFile;
	if(m_hDIB == NULL)
		return  false;
	nFile.Open(lpszPathName,CFile::modeWrite | CFile::modeCreate);
	SaveDIB(m_hDIB, nFile);
	nFile.Close();
	return true;
}

HDIB CBiYeSheJiDoc::GetHDIB() const
{
	return m_hDIB; 
}

CPalette* CBiYeSheJiDoc::GetDocPalette() const
{
    return m_palDIB;
}

CSize CBiYeSheJiDoc::GetDocSize() const
{
    return m_sizeDoc;
}
