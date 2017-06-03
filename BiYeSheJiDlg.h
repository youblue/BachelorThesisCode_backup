#if !defined(AFX_BIYESHEJIDLG_H__92196772_8812_4467_BFF7_81345B76FAEF__INCLUDED_)
#define AFX_BIYESHEJIDLG_H__92196772_8812_4467_BFF7_81345B76FAEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BiYeSheJiDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBiYeSheJiDlg dialog

class CBiYeSheJiDlg : public CDialog
{
// Construction
public:
	//HRESULT ShowPic(char *lpstrFile,HWND hWnd,int nScrWidth,int nScrHeight);
	HWND hwndAnalysis;
	CRect rect;
	CAPTUREPARMS m_Parms;
	HWND hwndVideo;
	CAPSTATUS m_CapStatus;
	CAPDRIVERCAPS m_CapDrvCap;
	CBiYeSheJiDlg(CWnd* pParent = NULL);   // standard constructor

	typedef struct{
		int Value;
		int Dist;
		int AngleNumber;	
	}MaxValue;

// Dialog Data
	//{{AFX_DATA(CBiYeSheJiDlg)
	enum { IDD = IDD_BIYESHEJI_DIALOG };
	double	m_K1;
	long	m_yStartRight;
	long	m_yStartLeft;
	long	m_yRight1;
	long	m_yLeft1;
	long	m_xStartRight;
	long	m_xStartLeft;
	long	m_xRight1;
	long	m_xLeft1;
	double	m_K;
	double	m_K2;
	double	m_b1;
	double	m_b2;
	double	m_Theta;
	double	m_MX0;
	double	m_MY0;
	double	m_b;
	double	m_le;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBiYeSheJiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBiYeSheJiDlg)
	afx_msg void OnStartcap();
	afx_msg void OnView();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnGo();
	afx_msg void OnRight();
	afx_msg void OnLeft();
	afx_msg void OnBack();
	afx_msg void OnStop();
	afx_msg void OnStopcap();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBrush m_brush;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIYESHEJIDLG_H__92196772_8812_4467_BFF7_81345B76FAEF__INCLUDED_)
