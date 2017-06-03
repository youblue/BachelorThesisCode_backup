// BiYeSheJiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BiYeSheJi.h"
#include "BiYeSheJiDoc.h"
#include "BiYeSheJiDlg.h"
#include "TemplateTrans.h"
#include <math.h>

#define  pi 3.141593

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBiYeSheJiDlg dialog


CBiYeSheJiDlg::CBiYeSheJiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBiYeSheJiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBiYeSheJiDlg)
	m_K1 = 0.0;
	m_yStartRight = 0;
	m_yStartLeft = 0;
	m_yRight1 = 0;
	m_yLeft1 = 0;
	m_xStartRight = 0;
	m_xStartLeft = 0;
	m_xRight1 = 0;
	m_xLeft1 = 0;
	m_K = 0.0;
	m_K2 = 0.0;
	m_b = 0.0;
	m_b1 = 0.0;
	m_b2 = 0.0;
	m_le = 0.0;
	m_Theta = 0.0;
	m_MX0 = 0.0;
	m_MY0 = 0.0;
	//}}AFX_DATA_INIT
	m_brush.CreateSolidBrush(RGB(208,255,208));
	
}


void CBiYeSheJiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBiYeSheJiDlg)
	DDX_Text(pDX, IDC_K1, m_K1);
	DDX_Text(pDX, IDC_yStartRight, m_yStartRight);
	DDX_Text(pDX, IDC_yStartLeft, m_yStartLeft);
	DDX_Text(pDX, IDC_yRight1, m_yRight1);
	DDX_Text(pDX, IDC_yLeft1, m_yLeft1);
	DDX_Text(pDX, IDC_xStartRight, m_xStartRight);
	DDX_Text(pDX, IDC_xStartLeft, m_xStartLeft);
	DDX_Text(pDX, IDC_xRight1, m_xRight1);
	DDX_Text(pDX, IDC_xLeft1, m_xLeft1);
	DDX_Text(pDX, IDC_K, m_K);
	DDX_Text(pDX, IDC_K2, m_K2);
	DDX_Text(pDX, IDC_b, m_b);
	DDX_Text(pDX, IDC_b1, m_b1);
	DDX_Text(pDX, IDC_b2, m_b2);
	DDX_Text(pDX, IDC_le, m_le);
	DDX_Text(pDX, IDC_Theta, m_Theta);
	DDX_Text(pDX, IDC_MX0, m_MX0);
	DDX_Text(pDX, IDC_MY0, m_MY0);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBiYeSheJiDlg, CDialog)
	//{{AFX_MSG_MAP(CBiYeSheJiDlg)
	ON_BN_CLICKED(IDC_Startcap, OnStartcap)
	ON_BN_CLICKED(IDC_VIEW, OnView)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_GO, OnGo)
	ON_BN_CLICKED(IDC_RIGHT, OnRight)
	ON_BN_CLICKED(IDC_LEFT, OnLeft)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_Stopcap, OnStopcap)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBiYeSheJiDlg message handlers

void CBiYeSheJiDlg::OnStartcap() 
{
	// TODO: Add your control notification handler code here

    SetTimer(1,100,NULL);

	CWnd *pWnd=AfxGetMainWnd()->GetDlgItem(IDC_VIEW);

	hwndVideo = capCreateCaptureWindow(
	  					(LPSTR) "My Capture Window",
	  					WS_CHILD | WS_VISIBLE,
	  					0, 0, 320,240,
	  					pWnd->GetSafeHwnd(),
	  					(int) 1);
    hwndAnalysis = capCreateCaptureWindow(
	  					(LPSTR) "My Capture Window",
	  					WS_CHILD | WS_VISIBLE,
	  					320, 0, 640,480,
	  					pWnd->GetSafeHwnd(),
	  					(int) 1);
	

	if(capDriverConnect(hwndVideo,0))
	{
		capDriverGetCaps(hwndVideo,&m_CapDrvCap,sizeof(CAPDRIVERCAPS));
		if(m_CapDrvCap.fCaptureInitialized)
		{
			capGetStatus(hwndVideo,&m_CapStatus,sizeof(m_CapStatus));
			capPreviewRate( hwndVideo, 66 );
			capPreview(hwndVideo,TRUE);
		}
		else
		{
			AfxMessageBox("�豸û�г�ʼ��!");
			AfxGetMainWnd()->PostMessage(WM_CLOSE);
		}
	}
	else
	{
		AfxMessageBox("�豸û����!");
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	}
	if(capPreview(hwndVideo,FALSE))
		capPreview(hwndVideo,TRUE);

	capCaptureGetSetup(hwndVideo,&m_Parms,sizeof(m_Parms));
    if(capCaptureGetSetup(hwndVideo,&m_Parms,sizeof(m_Parms))==TRUE)
	{}
	else
		AfxMessageBox("����ͷ������������!���������!");
//	capCaptureSequence(hwndVideo);
}

void CBiYeSheJiDlg::OnView() 
{
	// TODO: Add your control notification handler code here
	
}

void CBiYeSheJiDlg::OnTimer(UINT nIDEvent) 
{
// TODO: Add your message handler code here and/or call default
	capPreview(hwndVideo,FALSE);
	BOOL FileSaveDIB;
	FileSaveDIB=capFileSaveDIB(hwndVideo,"C:\\image.bmp");

	CFile nFile;
	nFile.Open("C:\\image.bmp",CFile::modeRead);
	HDIB hDIB1 = ReadDIBFile(nFile);
	HDIB hDIB2 = NewDIB(320,240,8);
	nFile.Close();

////////////////////////////////////////////////////////////////////////////////////////////
	LPSTR	lpDIB1;
	LPSTR	lpDIB2;
	
	// ��DIB����õ�DIBָ�벢����DIB
    lpDIB1 = (LPSTR) ::GlobalLock((HGLOBAL)hDIB1);
	lpDIB2 = (LPSTR) ::GlobalLock((HGLOBAL)hDIB2);

	// ָ��DIB������������ָ��
	LPSTR   lpDIBBits1;	
	LPSTR   lpDIBBits2;	

	// ָ��DIB���ص�ָ��
//	BYTE *	lpSrc1;	

	// ͼ����
	LONG	lWidth1;	
	LONG	lWidth2;
	// ͼ��߶�
    LONG  	lHeight1;
	LONG  	lHeight2;
	

	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes1;
	LONG	lLineBytes2;

	// ָ��BITMAPINFO�ṹ��ָ�루Win3.0��
	LPBITMAPINFO lpbmi1;	

	// ָ��BITMAPCOREINFO�ṹ��ָ��
	LPBITMAPCOREINFO lpbmc1;
	
	// ��ȡָ��BITMAPINFO�ṹ��ָ�루Win3.0��
	lpbmi1 = (LPBITMAPINFO)lpDIB1;	

	// ��ȡָ��BITMAPCOREINFO�ṹ��ָ��
	lpbmc1 = (LPBITMAPCOREINFO)lpDIB1;	

	// �Ҷ�ӳ���
//	BYTE bMap[256];
	BYTE r,g,b;

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits1 = ::FindDIBBits(lpDIB1);
	lpDIBBits2 = ::FindDIBBits(lpDIB2);
		
	// ��ȡͼ����
	lWidth1 = ::DIBWidth(lpDIB1);	
	lWidth2 = ::DIBWidth(lpDIB2);

	// ��ȡͼ��߶�
	lHeight1 = ::DIBHeight(lpDIB1);	
	lHeight2 = ::DIBHeight(lpDIB2);	

	// ����ͼ��ÿ�е��ֽ���
	lLineBytes1 = WIDTHBYTES(lWidth1 * 24);	
	lLineBytes2 = WIDTHBYTES(lWidth1 * 8);	

// ����ÿ�����ص���ɫ�����������ջҶ�ӳ����ɻҶ�ֵ��

//����ɨ��
for(int i = 0; i < lHeight1; i++)
{
  //����ɨ��
  for(int j = 0; j < lLineBytes1; j++)
  {
	  // ��ȡ����ɫ����
			r = *((unsigned char *)lpDIBBits1 + lLineBytes1 * i + j);
			j++;
			g = *((unsigned char *)lpDIBBits1 + lLineBytes1 * i + j);
			j++;
			b = *((unsigned char *)lpDIBBits1 + lLineBytes1 * i + j);

			// ����Ҷ�ֵ
			BYTE Y = (9798 * r + 19235 * g + 3735 * b) / 32768;
 
			// ��д�Ҷ�ֵ
			*((unsigned char *)lpDIBBits1 + lLineBytes1 * i + j - 2) = Y;
			*((unsigned char *)lpDIBBits1 + lLineBytes1 * i + j - 1) = Y;
			*((unsigned char *)lpDIBBits1 + lLineBytes1 * i + j ) = Y;

            *((unsigned char *)lpDIBBits2 + lLineBytes2 * i + (j - 2)/3)=Y;
  }
}
//�������
::GlobalUnlock ((HGLOBAL)hDIB1);

//////////////////////////////////////////////////////////////////////////////////////////////
/***************************/
/**********��ֵ�˲�*********/
/***************************/
/*****************************************************
* 
*   �������ƣ�
*      Template��
*
*    ������
*	   HDIB    hDIB         ��ͼ��ľ��
*      int  tem_w           ��ģ��Ŀ��
*      int  tem_h           ��ģ��ĸ߶�
*      
*    ���ܣ�
*	   ��ͼ�������ֵ
*
*    ˵����
*	   Ϊ�����������ģ��Ŀ�Ⱥ͸߶ȶ�ӦΪ����
*******************************************************/

    //ͳ���м�ֵ
    double mid;

	BYTE *temp=(BYTE*)malloc(640*240*8);//ֻ����1/3ͼ��

    //ָ��ͼ����ʼλ�õ�ָ��
    BYTE *lpDIB=(BYTE*)::GlobalLock((HGLOBAL) hDIB2);

	//ָ��������ʼλ�õ�ָ��
	BYTE *pScrBuff =(BYTE*)::FindDIBBits((char*)lpDIB2);
   
	//��ȡͼ�����ɫ��Ϣ
    int numColors=(int) ::DIBNumColors((char *)lpDIB2);

    //��ָ��ͼ��������ʼλ�õ�ָ�룬��ֵ��ָ�����
    BYTE* oldbuf = pScrBuff;

    //ѭ������
    int ii,jj,mm,nn;

	int w, h, dw;

	//��ȡͼ��Ŀ��
	w = (int) ::DIBWidth((char *)lpDIB);
	
	//��ȡͼ��ĸ߶�
	h = (int) ::DIBHeight((char *)lpDIB);
	
	//����ͼ��ÿ�е��ֽ���
	dw = (w+3)/4*4;      
	
	//����һ����ԭͼ���С��ͬ��25ɫ�Ҷ�λͼ
    HDIB newhDIB=NewDIB(w,h,8);  
    
	//ָ���µ�λͼ��ָ��
	BYTE *newlpDIB=(BYTE*)::GlobalLock((HGLOBAL) newhDIB);

	//ָ���µ�λͼ��������ʼλ�õ�ָ�� 
    BYTE *destBuf = (BYTE*)FindDIBBits((char *)newlpDIB);
    
   //��ָ����ͼ��������ʼλ�õ�ָ�룬��ֵ��ָ�����
    BYTE *newbuf=destBuf; 
	
	//��ͼ�����ɨ��
   
	//�� 
    for(ii=0;ii<h;ii++)
    {  
		//��
	   for(jj=0;jj<w;jj++)
	   {   

		   //Ϊͳ�Ʊ�������ʼֵ
	       

         //����ͼ���4���߿�����ر���ԭ�ҶȲ���
	     if( jj<((640-1)/2) || jj>(w-(640+1)/2) || ii<((240-1)/2) || ii>(h-(240+1)/2) )
	      *(newbuf+ii*dw+jj)=*(oldbuf+ii*dw+jj);
		 
         //�������������ؽ���ģ�����
		 else 
         { 

          //���㣨i,j������Ϊģ�������
          for(mm=ii-((240-1)/2);mm<=ii+((240-1)/2);mm++)
          {
		     for(nn=jj-((640-1)/2);nn<=jj+((640-1)/2);nn++)
		    
             //���Ե㣨i��j��Ϊ���ģ���ģ���С��ͬ�ķ�Χ�ڵ����ش��ݵ�ģ�������
		     temp[(mm-i+((240-1)/2))*640+nn-jj+((640-1)/2)]=*(oldbuf+mm*dw+nn);
		  
		  }
          
		 //�������ݷ�������ֵ
           for(mm=0;mm<640*240-1;mm++)
           {
		   
		      for(nn=0;nn<640*240-mm-1;nn++)
			  {
			    if(temp[nn]>temp[nn+1]) 
			    mid=temp[nn];
                temp[nn]=temp[nn+1];
			    temp[nn+1]=mid;
			  }
		   
		   } 

           //������Ľ���ŵ��µ�λͼ����Ӧλ��
	      *(newbuf+ii*dw+jj)=temp[(640*240-1)/2];
		 }
	   }
	} 
   

//////////////////////////////////////////////////////////////////////////////////////////////

/***************************/
/**********SOBEL************///ֻ����1/3ͼ��
/***************************/
// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst1;
	LPSTR	lpDst2;
	
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	LPSTR	lpNewDIBBits2;
	HLOCAL	hNewDIBBits2;

	//ѭ������
	long m;
	long n;

	// ģ��߶�
	int		iTempH;
	
	// ģ����
	int		iTempW;
	
	// ģ��ϵ��
	FLOAT	fTempC;
	
	// ģ������Ԫ��X����
	int		iTempMX;
	
	// ģ������Ԫ��Y����
	int		iTempMY;
	
	//ģ������
	FLOAT aTemplate[9];

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits1 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	
	// �����ڴ�
	lpNewDIBBits1 = (char * )LocalLock(hNewDIBBits1);

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits2 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	
	// �����ڴ�
	lpNewDIBBits2 = (char * )LocalLock(hNewDIBBits2);

	// ����Դͼ�񵽻���ͼ����
	lpDst1 = (char *)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits2, lWidth2 * lHeight2/2);
	lpDst2 = (char *)lpNewDIBBits2;
	memcpy(lpNewDIBBits2, lpDIBBits2, lWidth2 * lHeight2/2);

	// ����Sobelģ�����
	iTempW = 3;
	iTempH = 3;
	fTempC = 1.0;
	iTempMX = 1;
	iTempMY = 1;
	aTemplate[0] = -1.0;
	aTemplate[1] = -2.0;
	aTemplate[2] = -1.0;
	aTemplate[3] = 0.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 0.0;
	aTemplate[6] = 1.0;
	aTemplate[7] = 2.0;
	aTemplate[8] = 1.0;

	// ����Template()����
	Template(lpNewDIBBits1, lWidth2, lHeight2/2, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC);

	// ����Sobelģ�����
	aTemplate[0] = -1.0;
	aTemplate[1] = 0.0;
	aTemplate[2] = 1.0;
	aTemplate[3] = -2.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 2.0;
	aTemplate[6] = -1.0;
	aTemplate[7] = 0.0;
	aTemplate[8] = 1.0;

	// ����Template()����
	Template(lpNewDIBBits2, lWidth2, lHeight2/2, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC);


	//����������ͼ������ֵ
	for(n = 0; n <lHeight2/2; n++)
	{
		for(m = 0;m <lWidth2-1; m++)
		{

			// ָ�򻺴�ͼ��1������j�У���i�����ص�ָ��			
			lpDst1 = (char *)lpNewDIBBits1 + lWidth2 * n + m;

			// ָ�򻺴�ͼ��2������j�У���i�����ص�ָ��			
			lpDst2 = (char *)lpNewDIBBits2 + lWidth2 * n + m;
			
			if(*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;
		
		}
	}

	// ���ƾ���ģ��������ͼ��Դͼ��
	memcpy(lpDIBBits2, lpNewDIBBits1, lWidth2 * lHeight2/2);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	LocalUnlock(hNewDIBBits2);
	LocalFree(hNewDIBBits2);
//////////////////////////////////////////////////////////////////////////////////////////////

/***************************/
/********��ֵ�ָ�***********///ֻ����1/3ͼ��
/***************************/
   // ָ��Դͼ���ָ��
	LPSTR	lpSrc;
	
	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst;
	
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//ѭ������
	long u;
	long v;

	//����ֵ
	unsigned char pixel;

	//ֱ��ͼ����
	long lHistogram[256];

	//��ֵ�����Ҷ�ֵ����С�Ҷ�ֵ�����������ƽ���Ҷ�ֵ
	unsigned char iThreshold,iNewThreshold,iMaxGrayValue,iMinGrayValue,iMean1GrayValue,iMean2GrayValue;

	//���ڼ�������Ҷ�ƽ��ֵ���м����
	long lP1,lP2,lS1,lS2;

	//��������
	int iIterationTimes;

	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	
	// �����ڴ�
	lpNewDIBBits = (char * )LocalLock(hNewDIBBits);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = (char *)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth2 * lHeight2/2);

	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth2 * 8);

	for (u = 0; u < 256;u++)
	{
		lHistogram[u]=0;
	}

	//���ֱ��ͼ
	iMaxGrayValue = 0;
	iMinGrayValue = 255;
	for (u = 0;u < lWidth2 ;u++)
	{
		for(v = 0;v < lHeight2/2 ;v++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (char *)lpDIBBits2 + lLineBytes * v + u;
	
			pixel = (unsigned char)*lpSrc;
			
			lHistogram[pixel]++;
			//�޸������С�Ҷ�ֵ
			if(iMinGrayValue > pixel)
			{
				iMinGrayValue = pixel;
			}
			if(iMaxGrayValue < pixel)
			{
				iMaxGrayValue = pixel;
			}
		}
	}

	//�����������ֵ
	iNewThreshold = (iMinGrayValue + iMaxGrayValue)/2;
	iThreshold = 0;
	
	for(iIterationTimes = 0; iThreshold != iNewThreshold && iIterationTimes < 100;iIterationTimes ++)
	{
		iThreshold = iNewThreshold;
		lP1 =0;
		lP2 =0;
		lS1 = 0;
		lS2 = 0;
		//����������ĻҶ�ƽ��ֵ
		for (u = iMinGrayValue;u < iThreshold;u++)
		{
			lP1 += lHistogram[u]*u;
			lS1 += lHistogram[u];
		}
		iMean1GrayValue = (unsigned char)(lP1 / lS1);
		for (u = iThreshold+1;u < iMaxGrayValue;u++)
		{
			lP2 += lHistogram[u]*u;
			lS2 += lHistogram[u];
		}
		iMean2GrayValue = (unsigned char)(lP2 / lS2);
		iNewThreshold =  (iMean1GrayValue + iMean2GrayValue)/2;
	}

	//������ֵ��ͼ���ֵ��
	for (u = 0;u < lWidth2 ;u++)
	{
		for(v = 0;v < lHeight2/2 ;v++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (char *)lpDIBBits2 + lLineBytes * v + u;
	
			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst = (char *)lpNewDIBBits + lLineBytes * v + u;

			pixel = (unsigned char)*lpSrc;
			
			if(pixel <= iThreshold)
			{
				*lpDst = (unsigned char)0;
			}
			else
			{
				*lpDst = (unsigned char)255;
			}
		}
	}

	// ����ͼ��
	memcpy(lpDIBBits2, lpNewDIBBits, lWidth2 * lHeight2/2);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

//////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************
                         ��·�߽������㷨
 ************************************************************************/
	////////////////////////////
	//1����ɫ����ͼ�����1/3����
	////////////////////////////

	 // ָ��Դͼ���ָ��
	LPSTR	lpSrc3;
	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst3;
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits3;
	HLOCAL	hNewDIBBits3;
	//����ֵ
	unsigned char pixel3;

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits3 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	
	// �����ڴ�
	lpNewDIBBits3 = (char * )LocalLock(hNewDIBBits3);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst3 = (char *)lpNewDIBBits3;
	memset(lpDst3, (BYTE)255, lWidth2 * lHeight2/2);

	//��ɫ
	for(long yy = 0; yy <lHeight2/2; yy++)
	{
		for(long xx = 0;xx <lWidth2; xx++)
		{			
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc3 = (char *)lpDIBBits2 + lWidth2 * yy + xx;			
			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst3 = (char *)lpNewDIBBits + lWidth2 * yy + xx;			
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel3 = (unsigned char)*lpSrc3;

			if(pixel3 == 255)
			{
				*lpDst3 = (unsigned char)0;
			}
			else
			{
				*lpDst3 = (unsigned char)255;
			}
		}
	}
    // ����ͼ��
	memcpy(lpDIBBits2, lpNewDIBBits3, lWidth2 * lHeight2/2);
	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits3);
	LocalFree(hNewDIBBits3);

/*************************************************************************
 * 2��
 * ��1��  ���͵�1��
 ************************************************************************/
	
	LPSTR	lpSrc4;			// ָ��Դͼ���ָ��	
	LPSTR	lpDst4;			// ָ�򻺴�ͼ���ָ��	
	LPSTR	lpNewDIBBits4;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits4;	
	long i4,j4,m4,n4;		//ѭ������	
	unsigned char pixel4;	//����ֵ

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits4 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	lpNewDIBBits4 = (char * )LocalLock(hNewDIBBits4);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst4 = (char *)lpNewDIBBits4;
	memset(lpDst4, (BYTE)255, lWidth2 * lHeight2/2);

	//ʹ���Զ���ĽṹԪ�ؽ�������
	for(j4 = 1; j4 <lHeight2/2-1; j4++)
	{
		for(i4 = 0;i4 <lWidth2; i4++)
		{
			// ����ʹ��3��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұ�
			// ���������غ����ϱߺ����±ߵ���������

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc4 = (char *)lpDIBBits2 + lWidth2 * j4 + i4;
			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst4 = (char *)lpNewDIBBits4 + lWidth2 * j4 + i4;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel4 = (unsigned char)*lpSrc4;

			//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
			*lpDst4 = (unsigned char)255;

			//ԭͼ���ж�Ӧ�ṹԪ����Ϊ��ɫ����Щ����ֻҪ��һ���Ǻ�ɫ��
			//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
			//ע����DIBͼ�������������µ��õ�
			for (m4 = 0;m4 < 3;m4++ )
			{
				for (n4 = 0;n4 < 3;n4++)
				{
					pixel4 = *(lpSrc4 + (1-m4)*lWidth2 + (n4-1));
					if (pixel4 == 0 )
					{	
						*lpDst4 = (unsigned char)0;
						break;
					}
				}
			}				
		}
	}
	// �������ͺ��ͼ��
	memcpy(lpDIBBits2, lpNewDIBBits4, lWidth2 * lHeight2/2);

	LocalUnlock(hNewDIBBits4);
	LocalFree(hNewDIBBits4);

/*************************************************************************
 * 
 * ��2�����͵�2��
 ************************************************************************/
	
	LPSTR	lpSrc5;			// ָ��Դͼ���ָ��	
	LPSTR	lpDst5;			// ָ�򻺴�ͼ���ָ��	
	LPSTR	lpNewDIBBits5;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits5;	
	long i5,j5,m5,n5;		//ѭ������	
	unsigned char pixel5;	//����ֵ

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits5 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	lpNewDIBBits5 = (char * )LocalLock(hNewDIBBits5);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst5 = (char *)lpNewDIBBits5;
	memset(lpDst5, (BYTE)255, lWidth2 * lHeight2/2);

	//ʹ���Զ���ĽṹԪ�ؽ�������
	for(j5 = 1; j5 <lHeight2/2-1; j5++)
	{
		for(i5 = 0;i5 <lWidth2; i5++)
		{
			// ����ʹ��3��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұ�
			// ���������غ����ϱߺ����±ߵ���������

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc5 = (char *)lpDIBBits2 + lWidth2 * j5 + i5;
			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst5 = (char *)lpNewDIBBits5 + lWidth2 * j5 + i5;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel5 = (unsigned char)*lpSrc5;

			//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
			*lpDst5 = (unsigned char)255;

			//ԭͼ���ж�Ӧ�ṹԪ����Ϊ��ɫ����Щ����ֻҪ��һ���Ǻ�ɫ��
			//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
			//ע����DIBͼ�������������µ��õ�
			for (m5 = 0;m5 < 3;m5++ )
			{
				for (n5 = 0;n5 < 3;n5++)
				{
					pixel5 = *(lpSrc5 + (1-m5)*lWidth2 + (n5-1));
					if (pixel5 == 0 )
					{	
						*lpDst5 = (unsigned char)0;
						break;
					}
				}
			}				
		}
	}
	// �������ͺ��ͼ��
	memcpy(lpDIBBits2, lpNewDIBBits5, lWidth2 * lHeight2/2);

	LocalUnlock(hNewDIBBits5);
	LocalFree(hNewDIBBits5);
/*************************************************************************
 * 
 * ��3�����͵�3��
 ************************************************************************/
	
	LPSTR	lpSrc6;			// ָ��Դͼ���ָ��	
	LPSTR	lpDst6;			// ָ�򻺴�ͼ���ָ��	
	LPSTR	lpNewDIBBits6;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits6;	
	long i6,j6,m6,n6;		//ѭ������	
	unsigned char pixel6;	//����ֵ

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits6 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	lpNewDIBBits6 = (char * )LocalLock(hNewDIBBits6);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst6 = (char *)lpNewDIBBits6;
	memset(lpDst6, (BYTE)255, lWidth2 * lHeight2/2);

	//ʹ���Զ���ĽṹԪ�ؽ�������
	for(j6 = 1; j6 <lHeight2/2-1; j6++)
	{
		for(i6 = 0;i6 <lWidth2; i6++)
		{
			// ����ʹ��3��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұ�
			// ���������غ����ϱߺ����±ߵ���������

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc6 = (char *)lpDIBBits2 + lWidth2 * j6 + i6;
			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst6 = (char *)lpNewDIBBits6 + lWidth2 * j6 + i6;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel6 = (unsigned char)*lpSrc6;

			//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
			*lpDst6 = (unsigned char)255;

			//ԭͼ���ж�Ӧ�ṹԪ����Ϊ��ɫ����Щ����ֻҪ��һ���Ǻ�ɫ��
			//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
			//ע����DIBͼ�������������µ��õ�
			for (m6 = 0;m6 < 3;m6++ )
			{
				for (n6 = 0;n6 < 3;n6++)
				{
					pixel6 = *(lpSrc6 + (1-m6)*lWidth2 + (n6-1));
					if (pixel6 == 0 )
					{	
						*lpDst6 = (unsigned char)0;
						break;
					}
				}
			}				
		}
	}
	// �������ͺ��ͼ��
	memcpy(lpDIBBits2, lpNewDIBBits6, lWidth2 * lHeight2/2);

	LocalUnlock(hNewDIBBits6);
	LocalFree(hNewDIBBits6);
	/*************************************************************************
 * 
 * ��3�����͵�4��
 ************************************************************************/
	
	LPSTR	lpSrc11;			// ָ��Դͼ���ָ��	
	LPSTR	lpDst11;			// ָ�򻺴�ͼ���ָ��	
	LPSTR	lpNewDIBBits11;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits11;	
	long i11,j11,m11,n11;		//ѭ������	
	unsigned char pixel11;	//����ֵ

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits11 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	lpNewDIBBits11 = (char * )LocalLock(hNewDIBBits11);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst11 = (char *)lpNewDIBBits11;
	memset(lpDst11, (BYTE)255, lWidth2 * lHeight2/2);

	//ʹ���Զ���ĽṹԪ�ؽ�������
	for(j11 = 1; j11 <lHeight2/2-1; j11++)
	{
		for(i11 = 0;i11 <lWidth2; i11++)
		{
			// ����ʹ��3��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұ�
			// ���������غ����ϱߺ����±ߵ���������

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc11 = (char *)lpDIBBits2 + lWidth2 * j11 + i11;
			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst11 = (char *)lpNewDIBBits11 + lWidth2 * j11 + i11;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel11 = (unsigned char)*lpSrc11;

			//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
			*lpDst11 = (unsigned char)255;

			//ԭͼ���ж�Ӧ�ṹԪ����Ϊ��ɫ����Щ����ֻҪ��һ���Ǻ�ɫ��
			//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
			//ע����DIBͼ�������������µ��õ�
			for (m11 = 0;m11 < 3;m11++ )
			{
				for (n11 = 0;n11 < 3;n11++)
				{
					pixel11 = *(lpSrc11 + (1-m11)*lWidth2 + (n11-1));
					if (pixel11 == 0 )
					{	
						*lpDst11 = (unsigned char)0;
						break;
					}
				}
			}				
		}
	}
	// �������ͺ��ͼ��
	memcpy(lpDIBBits2, lpNewDIBBits11, lWidth2 * lHeight2/2);

	LocalUnlock(hNewDIBBits11);
	LocalFree(hNewDIBBits11);
	/*************************************************************************
	* 
	*��4����ʴ
	************************************************************************/
	
	LPSTR	lpSrc7;			// ָ��Դͼ���ָ��	
	LPSTR	lpDst7;			// ָ�򻺴�ͼ���ָ��	
	LPSTR	lpNewDIBBits7;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits7;	
	long i7,j7,n7,m7;			//ѭ������
	unsigned char pixel7;	//����ֵ

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits7 = LocalAlloc(LHND, lWidth2 * lHeight2/2);	
	lpNewDIBBits7 = (char * )LocalLock(hNewDIBBits7);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst7 = (char *)lpNewDIBBits7;
	memset(lpDst7, (BYTE)255, lWidth2 * lHeight2/2);

	//ʹ���Զ���ĽṹԪ�ؽ��и�ʴ
	for(j7 = 1; j7 <lHeight2/2-1; j7++)
	{
		for(i7 = 0;i7 <lWidth2; i7++)
		{
			// ����ʹ��3��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұ�
			// ���������غ����ϱߺ����±ߵ���������

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc7 = (char *)lpDIBBits2 + lWidth2 * j7 + i7;
			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst7 = (char *)lpNewDIBBits7 + lWidth2 * j7 + i7;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel7 = (unsigned char)*lpSrc7;

			//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
			*lpDst7 = (unsigned char)0;

			//���ԭͼ���ж�Ӧ�ṹԪ����Ϊ��ɫ����Щ������һ�����Ǻ�ɫ��
			//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
			//ע����DIBͼ�������������µ��õ�
			for (m7 = 0;m7 < 3;m7++ )
			{
				for (n7 = 0;n7 < 3;n7++)
				{
					pixel7 = *(lpSrc7 + ((2-m7)-1)*lWidth2 + (n7-1));
					if (pixel7 == 255 )
					{	
						*lpDst7 = (unsigned char)255;
						break;
					}
				}
			}			
		}
	}
	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits2, lpNewDIBBits7, lWidth2 * lHeight2/2);

	LocalUnlock(hNewDIBBits7);
	LocalFree(hNewDIBBits7);

	/*************************************************************************
	* 
	*��4����ʴ2
	************************************************************************/
	
	LPSTR	lpSrc12;			// ָ��Դͼ���ָ��	
	LPSTR	lpDst12;			// ָ�򻺴�ͼ���ָ��	
	LPSTR	lpNewDIBBits12;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits12;	
	long i12,j12,n12,m12;			//ѭ������
	unsigned char pixel12;	//����ֵ

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits12 = LocalAlloc(LHND, lWidth2 * lHeight2/2);	
	lpNewDIBBits12 = (char * )LocalLock(hNewDIBBits12);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst12 = (char *)lpNewDIBBits12;
	memset(lpDst12, (BYTE)255, lWidth2 * lHeight2/2);

	//ʹ���Զ���ĽṹԪ�ؽ��и�ʴ
	for(j12 = 1; j12 <lHeight2/2-1; j12++)
	{
		for(i12 = 0;i12 <lWidth2; i12++)
		{
			// ����ʹ��3��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұ�
			// ���������غ����ϱߺ����±ߵ���������

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc12 = (char *)lpDIBBits2 + lWidth2 * j12 + i12;
			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst12 = (char *)lpNewDIBBits12 + lWidth2 * j12 + i12;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel12 = (unsigned char)*lpSrc12;

			//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
			*lpDst12 = (unsigned char)0;

			//���ԭͼ���ж�Ӧ�ṹԪ����Ϊ��ɫ����Щ������һ�����Ǻ�ɫ��
			//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
			//ע����DIBͼ�������������µ��õ�
			for (m12 = 0;m12 < 3;m12++ )
			{
				for (n12 = 0;n12 < 3;n12++)
				{
					pixel12 = *(lpSrc12 + ((2-m12)-1)*lWidth2 + (n12-1));
					if (pixel12 == 255 )
					{	
						*lpDst12 = (unsigned char)255;
						break;
					}
				}
			}			
		}
	}
	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits2, lpNewDIBBits12, lWidth2 * lHeight2/2);

	LocalUnlock(hNewDIBBits12);
	LocalFree(hNewDIBBits12);
	/*************************************************************************
 * 
 *  ��5��ϸ��

 ************************************************************************/
		
	LPSTR	lpSrc8;			// ָ��Դͼ���ָ��	
	LPSTR	lpDst8;			// ָ�򻺴�ͼ���ָ��	
	LPSTR	lpNewDIBBits8;	// ָ�򻺴�DIBͼ���ָ��
	HLOCAL	hNewDIBBits8;	
	BOOL bModified;			//����	
	long i8,j8,m8,n8;			//ѭ������

	//�ĸ�����
	BOOL bCondition1;
	BOOL bCondition2;
	BOOL bCondition3;
	BOOL bCondition4;
	
	unsigned char nCount8;	//������	
	unsigned char pixel8;	//����ֵ	
	unsigned char neighbour[5][5];	//5��5������������ֵ

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits8 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	lpNewDIBBits8 = (char * )LocalLock(hNewDIBBits8);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst8 = (char *)lpNewDIBBits8;
	memset(lpDst8, (BYTE)255, lWidth2 * lHeight2/2);

	bModified = TRUE;
	while(bModified)
	{
		bModified = FALSE;
		for(j8 = 2; j8 <lHeight2/2-2; j8++)
		{
			for(i8 = 2;i8 <lWidth2-2; i8++)
			{
				bCondition1 = FALSE;
				bCondition2 = FALSE;
				bCondition3 = FALSE;
				bCondition4 = FALSE;

				//����ʹ��5��5�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ�������Χ�ļ��кͼ�������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc8 = (char *)lpDIBBits2 + lWidth2 * j8 + i8;
				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst8 = (char *)lpNewDIBBits8 + lWidth2 * j8 + i8;
				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel8 = (unsigned char)*lpSrc8;

				//���Դͼ���е�ǰ��Ϊ��ɫ��������
				if(pixel8 == 255)
				{
					continue;
				}

				//��õ�ǰ�����ڵ�5��5����������ֵ����ɫ��0������ɫ��1����
				for (m8 = 0;m8 < 5;m8++ )
				{
					for (n8 = 0;n8 < 5;n8++)
					{
						neighbour[m8][n8] =(255 - (unsigned char)*(lpSrc8 + 
							((4 - m8) - 2)*lWidth2 + n8 - 2 )) / 255;
					}
				}

				//����ж�������
				//�ж�2<=NZ(P1)<=6
				nCount8 =  neighbour[1][1] + neighbour[1][2] + neighbour[1][3] \
						+ neighbour[2][1] + neighbour[2][3] + \
						+ neighbour[3][1] + neighbour[3][2] + neighbour[3][3];
				if ( nCount8 >= 2 && nCount8 <=6)
				{
					bCondition1 = TRUE;
				}

				//�ж�Z0(P1)=1
				nCount8 = 0;
				if (neighbour[1][2] == 0 && neighbour[1][1] == 1)
					nCount8++;
				if (neighbour[1][1] == 0 && neighbour[2][1] == 1)
					nCount8++;
				if (neighbour[2][1] == 0 && neighbour[3][1] == 1)
					nCount8++;
				if (neighbour[3][1] == 0 && neighbour[3][2] == 1)
					nCount8++;
				if (neighbour[3][2] == 0 && neighbour[3][3] == 1)
					nCount8++;
				if (neighbour[3][3] == 0 && neighbour[2][3] == 1)
					nCount8++;
				if (neighbour[2][3] == 0 && neighbour[1][3] == 1)
					nCount8++;
				if (neighbour[1][3] == 0 && neighbour[1][2] == 1)
					nCount8++;
				if (nCount8 == 1)
					bCondition2 = TRUE;

				//�ж�P2*P4*P8=0 or Z0(p2)!=1
				if (neighbour[1][2]*neighbour[2][1]*neighbour[2][3] == 0)
				{
					bCondition3 = TRUE;
				}
				else
				{
					nCount8 = 0;
					if (neighbour[0][2] == 0 && neighbour[0][1] == 1)
						nCount8++;
					if (neighbour[0][1] == 0 && neighbour[1][1] == 1)
						nCount8++;
					if (neighbour[1][1] == 0 && neighbour[2][1] == 1)
						nCount8++;
					if (neighbour[2][1] == 0 && neighbour[2][2] == 1)
						nCount8++;
					if (neighbour[2][2] == 0 && neighbour[2][3] == 1)
						nCount8++;
					if (neighbour[2][3] == 0 && neighbour[1][3] == 1)
						nCount8++;
					if (neighbour[1][3] == 0 && neighbour[0][3] == 1)
						nCount8++;
					if (neighbour[0][3] == 0 && neighbour[0][2] == 1)
						nCount8++;
					if (nCount8 != 1)
						bCondition3 = TRUE;
				}

				//�ж�P2*P4*P6=0 or Z0(p4)!=1
				if (neighbour[1][2]*neighbour[2][1]*neighbour[3][2] == 0)
				{
					bCondition4 = TRUE;
				}
				else
				{
					nCount8 = 0;
					if (neighbour[1][1] == 0 && neighbour[1][0] == 1)
						nCount8++;
					if (neighbour[1][0] == 0 && neighbour[2][0] == 1)
						nCount8++;
					if (neighbour[2][0] == 0 && neighbour[3][0] == 1)
						nCount8++;
					if (neighbour[3][0] == 0 && neighbour[3][1] == 1)
						nCount8++;
					if (neighbour[3][1] == 0 && neighbour[3][2] == 1)
						nCount8++;
					if (neighbour[3][2] == 0 && neighbour[2][2] == 1)
						nCount8++;
					if (neighbour[2][2] == 0 && neighbour[1][2] == 1)
						nCount8++;
					if (neighbour[1][2] == 0 && neighbour[1][1] == 1)
						nCount8++;
					if (nCount8 != 1)
						bCondition4 = TRUE;
				}
				if(bCondition1 && bCondition2 && bCondition3 && bCondition4)
				{
					*lpDst8 = (unsigned char)255;
					bModified = TRUE;
				}
				else
				{
					*lpDst8 = (unsigned char)0;
				}
			}
		}
		// ���Ƹ�ʴ���ͼ��
		memcpy(lpDIBBits2, lpNewDIBBits8, lWidth2 * lHeight2/2);
	}
	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits2, lpNewDIBBits8, lWidth2 * lHeight2/2);

	LocalUnlock(hNewDIBBits8);
	LocalFree(hNewDIBBits8);

/*****************************************************************************/
	long width1,width2,xx1,xx2,xx,yy0;
    //��ʼ����յ������
	long xStartLeft,xStartRight,yStartLeft,yStartRight;

	RECT Rect;
	Rect.top=280;
	Rect.bottom=490;
	Rect.left=0;
	Rect.right=330;

	//����ת�۵�����
	long xLeft1,yLeft1,xRight1,yRight1,yTurn1;

	// ָ��Դͼ���ָ��
	LPSTR	lpSrc9;
	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst9;
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits9;
	HLOCAL	hNewDIBBits9;
	//����ֵ
	unsigned char pixel9;

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits9 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	
	// �����ڴ�
	lpNewDIBBits9 = (char * )LocalLock(hNewDIBBits9);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst9 = (char *)lpNewDIBBits9;
	memset(lpDst9, (BYTE)255, lWidth2 * lHeight2/2);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	width1=lWidth2/2;
	width2=lWidth2/2;
	long flag1=0;
	long flag2=0;

	char situation='M';

	for(xx=0;xx<=lWidth2;xx++)
	{
		lpSrc9 = (char *)lpDIBBits2 + lLineBytes * 0 + xx;		
		lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * 0 + xx;
		pixel9 = (unsigned char)*lpSrc9;

		if(pixel9==0)
		{
			if(xx<=lWidth2/2)
				situation='L';
			else
				situation='R';
			break;
		}
	}

	switch(situation)
	{
	case 'L':
		yStartLeft=0;
		xStartRight=0;
		for(xx=0;xx<=lWidth2/2;xx++)
		{
			lpSrc9 = (char *)lpDIBBits2 + lLineBytes * 0 + xx;		
			lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * 0 + xx;
			pixel9 = (unsigned char)*lpSrc9;

			if(pixel9==0)
			{
				*lpDst9 = (unsigned char)0;
				xStartLeft=xx;
				break;
			}
		}
		for(yy0=0;yy0<lHeight2/2;yy0++)
		{
			lpSrc9 = (char *)lpDIBBits2 + lLineBytes * yy0 + lWidth2;		
			lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * yy0 + lWidth2;
			pixel9 = (unsigned char)*lpSrc9;

			if(pixel9==0)
			{
				*lpDst9 = (unsigned char)0;
				yStartRight=yy0;
				break;
			}
		}
		//Ȼ��������
		break;

	case 'R':
		xStartLeft=0;
		yStartRight=0;
		for(yy0=0;yy0<lHeight2/2;yy0++)
		{
			lpSrc9 = (char *)lpDIBBits2 + lLineBytes * yy0;		
			lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * yy0;
			pixel9 = (unsigned char)*lpSrc9;

			if(pixel9==0)
			{
				*lpDst9 = (unsigned char)0;
				yStartLeft=yy0;
				break;
			}
		}
		for(xx=lWidth2/2;xx<lWidth2;xx++)
		{
			lpSrc9 = (char *)lpDIBBits2 + lLineBytes * 0 + xx;		
			lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * 0 + xx;
			pixel9 = (unsigned char)*lpSrc9;

			if(pixel9==0)
			{
				*lpDst9 = (unsigned char)0;
				xStartRight=xx;
				break;
			}
		}
		//Ȼ��������
		break;

	case 'M':
		/**********************���ʼ��***********************************/

		for(yy0=5;yy0<lHeight2/2;yy0++)
		{
			int flag=0;
			for(xx1=10;xx1>0;xx1--)
			{
				lpSrc9 = (char *)lpDIBBits2 + lLineBytes * yy0 + xx1;		
				lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * yy0 + xx1;
				pixel9 = (unsigned char)*lpSrc9;

				if(pixel9==0)
				{
					*lpDst9 = (unsigned char)0;
					xStartLeft=xx1;
					yStartLeft=yy0;
					flag=1;
					break;
				}
			}
			 if(flag)   
                break; 
		}

		for(yy0=5;yy0<lHeight2/2;yy0++)
		{
			int flag=0;
			for(xx2=lWidth2-10;xx2<lWidth2;xx2++)
			{
				lpSrc9 = (char *)lpDIBBits2 + lLineBytes * yy0 + xx2;		
				lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * yy0 + xx2;
				pixel9 = (unsigned char)*lpSrc9;

				if(pixel9==0)
				{
					*lpDst9 = (unsigned char)0;
					xStartRight=xx2;
					yStartRight=yy0;
					flag=1;
					break;
				}
			}
			 if(flag)   
                break; 
		}

/*****************�ڡ���ǰλ�á��Ի�����ʵʱ��ʾ*************************/ 
		UpdateData(TRUE); 
		m_xStartLeft=2*xStartLeft;
		m_xStartRight=2*xStartRight;
		m_yStartLeft=2*yStartLeft;
		m_yStartRight=2*yStartRight;

		CString	str1; 
		CString	str2; 
		CString	str3; 
		CString	str4; 

		str1.Format("%d", m_xStartLeft);   
		str2.Format("%d", m_xStartRight); 
		str3.Format("%d", m_yStartLeft); 
		str4.Format("%d", m_yStartRight); 

		GetDlgItem(IDC_xStartLeft)->SetWindowText(str1); 
		GetDlgItem(IDC_xStartRight)->SetWindowText(str2);  
		GetDlgItem(IDC_yStartLeft)->SetWindowText(str3);  
		GetDlgItem(IDC_yStartRight)->SetWindowText(str4);  

		UpdateData(FALSE);

////////////////////////////���////////////////////////////////////////////////////

		yLeft1=lHeight2/2;
		yRight1=lHeight2/2;
	
		for(yy0=yStartLeft+1;yy0<lHeight2/2;yy0++)
		{
			for(xx1=lWidth2/2-width1+1;xx1<lWidth2/2;xx1++)
			{
				lpSrc9 = (char *)lpDIBBits2 + lLineBytes * yy0 + xx1;		
				lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * yy0 + xx1;
				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel9 = (unsigned char)*lpSrc9;
        
				if(pixel9==255)
					*lpDst9 = (unsigned char)255;
				else
				{
					*lpDst9 = (unsigned char)0;
					width1 = lWidth2/2-xx1;
					break;   //��ֹ�ڲ�ѭ��
				}		
			}

			if(xx1>=lWidth2/2)
				flag1++;
			if(flag1>10)
			{
				yLeft1=yy0-10;
				break;
			}
		}
		xLeft1=lWidth2/2-width1;

//////////////////////////�ұ�////////////////////////////////////////////
		for(yy0=yStartRight+1;yy0<lHeight2/2;yy0++)
		{
			for(xx2=lWidth2/2+width2-1;xx2>lWidth2/2;xx2--)
			{		
				lpSrc9 = (char *)lpDIBBits2 + lLineBytes * yy0 + xx2;		
				lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * yy0 + xx2;
				pixel9 = (unsigned char)*lpSrc9;
				
				if(pixel9==255)
					*lpDst9 = (unsigned char)255;
				else
				{
					*lpDst9 = (unsigned char)0;
					width2 = xx2-lWidth2/2;
					break;   //��ֹ�ڲ�ѭ��
				}			
			}

			if(xx2<=lWidth2/2)
				flag2++;
			if(flag2>10)
			{
				yRight1=yy0-10;
				break;
			}
		}
		xRight1=lWidth2/2+width2;

/////////////////////////ȷ��ת�۵�ĺ�������///////////////////////////////
		if(yLeft1<=yRight1)
		{
			yTurn1=yLeft1;
			for(xx2=xLeft1+1;xx2<lWidth2;xx2++)
			{		
				lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * yTurn1 + xx2;
				if(*lpDst9==0)
				{
					xRight1=xx2;
					break;
				}
			}	
		}
		else
		{
			yTurn1=yRight1;
			for(xx1=xRight1-1;xx1>0;xx1--)
			{		
				lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * yTurn1 + xx1;
				if(*lpDst9==0)
				{
					xLeft1=xx1;
					break;
				}
			}
		}
/*****************�ڱ༭������ʾת�۵㼰�������Ϣ*****************/
		double StartDirectionL;
		double StartDirectionR;
		double StartDirection;

		if((xLeft1-xStartLeft)!=0)
			StartDirectionL=atan((double)(yTurn1-yStartLeft)/(double)(xLeft1-xStartLeft))*180/pi;
		else
			StartDirectionL=90.0;

		if((xRight1-xStartRight)!=0)
			StartDirectionR=180+atan((double)(yTurn1-yStartRight)/(double)(xRight1-xStartRight))*180/pi;
		else
			StartDirectionR=90.0;

		StartDirection=(double)((double)StartDirectionL+(double)StartDirectionR)/2;

		UpdateData(TRUE);
		m_xLeft1=2*xLeft1;
		m_xRight1=2*xRight1;
		m_yLeft1=2*yLeft1;
		m_yRight1=2*yRight1;
		m_K1=(double)(yTurn1-yStartLeft)/(double)(xLeft1-xStartLeft);
		m_b1=2*((double)(yStartLeft+yTurn1)-(double)m_K1*(double)(xStartLeft+xLeft1))/2;
		m_K2=(double)(yTurn1-yStartRight)/(double)(xRight1-xStartRight);
		m_b2=2*((double)(yStartRight+yTurn1)-(double)m_K2*(double)(xStartRight+xRight1))/2;
		m_MX0=(m_b2-m_b1)/(m_K1-m_K2);
		m_MY0=(m_K1*m_b2-m_K2*m_b1)/(m_K1-m_K2);
		if(StartDirection!=90)
		{
			m_K=tan(StartDirection);
			m_b=(m_K1*m_b2-m_K2*m_b1)/(m_K1-m_K2)+m_K*(m_b1-m_b2)/(m_K1-m_K2);
			m_le=-m_b/m_K-320;
		}
		else
			m_le=m_MX0-320;
		m_Theta=90-StartDirection;	
		CString	str5; 
		CString	str6;
		CString	str7;
		CString	str8;
		CString	str9;
		CString	str10;
		CString	str11;
		CString	str12;
		CString	str13;
		CString	str14;
		CString	str15;
		CString	str16;
		CString str17;
		CString str18;
		str5.Format("%d", m_xLeft1);   
		str6.Format("%d", m_xRight1); 
		str7.Format("%d", m_yLeft1); 
		str8.Format("%d", m_yRight1);
		str9.Format("%d", m_K1); 
		str10.Format("%d", m_b1); 
		str11.Format("%d", m_K2); 
		str12.Format("%d", m_b2); 
		str13.Format("%d", m_K); 
		str14.Format("%d", m_b); 
		str15.Format("%d", m_Theta);
		str16.Format("%d", m_le);
		str17.Format("%d", m_MX0);
		str18.Format("%d", m_MY0);
		GetDlgItem(IDC_xLeft1)->SetWindowText(str5);  
		GetDlgItem(IDC_xRight1)->SetWindowText(str6);  
		GetDlgItem(IDC_yLeft1)->SetWindowText(str7);  
		GetDlgItem(IDC_yRight1)->SetWindowText(str8);  
		GetDlgItem(IDC_K1)->SetWindowText(str9);
		GetDlgItem(IDC_b1)->SetWindowText(str10);
		GetDlgItem(IDC_K2)->SetWindowText(str11);
		GetDlgItem(IDC_b2)->SetWindowText(str12);
		GetDlgItem(IDC_K)->SetWindowText(str13);
		GetDlgItem(IDC_b)->SetWindowText(str14);
		GetDlgItem(IDC_Theta)->SetWindowText(str15);
		GetDlgItem(IDC_le)->SetWindowText(str16);
		GetDlgItem(IDC_MX0)->SetWindowText(str17);
		GetDlgItem(IDC_MY0)->SetWindowText(str18);
		UpdateData(FALSE);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		  
//////////////////////////////////////////////////////////////////////////////////////////
/**************************ת�����**************************************************/

/*	long width3,width4;//������߽�����Ϊwidth3,�ұ߽�����Ϊwidth4
	width3=xLeft1;
	width4=xRight1;

	for(yy0=yTurn1;yy0<lHeight2/2;yy0++)
	{
		if(yTurn1==yLeft1)
		{
			for(xx1=width3;xx1>0;xx1--)
			{
				lpSrc9 = (char *)lpDIBBits2 + lLineBytes * yy0 + xx1;		
				lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * yy0 + xx1;
				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel9 = (unsigned char)*lpSrc9;

				if(pixel9==255)
					*lpDst9 = (unsigned char)255;
				else
				{
					*lpDst9 = (unsigned char)0;
					width3 = xx1;
					xx1=-1;   //��ֹ�ڲ�ѭ��
				}
			}
			for(xx2=width4;xx2>width3;xx2--)
			{
				lpSrc9 = (char *)lpDIBBits2 + lLineBytes * yy0 + xx2;		
				lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * yy0 + xx2;
				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel9 = (unsigned char)*lpSrc9;

				if(pixel9==255)
					*lpDst9 = (unsigned char)255;
				else
				{
					*lpDst9 = (unsigned char)0;
					width4 = xx2;
					xx2=-1;   //��ֹ�ڲ�ѭ��
				}
			}
		}
		else
		{
			for(xx2=width4;xx2<lWidth2;xx2++)
			{
				lpSrc9 = (char *)lpDIBBits2 + lLineBytes * yy0 + xx2;		
				lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * yy0 + xx2;
				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel9 = (unsigned char)*lpSrc9;

				if(pixel9==255)
					*lpDst9 = (unsigned char)255;
				else
				{
					*lpDst9 = (unsigned char)0;
					width4 = xx2;
					xx2=1000;   //��ֹ�ڲ�ѭ��
				}
			}
			for(xx1=width3;xx1<width4;xx2++)
			{
				lpSrc9 = (char *)lpDIBBits2 + lLineBytes * yy0 + xx1;		
				lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * yy0 + xx1;
				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel9 = (unsigned char)*lpSrc9;

				if(pixel9==255)
					*lpDst9 = (unsigned char)255;
				else
				{
					*lpDst9 = (unsigned char)0;
					width3 = xx1;
					xx1=1000;   //��ֹ�ڲ�ѭ��
				}
			}	
		}
	}
	
*/

break;
	}

	
///////////////////////////////////////////////////////////////////////////////////////////
	// ����ͼ��
	memcpy(lpDIBBits2, lpNewDIBBits9, lWidth2 * lHeight2/2);
	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits9);
	LocalFree(hNewDIBBits9);

//////////////////////////////////////////////////////////////////////////////////////////////
	/*************************************************************************
                         Hough�任
 ************************************************************************/
	
	// ָ��Դͼ���ָ��
/*	LPSTR	lpSrc10;
	
	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst10;
	
	// ָ��任���ָ��
	LPSTR   lpTrans;
	
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits10;
	HLOCAL	hNewDIBBits10;

	//ָ��任���ָ��
	LPSTR	lpTransArea;
	HLOCAL	hTransArea;

	//�任��ĳߴ�
	int iMaxDist;
	int iMaxAngleNumber;

	//�任�������
	int iDist;
	int iAngleNumber;

	//ѭ������
	long iii;
	long jjj;

	//����ֵ
	unsigned char pixel10;

	//�洢�任���е��������ֵ
	MaxValue MaxValue1;
	MaxValue MaxValue2;

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits10 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	
	// �����ڴ�
	lpNewDIBBits10 = (char * )LocalLock(hNewDIBBits10);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst10 = (char *)lpNewDIBBits10;
	memset(lpDst10, (BYTE)255, lWidth2 * lHeight2/2);

	//����任��ĳߴ�
	//������
	iMaxDist = (int) sqrt(lWidth2*lWidth2 + lHeight2/2*lHeight2/2);

	//�Ƕȴ�0��180��ÿ��2��
	iMaxAngleNumber = 90;

	//Ϊ�任������ڴ�
	hTransArea = LocalAlloc(LHND, lWidth2 * lHeight2/2 * sizeof(int));

	// �����ڴ�
	lpTransArea = (char * )LocalLock(hTransArea);
		
	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ0
	lpTrans = (char *)lpTransArea;
	memset(lpTrans, 0, lWidth2 * lHeight2/2 * sizeof(int));


	for(jjj = 0; jjj <lHeight2/2; jjj++)
	{
		for(iii = 0;iii <lWidth2; iii++)
		{

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc10 = (char *)lpDIBBits2 + lLineBytes2 * jjj + iii;

			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel10 = (unsigned char)*lpSrc10;

			//����ǰ׵㣬���ڱ任��Ķ�Ӧ�����ϼ�1
			if(pixel10 == 0)
			{
				//ע�ⲽ����2��
				for(iAngleNumber=0; iAngleNumber<iMaxAngleNumber; iAngleNumber++)
				{
					iDist = (int) fabs(iii*cos(iAngleNumber*2*pi/180.0) + \
						jjj*sin(iAngleNumber*2*pi/180.0));
				
					//�任��Ķ�Ӧ���ϼ�1
					*(lpTransArea+iDist*iMaxAngleNumber+iAngleNumber) = \
						*(lpTransArea+iDist*iMaxAngleNumber+iAngleNumber) +1;
				}

				
			}
		
		}
	}

	//�ҵ��任���е��������ֵ��
	MaxValue1.Value=0;
	MaxValue2.Value=0;
	
	//�ҵ���һ�����ֵ��
	for (iDist=0; iDist<iMaxDist;iDist++)
	{
		for(iAngleNumber=0; iAngleNumber<iMaxAngleNumber; iAngleNumber++)
		{
			if((int)*(lpTransArea+iDist*iMaxAngleNumber+iAngleNumber)>MaxValue1.Value)
			{
				MaxValue1.Value = (int)*(lpTransArea+iDist*iMaxAngleNumber+iAngleNumber);
				MaxValue1.Dist = iDist;
				MaxValue1.AngleNumber = iAngleNumber;
			}

		}
	}

	//����һ�����ֵ�㸽������
	for (iDist = -9;iDist < 10;iDist++)
	{
		for(iAngleNumber=-1; iAngleNumber<2; iAngleNumber++)
		{
			if(iDist+MaxValue1.Dist>=0 && iDist+MaxValue1.Dist<iMaxDist \
				&& iAngleNumber+MaxValue1.AngleNumber>=0 && iAngleNumber+MaxValue1.AngleNumber<=iMaxAngleNumber)
			{
				*(lpTransArea+(iDist+MaxValue1.Dist)*iMaxAngleNumber+\
					(iAngleNumber+MaxValue1.AngleNumber))=0;
			}
		}
	}

	//�ҵ��ڶ������ֵ��
	for (iDist=0; iDist<iMaxDist;iDist++)
	{
		for(iAngleNumber=0; iAngleNumber<iMaxAngleNumber; iAngleNumber++)
		{
			if((int)*(lpTransArea+iDist*iMaxAngleNumber+iAngleNumber)>MaxValue2.Value)
			{
				MaxValue2.Value = (int)*(lpTransArea+iDist*iMaxAngleNumber+iAngleNumber);
				MaxValue2.Dist = iDist;
				MaxValue2.AngleNumber = iAngleNumber;
			}

		}
	}

	
		for(jjj = 0; jjj <lHeight2/2; jjj++)
		{
			for(iii = 0;iii <lWidth2; iii++)
			{	

				// ָ�򻺴�ͼ������j�У���i�����ص�ָ��			
				lpDst10 = (char *)lpNewDIBBits10 + lLineBytes * jjj + iii;	

				//�ڵ�һ��ֱ����
				iDist = (int) (iii*cos(MaxValue1.AngleNumber*2*pi/180.0) + \
							jjj*sin(MaxValue1.AngleNumber*2*pi/180.0));
				if (iDist == MaxValue1.Dist)
					*lpDst10 = (unsigned char)0;
				
				//�ڵڶ���ֱ����
				iDist = (int) (iii*cos(MaxValue2.AngleNumber*2*pi/180.0) + \
							jjj*sin(MaxValue2.AngleNumber*2*pi/180.0));
				if (iDist == MaxValue2.Dist)
					*lpDst10 = (unsigned char)0;
				
			}
		}


	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits2, lpNewDIBBits10, lWidth2 * lHeight2/2);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits10);
	LocalFree(hNewDIBBits10);

	// �ͷ��ڴ�
	LocalUnlock(hTransArea);
	LocalFree(hTransArea);
*/
//////////////////////////////////////////////////////////////////////////////////////////////
//�������
::GlobalUnlock ((HGLOBAL)hDIB2);
//////////////////////////////////////////////////////////////////////////////////////////////

    nFile.Open("C:\\image.bmp",CFile::modeWrite | CFile::modeCreate);
	SaveDIB(hDIB2, nFile);

    nFile.Close();
	
    ShowPic("C:\\image.bmp",hwndAnalysis,640,480);
	
	capPreview(hwndVideo,TRUE); 
	CDialog::OnTimer(nIDEvent);
}

/*********************ֹͣ�ɼ�*****************************/
void CBiYeSheJiDlg::OnStopcap() 
{
	// TODO: Add your control notification handler code here
	
}
/***********************************************************/
/**************ǰ�С���ת����ת��������ͣ��*****************/

void CBiYeSheJiDlg::OnGo() 
{
	// TODO: Add your control notification handler code here
	
}

void CBiYeSheJiDlg::OnLeft() 
{
	// TODO: Add your control notification handler code here
	
}

void CBiYeSheJiDlg::OnRight() 
{
	// TODO: Add your control notification handler code here
	
}

void CBiYeSheJiDlg::OnBack() 
{
	// TODO: Add your control notification handler code here
	
}

void CBiYeSheJiDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	
}



void CBiYeSheJiDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	//���ñ�����ɫ
	CRect rect;
	GetClientRect(&rect); //����Ի���ĳߴ�
	dc.FillSolidRect(&rect,RGB(208,255,208)); //���ƶԻ��򱳾�ɫ
	
	//����ģ����ͼԲ
/*	CClientDC m_dc(this);
	//���Բ����
	CRgn rgn; 
	CRect rect1(10, 280, 200, 470);//Բ�����꣨105��375��
	rgn.CreateEllipticRgnIndirect(&rect1);
	CBrush brush(RGB(0,0,0));
	m_dc.FillRgn(&rgn,&brush);	*/
}

/*HBRUSH CBiYeSheJiDlg::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC,pWnd,nCtlColor);
	return m_brush;
//	return hbr;
}*/
