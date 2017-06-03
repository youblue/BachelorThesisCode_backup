// BiYeSheJiView.h : interface of the CBiYeSheJiView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIYESHEJIVIEW_H__E707A837_A690_4722_AF3E_9EF32A9DEB90__INCLUDED_)
#define AFX_BIYESHEJIVIEW_H__E707A837_A690_4722_AF3E_9EF32A9DEB90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBiYeSheJiView : public CView
{
protected: // create from serialization only
	CBiYeSheJiView();
	DECLARE_DYNCREATE(CBiYeSheJiView)

// Attributes
public:
	CBiYeSheJiDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBiYeSheJiView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CPoint m_point;
	CPoint m_point1;
	CPoint m_Origin;
	CPoint m_Origin1;
	CPoint point2;
	CPoint point1;
	virtual ~CBiYeSheJiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBiYeSheJiView)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BiYeSheJiView.cpp
inline CBiYeSheJiDoc* CBiYeSheJiView::GetDocument()
   { return (CBiYeSheJiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIYESHEJIVIEW_H__E707A837_A690_4722_AF3E_9EF32A9DEB90__INCLUDED_)
