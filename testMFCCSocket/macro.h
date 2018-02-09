#pragma once

#define SOFT_VER "v00.01"

#define USE_INFRA_FLIR 0

#define PORT_LCD 8100	//���ؼ������LCD���ö˿�

#define en_success (int)(0)
#define en_fail (int)(~0)
#define en_err 1	//����
#define en_none 2	//û����Ϣ

#define SAFE_DEL(p) if(p){delete p; p = nullptr;}
#define SAFE_DELARRAY(p) if(p){delete []p; p = nullptr;}
#define SETVALUE(data, type, value) *(type*)data = value;
const int devid_main = 1234;	//��д���豸ID
//�����������ı��
typedef enum 
{
	enDevIdThermometer = 1,				//�¶ȼ�
	enDevIdGps = 2,						//����
	enDevIdUltraviolet = 3,				//����
	enDevIdPowerDev = 4,				//��Դ
	enDevIdLights = 5,					//�����
	enDevIdInfraredCamera = 6,			//�������
	enDevId130HighFreqCamera = 7,		//130���Ƶ���
	enDevId200OverallViewCamera = 8,		//200��ȫ�����
	enDevIdSoftVer = 9,	//����汾��
	enDevIdHDInfo = 10,	//Ӳ����Ϣ
	enDevPower_log = 11,	//������־

	//�ϲ��뿪��״̬
	enSwitch_zhukong1switch,	//����1����״̬
	enSwitch_zhukong1Comm,			//����1ͨ��״̬
	enSwitch_zhukong1powertimes,			//����1�ϵ����
	enSwitch_zhukong2switch,		//����2����״̬
	enSwitch_zhukong2Comm,			//����2ͨ��״̬
	enSwitch_zhukong2powertimes,	//����2�ϵ����
	enSwitch_buguangdeng,			//����ƿ���״̬
	enSwitch_huzhaoASwitch,	//����A����״̬
	enSwitch_huzhaoACishu,	//����A�ϵ����
	enSwitch_huzhaoBSwitch,	// ����B������״̬
	enSwitch_huzhaoBCishu,	//����B�ϵ����
	enSwitch_zhudianyuanCishu,	//�ϵ�Դ�ϵ����
	enSwitch_wenduState,	//�¶�״̬
	enSwitch_powerBoxTemperature,	//������¶�
	enSwitch_gongdianType,	//��������
	enSwitch_ziwai,		//�������
	enSwitch_newPowerPara,	//�µ�Դ��ز���
	enSwitch_newPowerLog,	//�µ�Դ��־
}enDevId;
// ¼�񱣴�·��
#define INFRARED_DIR "Infrared\\"
#define HIGHFREQ_DIR "HighFreq\\"
#define OVERALLVIEW_DIR "OverallView\\"


//�������ʵ�ö�ٱ���
typedef enum 
{
	enCodeRateBiaoqing_highFreq = 0,	//�����Ƶ
	enCodeRateBiaoqing_allview = 3,	//����ȫ��
	enCodeRateBiaoqing_infrared = 6,	//�������
}enCodeRate;

//��������
typedef enum 
{
	enAlarmType_daogao,	//����
	enAlarmType_lachu,	//����ֵ
	enAlarmType_wendu,	//�¶�
	enAlarmType_ziwai,	//����
	enAlarmType_six_onekilometer,  /// һ��������Խ�޻���
}enAlarmType;

#define DEFAULT_DATA_LEN 1400	//Ĭ�����ݳ���
#define MAX_DATA_LEN (1024)	//��󻺳�������
//#define MAX_DATA_H264_LEN (512*1024)	//���������H264
#define FRAME_PACK_SIZE 25	//����֡�Ļ������

template <int TMaxLen = DEFAULT_DATA_LEN>
class tDataLen
{
public:
	tDataLen():max_size_(TMaxLen)
	{
		//		data = nullptr;
		data = new unsigned char[max_size_];
		memset(data, 0, max_size_);
		len = 0;
	}
	tDataLen(const tDataLen& dta)
	{
		//����ļٶ����Ѿ������ڴ���
		this->max_size_ = dta.max_size_;
		this->len = dta.len;
		if (this->data)
		{
			delete[] data;
			data = NULL;
		}
		data = new unsigned char[max_size_];
		memcpy(this->data, dta.data, dta.len);
	}
	tDataLen(int max_size):max_size_(max_size)
	{
		data = new unsigned char[max_size_];
		memset(data, 0, max_size_);
		len =  0;
	};
	~tDataLen()
	{
		if (data)
		{
			delete[] data;
			data = nullptr;
		}
	}

	//��ֹһֱ�����ڴ棬����ֻ����ֱ�Ӹ�ֵ����
	tDataLen& operator = (const tDataLen& dta)
	{
		if (this->max_size_ < dta.len)
		{
			this->max_size_ = dta.max_size_;
			
			if (this->data)
			{
				delete[] data;
				data = NULL;
			}
			data = new unsigned char[max_size_];
		}
		this->len = dta.len;
		memcpy(this->data, dta.data, dta.len);
		return *this;
	}

	void rstMaxSize(int max_size)
	{
		if (data)
		{
			delete[] data;
			data = nullptr;
		}
		max_size_ = max_size;
		data = new unsigned char[max_size_];
		memset(data, 0, max_size_);
		len =  0;
	}
	unsigned char *data;
	int len;
	int max_size_;
};

//�������������ṹ��

typedef struct _txHighFreq	//��Ƶ
{
	int wireHeight;	//����
	int pullout;	//����ֵ
	int x1;         //���X����
	int y1;			//���Y����
	int x2;         //�ұ�X����
	int y2;			//�ұ�Y����
	int wirPix;     //�߽Ӵ���X
	float rimgHig;  //ͼ��ߵ�
	float rimgLow;  //ͼ��͵�
	float rsdg2Wid; //�ܵ繭��
}_txHighFreq,*ptHighFreq;

typedef struct _Maoduan
{
	int bIsMaoduan;	//�Ƿ�ê��
	int pullout2;	//�ڶ�������ֵ
	int nDistance;	//����ֵ
}_tMaoduan,*ptMaoduan;

typedef struct _tVideoParsedPara
{
	int type;		//������� �澯ģ��ʹ������ֶα��� �ļ�����
	int len;	//data �ĳ��� �澯ģ��ʹ������ֶα��� �ļ�ƫ��
	int width;	//ͼ����  �澯ģ��ʹ������ֶα��� �Ƿ�Ϊ�ؼ�֡
	int height;	//ͼ��߶�  
	int longitude;	//����
	int latitude;	//γ��
	int moons;	//���Ǹ���
	int speed;	//�ٶ�
	char powerFeedSection[32];	//�����
	char barNo[32];	//�˺�
	union _unPara
	{
		struct _tInfrared  //�������
		{
			/*int hotTemperature;	//�Ӵ����¶�ֵ,ͨ������
			int outerTemperature;	//�����¶�,ͨ������
			int innerTemperature;	//���ⲿ��ȡ�����ӵ��¶�*/
			int  hotTemperature;	    //�Ӵ����¶�ֵ,ͨ������
			int  outerTemperature;	//�����¶�,ͨ������    
			int    innerTemperature;	//���ⲿ��ȡ�����ӵ��¶�
			int    maxposx;             //�����λ��X
			int    maxposy;             //�����λ��Y
			int    minposx;             //�����λ��X
			int    minposy;             //�����λ��Y
			int    ldrix;               //���½�x
			int    ldriy;               //���½�y
			int    rurix;               //���Ͻ�x
			int    ruriy;               //���Ͻ�y

		}tInfrared;

		struct _txHighFreq	//��Ƶ
		{
			int wireHeight;	//����
			int pullout;	//����ֵ
			int x1;         //���X����
			int y1;			//���Y����
			int x2;         //�ұ�X����
			int y2;			//�ұ�Y����
			int wirPix_x;   //�߽Ӵ���X
			int wirPix_y;   //�߽Ӵ���Y 
			float rimgHig;  //ͼ��ߵ�
			float rimgLow;  //ͼ��͵�
			float rsdg2Wid; //�ܵ繭��
			bool bIsDaogao;  //�Ƿ��е���
			bool bIsLachu;   //�Ƿ�������
			bool bIsMaoduan; //�Ƿ���ê��
			int wirPix2_x;   //2�߽Ӵ���X 
			int wirPix2_y;   //2�߽Ӵ���Y 
			int wireDistance;//˫֧�Ӵ��߾���ֵ

			int SDGStatus;   //�ܵ繭����״̬  //0��ʾ�������У�1��ʾ��״̬��2��ʾ����״̬

		}tHighFreq;
		char resvered[64];	//����
	}unPara;
	bool bHandled;	//�Ƿ�������
	__int64 time;	//�ɼ���Ƭʱ��
	int analyseState;	//����״̬����Ϊ0�������ɹ�
	unsigned char data[1]; //������ͼ������JPEG
}tVideoParsedPara,*ptVideoParsedPara;