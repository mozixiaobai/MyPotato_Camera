extern HINSTANCE hModule2;

//1 �汾��Ϣ��ȡ
typedef int (__stdcall  *pFP_GetVersion)(unsigned char code[4]);
//2	��ʼ������
typedef int (__stdcall *pFP_Begin)(); 

//3	1öָ��ͼ��������ȡ
typedef int (__stdcall  *pFP_FeatureExtract)(unsigned char   cScannerType, //������� ָ�Ʋɼ������ʹ���
	unsigned char cFingerCode,	 // ָλ���롣���������
	unsigned char * pFingerImgBuf,//������� ָ��ͼ������ָ�� ͼ���ʽΪ256(width)*360(height) 8λ�Ҷ�ͼ�� 
	unsigned char * pFeatureData); //������� ָ��ͼ����������ָ��


//5	��2��ָ���������ݽ��бȶԣ��õ�ƥ�����ƶ�ֵ
typedef int (__stdcall  *pFP_FeatureMatch)(unsigned char * pFeatureData1,	//������� ָ����������1
	unsigned char * pFeatureData2,	//������� ָ����������2
	float * pfSimilarity);			//������� ƥ�����ƶ�ֵ0.00-1.00


//6	��ָ��ͼ���ָ���������бȶԣ��õ�ƥ�����ƶ�ֵ
typedef int (__stdcall  *pFP_ImageMatch)(unsigned char * pFingerImgBuf,	//������� ָ��ͼ������ָ�� ͼ���ʽΪ256(width)*360(height)
	unsigned char * pFeatureData,	//������� ָ����������
	float * pfSimilarity);			//������� ָ��ͼ����������ָ��

//7	��ָ��ͼ�����ݽ���ѹ��
typedef int (__stdcall  *pFP_Compress)(  unsigned char cScannerType,	//������� ָ�Ʋɼ������ʹ���
	unsigned char cEnrolResult,	
	unsigned char cFingerCode,		 // ָλ���롣���������
	unsigned  char * pFingerImgBuf,   //������� ָ��ͼ������ָ�� ͼ���ʽΪ256(width)*360(height)
	int nCompressRatio,				//������� ѹ������
	unsigned char * pCompressedImgBuf,//������� ָ��ͼ��ѹ������ָ�� �ռ�Ϊ20K�ֽ�
	unsigned char strBuf[256]);		//������� ����-4ʱ�Ĵ�����Ϣ

//8	��ָ��ͼ��ѹ�����ݽ��и���
typedef int (__stdcall  *pFP_Decompress)(unsigned char * pCompressedImgBuf,//������� ָ��ͼ��ѹ������ָ�� �ѷ����20K�ֽڿռ�
	unsigned char * pFingerImgBuf,	//������� ָ��ͼ������ָ�� ��С256*360 �ֽ�
	unsigned char strBuf[256]);		//������� ����-4ʱ�Ĵ�����Ϣ

//9	��ȡָ��ͼ�������ֵ
typedef int (__stdcall  *pFP_GetQualityScore)(unsigned char * pFingerImgBuf,//������� ָ��ͼ������ָ�� ͼ���ʽΪ256(width)*360(height)
	unsigned char  * pnScore);//������� ͼ������ֵ 00H - 64H


//10 ����"δע��"ָ����������
typedef int (__stdcall  *pFP_GenFeatureFromEmpty1)(
	unsigned char   cScannerType,  //������� ָ�Ʋɼ������ʹ���
	unsigned char	cFingerCode,	 // ָλ���롣���������
	unsigned char * pFeatureData  //������� ���ɵ����߷���512�ֽڿռ�
	);

//10 ����"δע��"ָ����������
typedef int (__stdcall  *pFP_GenFeatureFromEmpty2)(unsigned char cFingerCode, unsigned char * pFeatureData);//������� ���ɵ����߷���512�ֽڿռ�

//11 ����"δע��"ָ��ͼ��ѹ������
//typedef int (* pFP_GenCompressDataFromEmpty)(unsigned char * pCompressedImgBuf);//������� ���ɵ����߷���20K�ֽڿռ�
//

//12 ��������
typedef int (__stdcall  *pFP_End)();

extern pFP_GetVersion FP_GetVersion; 
extern pFP_Begin FP_Begin;
extern pFP_FeatureExtract FP_FeatureExtract;
extern pFP_FeatureMatch FP_FeatureMatch;
extern pFP_ImageMatch FP_ImageMatch;
extern pFP_Compress FP_Compress;
extern pFP_Decompress FP_Decompress;
extern pFP_GetQualityScore FP_GetQualityScore;
extern pFP_GenFeatureFromEmpty1 FP_GenFeatureFromEmpty1;
extern pFP_GenFeatureFromEmpty2 FP_GenFeatureFromEmpty2;
extern pFP_End FP_End;
extern BOOL LoadDll();
extern void FreeDll();