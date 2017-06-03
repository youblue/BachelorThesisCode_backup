// BiYeSheJiView.cpp : implementation of the CBiYeSheJiView class
//

#include "stdafx.h"
#include "BiYeSheJi.h"

#include "BiYeSheJiDoc.h"
#include "BiYeSheJiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBiYeSheJiView

IMPLEMENT_DYNCREATE(CBiYeSheJiView, CView)

BEGIN_MESSAGE_MAP(CBiYeSheJiView, CView)
	//{{AFX_MSG_MAP(CBiYeSheJiView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBiYeSheJiView construction/destruction

CBiYeSheJiView::CBiYeSheJiView()
{
	// TODO: add construction code here

}

CBiYeSheJiView::~CBiYeSheJiView()
{
}

BOOL CBiYeSheJiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBiYeSheJiView drawing

void CBiYeSheJiView::OnDraw(CDC* pDC)
{
	CBiYeSheJiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CBiYeSheJiView printing

BOOL CBiYeSheJiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBiYeSheJiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBiYeSheJiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBiYeSheJiView diagnostics

#ifdef _DEBUG
void CBiYeSheJiView::AssertValid() const
{
	CView::AssertValid();
}

void CBiYeSheJiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBiYeSheJiDoc* CBiYeSheJiView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBiYeSheJiDoc)));
	return (CBiYeSheJiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBiYeSheJiView message handlers

void CBiYeSheJiView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CView::OnPaint() for painting messages

	//设置背景颜色
	CRect rect;
	GetClientRect(&rect); //计算对话框的尺寸
	dc.FillSolidRect(&rect,RGB(255,255,208/*204,255,204*/)); //绘制对话框背景色

	//绘制模拟视图圆
	CClientDC m_dc(this);
/*	CRect r2(482,266,970,665);
	CPen pen;
	CPen* pOldPen1;
	pen.CreatePen(PS_SOLID | PS_COSMETIC,1,RGB(0,0,255));
	pOldPen1=m_dc.SelectObject(&pen);
	m_dc.Arc(r2,CPoint(r2.right,r2.CenterPoint().y),CPoint(r2.right,r2.CenterPoint().y));
	m_dc.SelectObject(pOldPen1);*/
	//填充圆形区
	CRgn rgn; 
	CRect rect1(10, 280, 200, 470);//圆心坐标（105，375）
	rgn.CreateEllipticRgnIndirect(&rect1);
	CBrush brush(RGB(0,0,0));
	m_dc.FillRgn(&rgn,&brush);	
	//绘制中心点
	//横杠杠
/*	m_Origin=CPoint(728,473);
	CClientDC cdc(this);
	cdc.MoveTo(m_Origin);
	m_point=CPoint(736,473);
	cdc.LineTo(m_point);
	//竖杠杠
	m_Origin1=CPoint(732,469);
	CClientDC cdc1(this);
	cdc.MoveTo(m_Origin1);
	m_point1=CPoint(732,477);
	cdc.LineTo(m_point1);

	//绘制罗经
	CRect r(482,70,970,220);
	CPen penBlue;
	CPen* pOldPen;
	penBlue.CreatePen(PS_SOLID | PS_COSMETIC,1,RGB(0,0,255));
	pOldPen=m_dc.SelectObject(&penBlue);
//	m_dc.Arc(r,CPoint(r.right,120/*r.CenterPoint().y*///),
//		CPoint(r.left,120/*r.CenterPoint().y)*/));
//	m_dc.SelectObject(pOldPen);
}
