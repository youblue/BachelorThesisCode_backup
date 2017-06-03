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
			AfxMessageBox("设备没有初始化!");
			AfxGetMainWnd()->PostMessage(WM_CLOSE);
		}
	}
	else
	{
		AfxMessageBox("设备没连接!");
		AfxGetMainWnd()->PostMessage(WM_CLOSE);
	}
	if(capPreview(hwndVideo,FALSE))
		capPreview(hwndVideo,TRUE);

	capCaptureGetSetup(hwndVideo,&m_Parms,sizeof(m_Parms));
    if(capCaptureGetSetup(hwndVideo,&m_Parms,sizeof(m_Parms))==TRUE)
	{}
	else
		AfxMessageBox("摄像头不能正常工作!请检查后，再试!");
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
	
	// 由DIB句柄得到DIB指针并锁定DIB
    lpDIB1 = (LPSTR) ::GlobalLock((HGLOBAL)hDIB1);
	lpDIB2 = (LPSTR) ::GlobalLock((HGLOBAL)hDIB2);

	// 指向DIB象素数据区的指针
	LPSTR   lpDIBBits1;	
	LPSTR   lpDIBBits2;	

	// 指向DIB象素的指针
//	BYTE *	lpSrc1;	

	// 图像宽度
	LONG	lWidth1;	
	LONG	lWidth2;
	// 图像高度
    LONG  	lHeight1;
	LONG  	lHeight2;
	

	// 图像每行的字节数
	LONG	lLineBytes1;
	LONG	lLineBytes2;

	// 指向BITMAPINFO结构的指针（Win3.0）
	LPBITMAPINFO lpbmi1;	

	// 指向BITMAPCOREINFO结构的指针
	LPBITMAPCOREINFO lpbmc1;
	
	// 获取指向BITMAPINFO结构的指针（Win3.0）
	lpbmi1 = (LPBITMAPINFO)lpDIB1;	

	// 获取指向BITMAPCOREINFO结构的指针
	lpbmc1 = (LPBITMAPCOREINFO)lpDIB1;	

	// 灰度映射表
//	BYTE bMap[256];
	BYTE r,g,b;

	// 找到DIB图像象素起始位置
	lpDIBBits1 = ::FindDIBBits(lpDIB1);
	lpDIBBits2 = ::FindDIBBits(lpDIB2);
		
	// 获取图像宽度
	lWidth1 = ::DIBWidth(lpDIB1);	
	lWidth2 = ::DIBWidth(lpDIB2);

	// 获取图像高度
	lHeight1 = ::DIBHeight(lpDIB1);	
	lHeight2 = ::DIBHeight(lpDIB2);	

	// 计算图像每行的字节数
	lLineBytes1 = WIDTHBYTES(lWidth1 * 24);	
	lLineBytes2 = WIDTHBYTES(lWidth1 * 8);	

// 更换每个象素的颜色索引（即按照灰度映射表换成灰度值）

//逐行扫描
for(int i = 0; i < lHeight1; i++)
{
  //逐列扫描
  for(int j = 0; j < lLineBytes1; j++)
  {
	  // 获取各颜色分量
			r = *((unsigned char *)lpDIBBits1 + lLineBytes1 * i + j);
			j++;
			g = *((unsigned char *)lpDIBBits1 + lLineBytes1 * i + j);
			j++;
			b = *((unsigned char *)lpDIBBits1 + lLineBytes1 * i + j);

			// 计算灰度值
			BYTE Y = (9798 * r + 19235 * g + 3735 * b) / 32768;
 
			// 回写灰度值
			*((unsigned char *)lpDIBBits1 + lLineBytes1 * i + j - 2) = Y;
			*((unsigned char *)lpDIBBits1 + lLineBytes1 * i + j - 1) = Y;
			*((unsigned char *)lpDIBBits1 + lLineBytes1 * i + j ) = Y;

            *((unsigned char *)lpDIBBits2 + lLineBytes2 * i + (j - 2)/3)=Y;
  }
}
//解除锁定
::GlobalUnlock ((HGLOBAL)hDIB1);

//////////////////////////////////////////////////////////////////////////////////////////////
/***************************/
/**********中值滤波*********/
/***************************/
/*****************************************************
* 
*   函数名称：
*      Template：
*
*    参数：
*	   HDIB    hDIB         －图像的句柄
*      int  tem_w           －模板的宽度
*      int  tem_h           －模板的高度
*      
*    功能：
*	   对图像进行中值
*
*    说明：
*	   为处理方便起见，模板的宽度和高度都应为奇数
*******************************************************/

    //统计中间值
    double mid;

	BYTE *temp=(BYTE*)malloc(640*240*8);//只处理1/3图像

    //指向图像起始位置的指针
    BYTE *lpDIB=(BYTE*)::GlobalLock((HGLOBAL) hDIB2);

	//指向象素起始位置的指针
	BYTE *pScrBuff =(BYTE*)::FindDIBBits((char*)lpDIB2);
   
	//获取图像的颜色信息
    int numColors=(int) ::DIBNumColors((char *)lpDIB2);

    //将指向图像象素起始位置的指针，赋值给指针变量
    BYTE* oldbuf = pScrBuff;

    //循环变量
    int ii,jj,mm,nn;

	int w, h, dw;

	//获取图像的宽度
	w = (int) ::DIBWidth((char *)lpDIB);
	
	//获取图像的高度
	h = (int) ::DIBHeight((char *)lpDIB);
	
	//计算图像每行的字节数
	dw = (w+3)/4*4;      
	
	//建立一个和原图像大小相同的25色灰度位图
    HDIB newhDIB=NewDIB(w,h,8);  
    
	//指向新的位图的指针
	BYTE *newlpDIB=(BYTE*)::GlobalLock((HGLOBAL) newhDIB);

	//指向新的位图的象素起始位置的指针 
    BYTE *destBuf = (BYTE*)FindDIBBits((char *)newlpDIB);
    
   //将指向新图像象素起始位置的指针，赋值给指针变量
    BYTE *newbuf=destBuf; 
	
	//对图像进行扫描
   
	//行 
    for(ii=0;ii<h;ii++)
    {  
		//列
	   for(jj=0;jj<w;jj++)
	   {   

		   //为统计变量赋初始值
	       

         //对于图像的4个边框的象素保持原灰度不变
	     if( jj<((640-1)/2) || jj>(w-(640+1)/2) || ii<((240-1)/2) || ii>(h-(240+1)/2) )
	      *(newbuf+ii*dw+jj)=*(oldbuf+ii*dw+jj);
		 
         //对于其他的象素进行模板操作
		 else 
         { 

          //将点（i,j）点作为模板的中心
          for(mm=ii-((240-1)/2);mm<=ii+((240-1)/2);mm++)
          {
		     for(nn=jj-((640-1)/2);nn<=jj+((640-1)/2);nn++)
		    
             //将以点（i，j）为中心，与模板大小相同的范围内的象素传递到模板矩阵中
		     temp[(mm-i+((240-1)/2))*640+nn-jj+((640-1)/2)]=*(oldbuf+mm*dw+nn);
		  
		  }
          
		 //利用气泡法计算中值
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

           //将计算的结果放到新的位图的相应位置
	      *(newbuf+ii*dw+jj)=temp[(640*240-1)/2];
		 }
	   }
	} 
   

//////////////////////////////////////////////////////////////////////////////////////////////

/***************************/
/**********SOBEL************///只处理1/3图像
/***************************/
// 指向缓存图像的指针
	LPSTR	lpDst1;
	LPSTR	lpDst2;
	
	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	LPSTR	lpNewDIBBits2;
	HLOCAL	hNewDIBBits2;

	//循环变量
	long m;
	long n;

	// 模板高度
	int		iTempH;
	
	// 模板宽度
	int		iTempW;
	
	// 模板系数
	FLOAT	fTempC;
	
	// 模板中心元素X坐标
	int		iTempMX;
	
	// 模板中心元素Y坐标
	int		iTempMY;
	
	//模板数组
	FLOAT aTemplate[9];

	// 暂时分配内存，以保存新图像
	hNewDIBBits1 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	
	// 锁定内存
	lpNewDIBBits1 = (char * )LocalLock(hNewDIBBits1);

	// 暂时分配内存，以保存新图像
	hNewDIBBits2 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	
	// 锁定内存
	lpNewDIBBits2 = (char * )LocalLock(hNewDIBBits2);

	// 拷贝源图像到缓存图像中
	lpDst1 = (char *)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits2, lWidth2 * lHeight2/2);
	lpDst2 = (char *)lpNewDIBBits2;
	memcpy(lpNewDIBBits2, lpDIBBits2, lWidth2 * lHeight2/2);

	// 设置Sobel模板参数
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

	// 调用Template()函数
	Template(lpNewDIBBits1, lWidth2, lHeight2/2, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC);

	// 设置Sobel模板参数
	aTemplate[0] = -1.0;
	aTemplate[1] = 0.0;
	aTemplate[2] = 1.0;
	aTemplate[3] = -2.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 2.0;
	aTemplate[6] = -1.0;
	aTemplate[7] = 0.0;
	aTemplate[8] = 1.0;

	// 调用Template()函数
	Template(lpNewDIBBits2, lWidth2, lHeight2/2, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC);


	//求两幅缓存图像的最大值
	for(n = 0; n <lHeight2/2; n++)
	{
		for(m = 0;m <lWidth2-1; m++)
		{

			// 指向缓存图像1倒数第j行，第i个象素的指针			
			lpDst1 = (char *)lpNewDIBBits1 + lWidth2 * n + m;

			// 指向缓存图像2倒数第j行，第i个象素的指针			
			lpDst2 = (char *)lpNewDIBBits2 + lWidth2 * n + m;
			
			if(*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;
		
		}
	}

	// 复制经过模板运算后的图像到源图像
	memcpy(lpDIBBits2, lpNewDIBBits1, lWidth2 * lHeight2/2);

	// 释放内存
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	LocalUnlock(hNewDIBBits2);
	LocalFree(hNewDIBBits2);
//////////////////////////////////////////////////////////////////////////////////////////////

/***************************/
/********阈值分割***********///只处理1/3图像
/***************************/
   // 指向源图像的指针
	LPSTR	lpSrc;
	
	// 指向缓存图像的指针
	LPSTR	lpDst;
	
	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//循环变量
	long u;
	long v;

	//像素值
	unsigned char pixel;

	//直方图数组
	long lHistogram[256];

	//阈值，最大灰度值与最小灰度值，两个区域的平均灰度值
	unsigned char iThreshold,iNewThreshold,iMaxGrayValue,iMinGrayValue,iMean1GrayValue,iMean2GrayValue;

	//用于计算区域灰度平均值的中间变量
	long lP1,lP2,lS1,lS2;

	//迭代次数
	int iIterationTimes;

	// 图像每行的字节数
	LONG lLineBytes;

	// 暂时分配内存，以保存新图像
	hNewDIBBits = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	
	// 锁定内存
	lpNewDIBBits = (char * )LocalLock(hNewDIBBits);

	// 初始化新分配的内存，设定初始值为255
	lpDst = (char *)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth2 * lHeight2/2);

	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth2 * 8);

	for (u = 0; u < 256;u++)
	{
		lHistogram[u]=0;
	}

	//获得直方图
	iMaxGrayValue = 0;
	iMinGrayValue = 255;
	for (u = 0;u < lWidth2 ;u++)
	{
		for(v = 0;v < lHeight2/2 ;v++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char *)lpDIBBits2 + lLineBytes * v + u;
	
			pixel = (unsigned char)*lpSrc;
			
			lHistogram[pixel]++;
			//修改最大，最小灰度值
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

	//迭代求最佳阈值
	iNewThreshold = (iMinGrayValue + iMaxGrayValue)/2;
	iThreshold = 0;
	
	for(iIterationTimes = 0; iThreshold != iNewThreshold && iIterationTimes < 100;iIterationTimes ++)
	{
		iThreshold = iNewThreshold;
		lP1 =0;
		lP2 =0;
		lS1 = 0;
		lS2 = 0;
		//求两个区域的灰度平均值
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

	//根据阈值将图像二值化
	for (u = 0;u < lWidth2 ;u++)
	{
		for(v = 0;v < lHeight2/2 ;v++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc = (char *)lpDIBBits2 + lLineBytes * v + u;
	
			// 指向目标图像倒数第j行，第i个象素的指针			
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

	// 复制图像
	memcpy(lpDIBBits2, lpNewDIBBits, lWidth2 * lHeight2/2);

	// 释放内存
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

//////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************
                         道路边界搜索算法
 ************************************************************************/
	////////////////////////////
	//1、反色处理图像的下1/3部分
	////////////////////////////

	 // 指向源图像的指针
	LPSTR	lpSrc3;
	// 指向缓存图像的指针
	LPSTR	lpDst3;
	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits3;
	HLOCAL	hNewDIBBits3;
	//像素值
	unsigned char pixel3;

	// 暂时分配内存，以保存新图像
	hNewDIBBits3 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	
	// 锁定内存
	lpNewDIBBits3 = (char * )LocalLock(hNewDIBBits3);

	// 初始化新分配的内存，设定初始值为255
	lpDst3 = (char *)lpNewDIBBits3;
	memset(lpDst3, (BYTE)255, lWidth2 * lHeight2/2);

	//反色
	for(long yy = 0; yy <lHeight2/2; yy++)
	{
		for(long xx = 0;xx <lWidth2; xx++)
		{			
			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc3 = (char *)lpDIBBits2 + lWidth2 * yy + xx;			
			// 指向目标图像倒数第j行，第i个象素的指针			
			lpDst3 = (char *)lpNewDIBBits + lWidth2 * yy + xx;			
			//取得当前指针处的像素值，注意要转换为unsigned char型
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
    // 复制图像
	memcpy(lpDIBBits2, lpNewDIBBits3, lWidth2 * lHeight2/2);
	// 释放内存
	LocalUnlock(hNewDIBBits3);
	LocalFree(hNewDIBBits3);

/*************************************************************************
 * 2、
 * （1）  膨胀第1次
 ************************************************************************/
	
	LPSTR	lpSrc4;			// 指向源图像的指针	
	LPSTR	lpDst4;			// 指向缓存图像的指针	
	LPSTR	lpNewDIBBits4;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits4;	
	long i4,j4,m4,n4;		//循环变量	
	unsigned char pixel4;	//像素值

	// 暂时分配内存，以保存新图像
	hNewDIBBits4 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	lpNewDIBBits4 = (char * )LocalLock(hNewDIBBits4);

	// 初始化新分配的内存，设定初始值为255
	lpDst4 = (char *)lpNewDIBBits4;
	memset(lpDst4, (BYTE)255, lWidth2 * lHeight2/2);

	//使用自定义的结构元素进行膨胀
	for(j4 = 1; j4 <lHeight2/2-1; j4++)
	{
		for(i4 = 0;i4 <lWidth2; i4++)
		{
			// 由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边
			// 的两列像素和最上边和最下边的两列像素

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc4 = (char *)lpDIBBits2 + lWidth2 * j4 + i4;
			// 指向目标图像倒数第j行，第i个象素的指针			
			lpDst4 = (char *)lpNewDIBBits4 + lWidth2 * j4 + i4;
			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixel4 = (unsigned char)*lpSrc4;

			//目标图像中的当前点先赋成白色
			*lpDst4 = (unsigned char)255;

			//原图像中对应结构元素中为黑色的那些点中只要有一个是黑色，
			//则将目标图像中的当前点赋成黑色
			//注意在DIB图像中内容是上下倒置的
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
	// 复制膨胀后的图像
	memcpy(lpDIBBits2, lpNewDIBBits4, lWidth2 * lHeight2/2);

	LocalUnlock(hNewDIBBits4);
	LocalFree(hNewDIBBits4);

/*************************************************************************
 * 
 * （2）膨胀第2次
 ************************************************************************/
	
	LPSTR	lpSrc5;			// 指向源图像的指针	
	LPSTR	lpDst5;			// 指向缓存图像的指针	
	LPSTR	lpNewDIBBits5;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits5;	
	long i5,j5,m5,n5;		//循环变量	
	unsigned char pixel5;	//像素值

	// 暂时分配内存，以保存新图像
	hNewDIBBits5 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	lpNewDIBBits5 = (char * )LocalLock(hNewDIBBits5);

	// 初始化新分配的内存，设定初始值为255
	lpDst5 = (char *)lpNewDIBBits5;
	memset(lpDst5, (BYTE)255, lWidth2 * lHeight2/2);

	//使用自定义的结构元素进行膨胀
	for(j5 = 1; j5 <lHeight2/2-1; j5++)
	{
		for(i5 = 0;i5 <lWidth2; i5++)
		{
			// 由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边
			// 的两列像素和最上边和最下边的两列像素

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc5 = (char *)lpDIBBits2 + lWidth2 * j5 + i5;
			// 指向目标图像倒数第j行，第i个象素的指针			
			lpDst5 = (char *)lpNewDIBBits5 + lWidth2 * j5 + i5;
			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixel5 = (unsigned char)*lpSrc5;

			//目标图像中的当前点先赋成白色
			*lpDst5 = (unsigned char)255;

			//原图像中对应结构元素中为黑色的那些点中只要有一个是黑色，
			//则将目标图像中的当前点赋成黑色
			//注意在DIB图像中内容是上下倒置的
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
	// 复制膨胀后的图像
	memcpy(lpDIBBits2, lpNewDIBBits5, lWidth2 * lHeight2/2);

	LocalUnlock(hNewDIBBits5);
	LocalFree(hNewDIBBits5);
/*************************************************************************
 * 
 * （3）膨胀第3次
 ************************************************************************/
	
	LPSTR	lpSrc6;			// 指向源图像的指针	
	LPSTR	lpDst6;			// 指向缓存图像的指针	
	LPSTR	lpNewDIBBits6;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits6;	
	long i6,j6,m6,n6;		//循环变量	
	unsigned char pixel6;	//像素值

	// 暂时分配内存，以保存新图像
	hNewDIBBits6 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	lpNewDIBBits6 = (char * )LocalLock(hNewDIBBits6);

	// 初始化新分配的内存，设定初始值为255
	lpDst6 = (char *)lpNewDIBBits6;
	memset(lpDst6, (BYTE)255, lWidth2 * lHeight2/2);

	//使用自定义的结构元素进行膨胀
	for(j6 = 1; j6 <lHeight2/2-1; j6++)
	{
		for(i6 = 0;i6 <lWidth2; i6++)
		{
			// 由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边
			// 的两列像素和最上边和最下边的两列像素

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc6 = (char *)lpDIBBits2 + lWidth2 * j6 + i6;
			// 指向目标图像倒数第j行，第i个象素的指针			
			lpDst6 = (char *)lpNewDIBBits6 + lWidth2 * j6 + i6;
			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixel6 = (unsigned char)*lpSrc6;

			//目标图像中的当前点先赋成白色
			*lpDst6 = (unsigned char)255;

			//原图像中对应结构元素中为黑色的那些点中只要有一个是黑色，
			//则将目标图像中的当前点赋成黑色
			//注意在DIB图像中内容是上下倒置的
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
	// 复制膨胀后的图像
	memcpy(lpDIBBits2, lpNewDIBBits6, lWidth2 * lHeight2/2);

	LocalUnlock(hNewDIBBits6);
	LocalFree(hNewDIBBits6);
	/*************************************************************************
 * 
 * （3）膨胀第4次
 ************************************************************************/
	
	LPSTR	lpSrc11;			// 指向源图像的指针	
	LPSTR	lpDst11;			// 指向缓存图像的指针	
	LPSTR	lpNewDIBBits11;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits11;	
	long i11,j11,m11,n11;		//循环变量	
	unsigned char pixel11;	//像素值

	// 暂时分配内存，以保存新图像
	hNewDIBBits11 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	lpNewDIBBits11 = (char * )LocalLock(hNewDIBBits11);

	// 初始化新分配的内存，设定初始值为255
	lpDst11 = (char *)lpNewDIBBits11;
	memset(lpDst11, (BYTE)255, lWidth2 * lHeight2/2);

	//使用自定义的结构元素进行膨胀
	for(j11 = 1; j11 <lHeight2/2-1; j11++)
	{
		for(i11 = 0;i11 <lWidth2; i11++)
		{
			// 由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边
			// 的两列像素和最上边和最下边的两列像素

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc11 = (char *)lpDIBBits2 + lWidth2 * j11 + i11;
			// 指向目标图像倒数第j行，第i个象素的指针			
			lpDst11 = (char *)lpNewDIBBits11 + lWidth2 * j11 + i11;
			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixel11 = (unsigned char)*lpSrc11;

			//目标图像中的当前点先赋成白色
			*lpDst11 = (unsigned char)255;

			//原图像中对应结构元素中为黑色的那些点中只要有一个是黑色，
			//则将目标图像中的当前点赋成黑色
			//注意在DIB图像中内容是上下倒置的
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
	// 复制膨胀后的图像
	memcpy(lpDIBBits2, lpNewDIBBits11, lWidth2 * lHeight2/2);

	LocalUnlock(hNewDIBBits11);
	LocalFree(hNewDIBBits11);
	/*************************************************************************
	* 
	*（4）腐蚀
	************************************************************************/
	
	LPSTR	lpSrc7;			// 指向源图像的指针	
	LPSTR	lpDst7;			// 指向缓存图像的指针	
	LPSTR	lpNewDIBBits7;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits7;	
	long i7,j7,n7,m7;			//循环变量
	unsigned char pixel7;	//像素值

	// 暂时分配内存，以保存新图像
	hNewDIBBits7 = LocalAlloc(LHND, lWidth2 * lHeight2/2);	
	lpNewDIBBits7 = (char * )LocalLock(hNewDIBBits7);

	// 初始化新分配的内存，设定初始值为255
	lpDst7 = (char *)lpNewDIBBits7;
	memset(lpDst7, (BYTE)255, lWidth2 * lHeight2/2);

	//使用自定义的结构元素进行腐蚀
	for(j7 = 1; j7 <lHeight2/2-1; j7++)
	{
		for(i7 = 0;i7 <lWidth2; i7++)
		{
			// 由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边
			// 的两列像素和最上边和最下边的两列像素

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc7 = (char *)lpDIBBits2 + lWidth2 * j7 + i7;
			// 指向目标图像倒数第j行，第i个象素的指针			
			lpDst7 = (char *)lpNewDIBBits7 + lWidth2 * j7 + i7;
			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixel7 = (unsigned char)*lpSrc7;

			//目标图像中的当前点先赋成黑色
			*lpDst7 = (unsigned char)0;

			//如果原图像中对应结构元素中为黑色的那些点中有一个不是黑色，
			//则将目标图像中的当前点赋成白色
			//注意在DIB图像中内容是上下倒置的
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
	// 复制腐蚀后的图像
	memcpy(lpDIBBits2, lpNewDIBBits7, lWidth2 * lHeight2/2);

	LocalUnlock(hNewDIBBits7);
	LocalFree(hNewDIBBits7);

	/*************************************************************************
	* 
	*（4）腐蚀2
	************************************************************************/
	
	LPSTR	lpSrc12;			// 指向源图像的指针	
	LPSTR	lpDst12;			// 指向缓存图像的指针	
	LPSTR	lpNewDIBBits12;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits12;	
	long i12,j12,n12,m12;			//循环变量
	unsigned char pixel12;	//像素值

	// 暂时分配内存，以保存新图像
	hNewDIBBits12 = LocalAlloc(LHND, lWidth2 * lHeight2/2);	
	lpNewDIBBits12 = (char * )LocalLock(hNewDIBBits12);

	// 初始化新分配的内存，设定初始值为255
	lpDst12 = (char *)lpNewDIBBits12;
	memset(lpDst12, (BYTE)255, lWidth2 * lHeight2/2);

	//使用自定义的结构元素进行腐蚀
	for(j12 = 1; j12 <lHeight2/2-1; j12++)
	{
		for(i12 = 0;i12 <lWidth2; i12++)
		{
			// 由于使用3×3的结构元素，为防止越界，所以不处理最左边和最右边
			// 的两列像素和最上边和最下边的两列像素

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc12 = (char *)lpDIBBits2 + lWidth2 * j12 + i12;
			// 指向目标图像倒数第j行，第i个象素的指针			
			lpDst12 = (char *)lpNewDIBBits12 + lWidth2 * j12 + i12;
			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixel12 = (unsigned char)*lpSrc12;

			//目标图像中的当前点先赋成黑色
			*lpDst12 = (unsigned char)0;

			//如果原图像中对应结构元素中为黑色的那些点中有一个不是黑色，
			//则将目标图像中的当前点赋成白色
			//注意在DIB图像中内容是上下倒置的
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
	// 复制腐蚀后的图像
	memcpy(lpDIBBits2, lpNewDIBBits12, lWidth2 * lHeight2/2);

	LocalUnlock(hNewDIBBits12);
	LocalFree(hNewDIBBits12);
	/*************************************************************************
 * 
 *  （5）细化

 ************************************************************************/
		
	LPSTR	lpSrc8;			// 指向源图像的指针	
	LPSTR	lpDst8;			// 指向缓存图像的指针	
	LPSTR	lpNewDIBBits8;	// 指向缓存DIB图像的指针
	HLOCAL	hNewDIBBits8;	
	BOOL bModified;			//脏标记	
	long i8,j8,m8,n8;			//循环变量

	//四个条件
	BOOL bCondition1;
	BOOL bCondition2;
	BOOL bCondition3;
	BOOL bCondition4;
	
	unsigned char nCount8;	//计数器	
	unsigned char pixel8;	//像素值	
	unsigned char neighbour[5][5];	//5×5相邻区域像素值

	// 暂时分配内存，以保存新图像
	hNewDIBBits8 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	lpNewDIBBits8 = (char * )LocalLock(hNewDIBBits8);

	// 初始化新分配的内存，设定初始值为255
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

				//由于使用5×5的结构元素，为防止越界，所以不处理外围的几行和几列像素

				// 指向源图像倒数第j行，第i个象素的指针			
				lpSrc8 = (char *)lpDIBBits2 + lWidth2 * j8 + i8;
				// 指向目标图像倒数第j行，第i个象素的指针			
				lpDst8 = (char *)lpNewDIBBits8 + lWidth2 * j8 + i8;
				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel8 = (unsigned char)*lpSrc8;

				//如果源图像中当前点为白色，则跳过
				if(pixel8 == 255)
				{
					continue;
				}

				//获得当前点相邻的5×5区域内像素值，白色用0代表，黑色用1代表
				for (m8 = 0;m8 < 5;m8++ )
				{
					for (n8 = 0;n8 < 5;n8++)
					{
						neighbour[m8][n8] =(255 - (unsigned char)*(lpSrc8 + 
							((4 - m8) - 2)*lWidth2 + n8 - 2 )) / 255;
					}
				}

				//逐个判断条件。
				//判断2<=NZ(P1)<=6
				nCount8 =  neighbour[1][1] + neighbour[1][2] + neighbour[1][3] \
						+ neighbour[2][1] + neighbour[2][3] + \
						+ neighbour[3][1] + neighbour[3][2] + neighbour[3][3];
				if ( nCount8 >= 2 && nCount8 <=6)
				{
					bCondition1 = TRUE;
				}

				//判断Z0(P1)=1
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

				//判断P2*P4*P8=0 or Z0(p2)!=1
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

				//判断P2*P4*P6=0 or Z0(p4)!=1
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
		// 复制腐蚀后的图像
		memcpy(lpDIBBits2, lpNewDIBBits8, lWidth2 * lHeight2/2);
	}
	// 复制腐蚀后的图像
	memcpy(lpDIBBits2, lpNewDIBBits8, lWidth2 * lHeight2/2);

	LocalUnlock(hNewDIBBits8);
	LocalFree(hNewDIBBits8);

/*****************************************************************************/
	long width1,width2,xx1,xx2,xx,yy0;
    //起始点和终点横坐标
	long xStartLeft,xStartRight,yStartLeft,yStartRight;

	RECT Rect;
	Rect.top=280;
	Rect.bottom=490;
	Rect.left=0;
	Rect.right=330;

	//定义转折点坐标
	long xLeft1,yLeft1,xRight1,yRight1,yTurn1;

	// 指向源图像的指针
	LPSTR	lpSrc9;
	// 指向缓存图像的指针
	LPSTR	lpDst9;
	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits9;
	HLOCAL	hNewDIBBits9;
	//像素值
	unsigned char pixel9;

	// 暂时分配内存，以保存新图像
	hNewDIBBits9 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	
	// 锁定内存
	lpNewDIBBits9 = (char * )LocalLock(hNewDIBBits9);

	// 初始化新分配的内存，设定初始值为255
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
		//然后舵机向右
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
		//然后舵机向左
		break;

	case 'M':
		/**********************求初始点***********************************/

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

/*****************在“当前位置”对话框中实时显示*************************/ 
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

////////////////////////////左边////////////////////////////////////////////////////

		yLeft1=lHeight2/2;
		yRight1=lHeight2/2;
	
		for(yy0=yStartLeft+1;yy0<lHeight2/2;yy0++)
		{
			for(xx1=lWidth2/2-width1+1;xx1<lWidth2/2;xx1++)
			{
				lpSrc9 = (char *)lpDIBBits2 + lLineBytes * yy0 + xx1;		
				lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * yy0 + xx1;
				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel9 = (unsigned char)*lpSrc9;
        
				if(pixel9==255)
					*lpDst9 = (unsigned char)255;
				else
				{
					*lpDst9 = (unsigned char)0;
					width1 = lWidth2/2-xx1;
					break;   //中止内层循环
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

//////////////////////////右边////////////////////////////////////////////
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
					break;   //中止内层循环
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

/////////////////////////确定转折点的横纵坐标///////////////////////////////
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
/*****************在编辑框中显示转折点及方向的信息*****************/
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
/**************************转弯后处理**************************************************/

/*	long width3,width4;//定义左边界距左边为width3,右边界距左边为width4
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
				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel9 = (unsigned char)*lpSrc9;

				if(pixel9==255)
					*lpDst9 = (unsigned char)255;
				else
				{
					*lpDst9 = (unsigned char)0;
					width3 = xx1;
					xx1=-1;   //中止内层循环
				}
			}
			for(xx2=width4;xx2>width3;xx2--)
			{
				lpSrc9 = (char *)lpDIBBits2 + lLineBytes * yy0 + xx2;		
				lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * yy0 + xx2;
				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel9 = (unsigned char)*lpSrc9;

				if(pixel9==255)
					*lpDst9 = (unsigned char)255;
				else
				{
					*lpDst9 = (unsigned char)0;
					width4 = xx2;
					xx2=-1;   //中止内层循环
				}
			}
		}
		else
		{
			for(xx2=width4;xx2<lWidth2;xx2++)
			{
				lpSrc9 = (char *)lpDIBBits2 + lLineBytes * yy0 + xx2;		
				lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * yy0 + xx2;
				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel9 = (unsigned char)*lpSrc9;

				if(pixel9==255)
					*lpDst9 = (unsigned char)255;
				else
				{
					*lpDst9 = (unsigned char)0;
					width4 = xx2;
					xx2=1000;   //中止内层循环
				}
			}
			for(xx1=width3;xx1<width4;xx2++)
			{
				lpSrc9 = (char *)lpDIBBits2 + lLineBytes * yy0 + xx1;		
				lpDst9 = (char *)lpNewDIBBits9 + lLineBytes * yy0 + xx1;
				//取得当前指针处的像素值，注意要转换为unsigned char型
				pixel9 = (unsigned char)*lpSrc9;

				if(pixel9==255)
					*lpDst9 = (unsigned char)255;
				else
				{
					*lpDst9 = (unsigned char)0;
					width3 = xx1;
					xx1=1000;   //中止内层循环
				}
			}	
		}
	}
	
*/

break;
	}

	
///////////////////////////////////////////////////////////////////////////////////////////
	// 复制图像
	memcpy(lpDIBBits2, lpNewDIBBits9, lWidth2 * lHeight2/2);
	// 释放内存
	LocalUnlock(hNewDIBBits9);
	LocalFree(hNewDIBBits9);

//////////////////////////////////////////////////////////////////////////////////////////////
	/*************************************************************************
                         Hough变换
 ************************************************************************/
	
	// 指向源图像的指针
/*	LPSTR	lpSrc10;
	
	// 指向缓存图像的指针
	LPSTR	lpDst10;
	
	// 指向变换域的指针
	LPSTR   lpTrans;
	
	// 指向缓存DIB图像的指针
	LPSTR	lpNewDIBBits10;
	HLOCAL	hNewDIBBits10;

	//指向变换域的指针
	LPSTR	lpTransArea;
	HLOCAL	hTransArea;

	//变换域的尺寸
	int iMaxDist;
	int iMaxAngleNumber;

	//变换域的坐标
	int iDist;
	int iAngleNumber;

	//循环变量
	long iii;
	long jjj;

	//像素值
	unsigned char pixel10;

	//存储变换域中的两个最大值
	MaxValue MaxValue1;
	MaxValue MaxValue2;

	// 暂时分配内存，以保存新图像
	hNewDIBBits10 = LocalAlloc(LHND, lWidth2 * lHeight2/2);
	
	// 锁定内存
	lpNewDIBBits10 = (char * )LocalLock(hNewDIBBits10);

	// 初始化新分配的内存，设定初始值为255
	lpDst10 = (char *)lpNewDIBBits10;
	memset(lpDst10, (BYTE)255, lWidth2 * lHeight2/2);

	//计算变换域的尺寸
	//最大距离
	iMaxDist = (int) sqrt(lWidth2*lWidth2 + lHeight2/2*lHeight2/2);

	//角度从0－180，每格2度
	iMaxAngleNumber = 90;

	//为变换域分配内存
	hTransArea = LocalAlloc(LHND, lWidth2 * lHeight2/2 * sizeof(int));

	// 锁定内存
	lpTransArea = (char * )LocalLock(hTransArea);
		
	// 初始化新分配的内存，设定初始值为0
	lpTrans = (char *)lpTransArea;
	memset(lpTrans, 0, lWidth2 * lHeight2/2 * sizeof(int));


	for(jjj = 0; jjj <lHeight2/2; jjj++)
	{
		for(iii = 0;iii <lWidth2; iii++)
		{

			// 指向源图像倒数第j行，第i个象素的指针			
			lpSrc10 = (char *)lpDIBBits2 + lLineBytes2 * jjj + iii;

			//取得当前指针处的像素值，注意要转换为unsigned char型
			pixel10 = (unsigned char)*lpSrc10;

			//如果是白点，则在变换域的对应各点上加1
			if(pixel10 == 0)
			{
				//注意步长是2度
				for(iAngleNumber=0; iAngleNumber<iMaxAngleNumber; iAngleNumber++)
				{
					iDist = (int) fabs(iii*cos(iAngleNumber*2*pi/180.0) + \
						jjj*sin(iAngleNumber*2*pi/180.0));
				
					//变换域的对应点上加1
					*(lpTransArea+iDist*iMaxAngleNumber+iAngleNumber) = \
						*(lpTransArea+iDist*iMaxAngleNumber+iAngleNumber) +1;
				}

				
			}
		
		}
	}

	//找到变换域中的两个最大值点
	MaxValue1.Value=0;
	MaxValue2.Value=0;
	
	//找到第一个最大值点
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

	//将第一个最大值点附近清零
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

	//找到第二个最大值点
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

				// 指向缓存图像倒数第j行，第i个象素的指针			
				lpDst10 = (char *)lpNewDIBBits10 + lLineBytes * jjj + iii;	

				//在第一条直线上
				iDist = (int) (iii*cos(MaxValue1.AngleNumber*2*pi/180.0) + \
							jjj*sin(MaxValue1.AngleNumber*2*pi/180.0));
				if (iDist == MaxValue1.Dist)
					*lpDst10 = (unsigned char)0;
				
				//在第二条直线上
				iDist = (int) (iii*cos(MaxValue2.AngleNumber*2*pi/180.0) + \
							jjj*sin(MaxValue2.AngleNumber*2*pi/180.0));
				if (iDist == MaxValue2.Dist)
					*lpDst10 = (unsigned char)0;
				
			}
		}


	// 复制腐蚀后的图像
	memcpy(lpDIBBits2, lpNewDIBBits10, lWidth2 * lHeight2/2);

	// 释放内存
	LocalUnlock(hNewDIBBits10);
	LocalFree(hNewDIBBits10);

	// 释放内存
	LocalUnlock(hTransArea);
	LocalFree(hTransArea);
*/
//////////////////////////////////////////////////////////////////////////////////////////////
//解除锁定
::GlobalUnlock ((HGLOBAL)hDIB2);
//////////////////////////////////////////////////////////////////////////////////////////////

    nFile.Open("C:\\image.bmp",CFile::modeWrite | CFile::modeCreate);
	SaveDIB(hDIB2, nFile);

    nFile.Close();
	
    ShowPic("C:\\image.bmp",hwndAnalysis,640,480);
	
	capPreview(hwndVideo,TRUE); 
	CDialog::OnTimer(nIDEvent);
}

/*********************停止采集*****************************/
void CBiYeSheJiDlg::OnStopcap() 
{
	// TODO: Add your control notification handler code here
	
}
/***********************************************************/
/**************前行、左转、右转、倒车、停车*****************/

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
	//设置背景颜色
	CRect rect;
	GetClientRect(&rect); //计算对话框的尺寸
	dc.FillSolidRect(&rect,RGB(208,255,208)); //绘制对话框背景色
	
	//绘制模拟视图圆
/*	CClientDC m_dc(this);
	//填充圆形区
	CRgn rgn; 
	CRect rect1(10, 280, 200, 470);//圆心坐标（105，375）
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
