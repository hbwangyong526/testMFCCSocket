#pragma once
#include <string>
using namespace std;
//�����ļ��Կ�ִ���ļ���Ϊ׼


typedef struct _tInitPara
{
	string id;			//����ID��
	string rootPath;		//���ݿ�·��
	string path2add;	//���ݴ���
	string boardName;	//��������
	
	bool bConnectRemote; // ���ӵ�������
	string remoteIp;	//��������IP
	int remotePort;	//��������port
	int period;      // �г�����״̬ʵʱ�ϱ����� ��

	bool bConnectRemotePush; // ���ӵ�����������
	string remoteIpPush;	//������������IP
	int remotePortPush;	//�������������˿�

	string localIp;		//����IP
	string localInnerIp;	//�����ڲ�IP
	string pairIp;		//�Զ�IP����һ����ӵ�IP
	string locomotiveNumber;	//�������
	string pantographNumber;	//�ܵ繭���
	///��������ڷ�
	bool bThermometer;	//�¶ȼ��Ƿ����
	bool bGps;			//����ģ���Ƿ����
	string broadcastip;	//�㲥IP
	bool bUltraviolet;	//�����Ƿ����
	bool bPowerDev;		//��Դ�豸�Ƿ����
	bool bLights;		//������Ƿ����
	bool bInfraredCamera;	//��������Ƿ����
	bool b130HighFreqCamera;	//130���Ƶ����Ƿ����
	bool b200OverallViewCamera;	//200��ȫ������Ƿ����

	//���ӵ���������
	string highFreqCameraPara;	//��Ƶ����������ݴ����IP��ַ
	string infraCameraPara;		//��������������ݴ����IP��ַ
	string allviewCameraPara;	//ȫ�������������ʶ�����
	string serialPortPeripGps;	//����GPS IP ��ַ
	int serialPortPeripWendu;	//�¶����贮��

	int ultravioletLahuInternal;	//�������������ʱ��
	string url500Camera;	// 500���������������ַ
	string ipUltravilet;	//����IP��ַ
	int powerCommNo;		//��Դͨ�Ŵ�������
	///�澯
	int ultravioletAlarm;		//��������ʱ��
	int infraTemperature;	//������������¶ȸ澯
	int alarmLachuMin;	//��������
	int alarmLachuMax;	//��������
	int alarmDaogaoMin;	//��������
	int alarmDaogaoMax;	//��������
	//������ò���
    int  nCameHighTrig;
	int  nCamePanoTrig;
	int  nCameHighExpo;
	int  nCamePanoExpo;
	int  nCameHighGain;
	int  nCamePanoGain;
	int  nCameHighEdge;
    int  nCamePanoEdge;

	//������
	int serNoHighFreq;	//��Ƶ���ĸ���

	//�Ƿ��ͱ�������Ϣ
	int bUploadAlarm;	
	//�����ػ���ʱʱ��,��λ��
	int localShutDownTime;
	//��Դ�ػ���ʱʱ��,��λ��
	int powerShutDownTime;
}tInitPara,*ptInitPara;

class CInitPara : public Singletion<CInitPara>
{
	SINGLETON_INIT(CInitPara)
public:
	inline ptInitPara getPara() const
	{
		return m_pInitPara;
	}
public:
	static string getModleName();
	static string getModlePath();
	static bool isFileExists(string lpszFileName);
	static void getHardInfo(int &nFreeSpace, int& nTotalSpace);
	int writeOtherPara();
private:
	int init() override;
	int deInit() override;

	int initXml();	//��ʼ��XML
	int initOtherPara();	//��ʼ����������
	int initCrtDir();
	int creatMultidir(string &strPath);
private:
	ptInitPara m_pInitPara;
};