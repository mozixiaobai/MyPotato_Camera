#ifndef  _COMMON_H_
#define  _COMMON_H_

BYTE Get8bitBmpGray(BYTE *buf, DWORD bufSize);//��ȡ8λ�Ҷ�ͼ��ĻҶȾ�ֵ
int WriteHead(unsigned char* Output,unsigned char *Input,int nWidth,int nHeight);
BOOL LoadBmpFile (HWND hWnd,unsigned char *BMPBuf,int nWidth,int nHeight);
#endif