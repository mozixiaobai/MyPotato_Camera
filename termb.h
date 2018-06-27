extern HINSTANCE hModule;

//����֤;
typedef int (* pAuthenticate)();
typedef int (* pAuthenticateExt)();

//�رմ���
typedef int (* pCloseComm)(); 

//��ȡ�豸���
typedef int (* pGetDeviceID)(char * pMsg);		

//��ȡbmp��Ƭ
typedef int (* pGetPhoto)(char * Wlt_File);

//��ȡSAM���
typedef char* (*pGetSAMID)();

// ��ʼ������;
typedef  int (*pInitComm)(int port);

// ��ʼ������(��չ);
typedef int  (*pInitCommExt)();

//��ȡ���̺Ͳ�Ʒ��Ϣ
typedef void (*pMfrInfo)(char * cDeviceType,char * cDeviceCategory,char * cDeviceName,char * cMfr);

//��������,��Ϣ�ļ��洢��Ӧ�ó���ǰĿ¼��;
typedef int  (*pRead_Content)( int active);

//	��������,��Ϣ�ļ��洢��ָ��Ŀ¼�¡�
typedef int  (*pRead_Content_Path)(char* cPath, int active);

extern pAuthenticate Authenticate; 
extern pAuthenticateExt  AuthenticateExt;
extern pCloseComm CloseComm;
extern pGetDeviceID  GetDeviceID;
extern pGetPhoto GetPhoto;
extern pGetSAMID  GetSAMID;
extern pInitComm InitComm;
extern pInitCommExt InitCommExt;
extern pMfrInfo MfrInfo;
extern pRead_Content Read_Content;
extern pRead_Content_Path Read_Content_Path;
extern BOOL LoadTermbDll();
extern void FreeTermbDll();