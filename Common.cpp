#include "StdAfx.h"
#include "Common.h"

BYTE Get8bitBmpGray(BYTE *buf, DWORD bufSize)//��ȡ8λ�Ҷ�ͼ��ĻҶȾ�ֵ
{
	DWORD sum = 0;
	for (int i = 0; i < bufSize; i++)
	{
		sum += buf[i];
	}
	float avg = 1.0 * sum / bufSize + 0.5;
	return (BYTE)avg;
}

int WriteHead(unsigned char* Output,unsigned char *Input,int nWidth,int nHeight)
{
	int IMAGE_X=nWidth,IMAGE_Y=nHeight;
	unsigned char head[1078]={
		/***************************/
		//file header
		0x42,0x4d,//file type 
			//0x36,0x6c,0x01,0x00, //file size***
			0x0,0x0,0x0,0x00, //file size***
			0x00,0x00, //reserved
			0x00,0x00,//reserved
			0x36,0x4,0x00,0x00,//head byte***
			/***************************/
			//infoheader
			0x28,0x00,0x00,0x00,//struct size
			
			//0x00,0x01,0x00,0x00,//map width*** 
			0x00,0x00,0x0,0x00,//map width*** 
			//0x68,0x01,0x00,0x00,//map height***
			0x00,0x00,0x00,0x00,//map height***
			
			0x01,0x00,//must be 1
			0x08,0x00,//color count***
			0x00,0x00,0x00,0x00, //compression
			//0x00,0x68,0x01,0x00,//data size***
			0x00,0x00,0x00,0x00,//data size***
			0x00,0x00,0x00,0x00, //dpix
			0x00,0x00,0x00,0x00, //dpiy
			0x00,0x00,0x00,0x00,//color used
			0x00,0x00,0x00,0x00,//color important
			
	};
	
	long num;
	num=IMAGE_X; head[18]= num & 0xFF;
	num=num>>8;  head[19]= num & 0xFF;
	num=num>>8;  head[20]= num & 0xFF;
	num=num>>8;  head[21]= num & 0xFF;
	
	
	num=IMAGE_Y; head[22]= num & 0xFF;
	num=num>>8;  head[23]= num & 0xFF;
	num=num>>8;  head[24]= num & 0xFF;
	num=num>>8;  head[25]= num & 0xFF;
	
	int i,j;
	
	j=0;
	for (i=54;i<1078;i=i+4)
	{
		head[i]=head[i+1]=head[i+2]=j; 
		head[i+3]=0;
		j++;
	} 
	
	memcpy(Output,head,sizeof(byte)*1078);
	for(  i=0;i<=IMAGE_Y-1; i++ )
	{
		memcpy(Output+1078*sizeof(char)+(i)*(IMAGE_X),Input+i*IMAGE_X,IMAGE_X*sizeof(char));
	}
	
	return 1;
}
 


BITMAPFILEHEADER  bf;

BITMAPINFOHEADER bi;
#define WIDTHBYTES(i)    ((i+31)/32*4)
BOOL LoadBmpFile (HWND hWnd,unsigned char *BMPBuf,int nWidth,int nHeight)

{   	
	HFILE hf=NULL; //�ļ����
	
	//ָ��BITMAPINFOHEADER�ṹ��ָ��	
	LPBITMAPINFOHEADER    lpImgData; 
	
	LOGPALETTE *pPal; //ָ���߼���ɫ��ṹ��ָ��	
	LPRGBQUAD lpRGB; //ָ��RGBQUAD�ṹ��ָ��	
	HPALETTE hPrevPalette; //���������豸��ԭ���ĵ�ɫ��	
	HDC hDc; //�豸���	
	HLOCAL hPal; //�洢��ɫ��ľֲ��ڴ���	
	DWORD LineBytes;  //ÿһ�е��ֽ���	
	DWORD ImgSize;   //ʵ�ʵ�ͼ������ռ�õ��ֽ���
	
	//ʵ���õ�����ɫ�� ������ɫ�������е���ɫ����
	DWORD NumColors; 
	
	DWORD i;
	void* hImgData;
	HPALETTE hPalette;
 	
	//��BITMAPFILEHEADER�ṹ���ļ��ж�������д��bf��	
	memcpy((LPSTR)&bf, BMPBuf, sizeof(BITMAPFILEHEADER)); 
	
	//��BITMAPINFOHEADER�ṹ���ļ��ж�������д��bi��
	memcpy((LPSTR)&bi, BMPBuf+sizeof(BITMAPFILEHEADER),
		sizeof(BITMAPINFOHEADER));	 	
	LineBytes=(DWORD)WIDTHBYTES(bi.biWidth*bi.biBitCount);
	
	//ImgSizeΪʵ�ʵ�ͼ������ռ�õ��ֽ���	
	ImgSize=(DWORD)LineBytes*bi.biHeight;
	
	//NumColorsΪʵ���õ�����ɫ�� ������ɫ�������е���ɫ����
	if(bi.biClrUsed!=0)//���bi.biClrUsed��Ϊ�㣬��Ϊʵ���õ�����ɫ��
	{			
		NumColors=(DWORD)bi.biClrUsed; 	
	}
	else //�����õ�����ɫ��Ϊ2biBitCount��		
	{
		switch(bi.biBitCount)
		{		
		case 1:			
			NumColors=2;			
			break;			
		case 4:			
			NumColors=16;			
			break;			
		case 8:			
			NumColors=256;			
			break;			
		case 24:			
			NumColors=0; //�������ɫͼ��û�õ���ɫ��			
			break;			
		default: //��������������ɫ������Ϊ����			
			MessageBox(hWnd,TEXT("Invalid color numbers!"),
				TEXT("Error Message"), MB_OK|MB_ICONEXCLAMATION);			
			_lclose(hf);			
			return FALSE; //�ر��ļ�������FALSE			
		}
	}
	
	if(bf.bfOffBits!=(DWORD)(NumColors*sizeof(RGBQUAD)
		+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)))
		
	{		
		//�������ƫ������ʵ��ƫ����������һ������ɫ������		
		MessageBox(hWnd,TEXT("Invalid color numbers!"),
			TEXT("Error Message"), MB_OK|MB_ICONEXCLAMATION);		
		return FALSE; //�ر��ļ�������FALSE		
	}
	
	bf.bfSize=sizeof(BITMAPFILEHEADER)
		+sizeof(BITMAPINFOHEADER)+		
		NumColors*sizeof(RGBQUAD)+ImgSize;
	
	//�����ڴ棬��СΪBITMAPINFOHEADER�ṹ���ȼӵ�ɫ��+ʵ��λͼ
	
	if((hImgData=GlobalAlloc(GHND,(DWORD)		
		(sizeof(BITMAPINFOHEADER)+		
		NumColors*sizeof(RGBQUAD)+		
		ImgSize)))==NULL)		
	{		
		//�����ڴ����		
		MessageBox(hWnd, TEXT("Error alloc memory!"),
			TEXT("ErrorMessage"), MB_OK|MB_ICONEXCLAMATION);		
		return FALSE; //�ر��ļ�������FALSE		
	}
	
	//ָ��lpImgDataָ����ڴ���	
	lpImgData=(LPBITMAPINFOHEADER)GlobalLock(hImgData); 
		
	//���ļ����ݶ���lpImgData	
	memcpy((char *)lpImgData,BMPBuf+sizeof(BITMAPFILEHEADER),
		(long)sizeof(BITMAPINFOHEADER)		
		+(long)NumColors*sizeof(RGBQUAD)+ImgSize); 
	
	if(NumColors!=0) //NumColors��Ϊ�㣬˵���õ��˵�ɫ��		
	{		
		//Ϊ�߼���ɫ�����ֲ��ڴ棬��СΪ�߼���ɫ��ṹ���ȼ�		
		//NumColors��PALETTENTRY		
		hPal=LocalAlloc(LHND,sizeof(LOGPALETTE)+			
			NumColors* sizeof(PALETTEENTRY));
		
		//ָ��pPalָ����ڴ���		
		pPal =(LOGPALETTE *)LocalLock(hPal);
		
		//��д�߼���ɫ��ṹ��ͷ		
		pPal->palNumEntries = (unsigned short)NumColors;	
		pPal->palVersion = 0x300;
		
		//lpRGBָ����ǵ�ɫ�忪ʼ��λ��		
		lpRGB = (LPRGBQUAD)((LPSTR)lpImgData +			
			(DWORD)sizeof(BITMAPINFOHEADER));
		
		//��дÿһ��
		
		for (i = 0; i < NumColors; i++)			
		{			
			pPal->palPalEntry[i].peRed=lpRGB->rgbRed;			
			pPal->palPalEntry[i].peGreen=lpRGB->rgbGreen;			
			pPal->palPalEntry[i].peBlue=lpRGB->rgbBlue;			
			pPal->palPalEntry[i].peFlags=(BYTE)0;			
			lpRGB++; //ָ���Ƶ���һ��			
		}
		
		//�����߼���ɫ�壬hPalette��һ��ȫ�ֱ���		
		hPalette=CreatePalette(pPal);
		
		//�ͷžֲ��ڴ�		
		LocalUnlock(hPal);		
		LocalFree(hPal);		
	}
	
	//����豸�����ľ��	
	hDc=GetDC(hWnd);
	
	if(hPalette) //����ղŲ������߼���ɫ��		
	{		
		//���µ��߼���ɫ��ѡ��DC�����ɵ��߼���ɫ����������//hPrevPalette		
		hPrevPalette=SelectPalette(hDc,hPalette,FALSE);		
		RealizePalette(hDc);		
	}
	
	//����λͼ���	
	HBITMAP hBitmap = CreateDIBitmap(hDc, 
		(LPBITMAPINFOHEADER)lpImgData, (LONG)CBM_INIT,		
		(LPSTR)lpImgData+sizeof(BITMAPINFOHEADER)
		+NumColors*sizeof(RGBQUAD),		
		(LPBITMAPINFO)lpImgData, DIB_RGB_COLORS);
	
	HDC hMemDC = CreateCompatibleDC(hDc);// �����ڴ�
	SelectObject(hMemDC, hBitmap);
	
	StretchBlt(hDc, 0, 0, nWidth, nHeight, hMemDC, 0, 0,
		nWidth,nHeight,SRCCOPY);//�Ŵ�����
	
	//��ԭ���ĵ�ɫ��(����еĻ�)ѡ���豸�����ľ��	
	if(hPalette && hPrevPalette)		
	{		
		SelectPalette(hDc,hPrevPalette,FALSE);		
		RealizePalette(hDc);		
	}

	DeleteDC(hMemDC);//�ͷ��ڴ��豸������	
	ReleaseDC(hWnd,hDc); //�ͷ��豸������		
	GlobalUnlock(hImgData); //�����ڴ���
	GlobalFree(hImgData);
	DeleteObject(hBitmap);
	return TRUE; //�ɹ�����	
}
