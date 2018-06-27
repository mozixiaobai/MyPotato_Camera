
#ifdef _UDS_VIDEOCORE_DLL
#define UDSDLL_INTERFACE extern "C" _declspec(dllexport)
#else
#define UDSDLL_INTERFACE extern "C" _declspec(dllimport)
#endif

#define UDSVIDEOCORE_SUCCEED			0		//�ɹ�
#define UDSVIDEOCORE_ERR_NODEVICE		-1000	//���豸
#define UDSVIDEOCORE_ERR_NODEVSELECTED	-1001	//��δѡ���豸
#define UDSVIDEOCORE_ERR_DEVNOTRUN		-1002	//�豸��δ��ʼ����
#define UDSVIDEOCORE_ERR_INVALIDHWND	-1003	//�Ǵ��ھ��
#define UDSVIDEOCORE_ERR_GETCWND		-1004	//��ȡCWNDʧ��
#define UDSVIDEOCORE_
#define UDSVIDEOCORE_
#define UDSVIDEOCORE_
#define UDSVIDEOCORE_

#define UDSVIDEOCORE_ERR_INVALIDIDX	-5		//�Ƿ�����

UDSDLL_INTERFACE LONG InitialLib(LONG showHwnd);

UDSDLL_INTERFACE LONG UninitialLib();

UDSDLL_INTERFACE LONG GetDevCount();

UDSDLL_INTERFACE BSTR GetDevName(int index);

UDSDLL_INTERFACE LONG SelectDevice(int index);

UDSDLL_INTERFACE LONG GetResoCount();

UDSDLL_INTERFACE LONG GetResobyIndex(int index, int& width, int& height);

UDSDLL_INTERFACE BSTR GetResobyIndexEx(int index);

UDSDLL_INTERFACE LONG SetResolution(int index);

UDSDLL_INTERFACE LONG SetResolutionEx(int width, int height);

UDSDLL_INTERFACE LONG StartRun();

UDSDLL_INTERFACE LONG StartRunEx(int width, int height);

UDSDLL_INTERFACE LONG StopRun();

UDSDLL_INTERFACE LONG GetCurResoIndex();

UDSDLL_INTERFACE LONG GetCurReso(int& width, int& height);

UDSDLL_INTERFACE BSTR GetCurResoEx();

UDSDLL_INTERFACE LONG SetColorMode(int index);

UDSDLL_INTERFACE LONG CaptureImage(BSTR fileName);

UDSDLL_INTERFACE LONG CapturePDF(BSTR pdfName);

UDSDLL_INTERFACE BSTR CaptureBase64();

UDSDLL_INTERFACE LONG CaptureBarcode(BSTR folderPath, LONG fileType);

UDSDLL_INTERFACE LONG RotatedVideo(LONG type);

UDSDLL_INTERFACE LONG AdjuestImageCrop(BOOL bCrop);

UDSDLL_INTERFACE LONG ManualImageCrop(BOOL bCrop);

UDSDLL_INTERFACE LONG ManualBeginPoint(int x, int y);

UDSDLL_INTERFACE LONG ManualEndPoint(int x, int y);

UDSDLL_INTERFACE LONG ShowVideoInfo(BOOL bShow);

UDSDLL_INTERFACE LONG HTTPUpload(BSTR url, BSTR fileName, BOOL bDel);