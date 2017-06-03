// BiYeSheJi.h : main header file for the BIYESHEJI application
//

#if !defined(AFX_BIYESHEJI_H__52D26B0C_A53D_48C1_98C5_A7FDD66A76AC__INCLUDED_)
#define AFX_BIYESHEJI_H__52D26B0C_A53D_48C1_98C5_A7FDD66A76AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBiYeSheJiApp:
// See BiYeSheJi.cpp for the implementation of this class
//

class CBiYeSheJiApp : public CWinApp
{
public:
	CBiYeSheJiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBiYeSheJiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBiYeSheJiApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIYESHEJI_H__52D26B0C_A53D_48C1_98C5_A7FDD66A76AC__INCLUDED_)
