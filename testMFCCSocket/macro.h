#pragma once

#define SOFT_VER "v00.01"

#define USE_INFRA_FLIR 0

#define PORT_LCD 8100	//本地监听针对LCD所用端口

#define en_success (int)(0)
#define en_fail (int)(~0)
#define en_err 1	//错误
#define en_none 2	//没有消息

#define SAFE_DEL(p) if(p){delete p; p = nullptr;}
#define SAFE_DELARRAY(p) if(p){delete []p; p = nullptr;}
#define SETVALUE(data, type, value) *(type*)data = value;
const int devid_main = 1234;	//填写的设备ID
//定义各个外设的编号
typedef enum 
{
	enDevIdThermometer = 1,				//温度计
	enDevIdGps = 2,						//导航
	enDevIdUltraviolet = 3,				//紫外
	enDevIdPowerDev = 4,				//电源
	enDevIdLights = 5,					//闪光灯
	enDevIdInfraredCamera = 6,			//红外相机
	enDevId130HighFreqCamera = 7,		//130万高频相机
	enDevId200OverallViewCamera = 8,		//200万全景相机
	enDevIdSoftVer = 9,	//软件版本号
	enDevIdHDInfo = 10,	//硬盘信息
	enDevPower_log = 11,	//请求日志

	//合并入开关状态
	enSwitch_zhukong1switch,	//主控1开关状态
	enSwitch_zhukong1Comm,			//主控1通信状态
	enSwitch_zhukong1powertimes,			//主控1上电次数
	enSwitch_zhukong2switch,		//主控2开关状态
	enSwitch_zhukong2Comm,			//主控2通信状态
	enSwitch_zhukong2powertimes,	//主控2上电次数
	enSwitch_buguangdeng,			//补光灯开关状态
	enSwitch_huzhaoASwitch,	//护罩A开关状态
	enSwitch_huzhaoACishu,	//护罩A上电次数
	enSwitch_huzhaoBSwitch,	// 护罩B开开关状态
	enSwitch_huzhaoBCishu,	//护罩B上电次数
	enSwitch_zhudianyuanCishu,	//上电源上电次数
	enSwitch_wenduState,	//温度状态
	enSwitch_powerBoxTemperature,	//配电箱温度
	enSwitch_gongdianType,	//供电类型
	enSwitch_ziwai,		//紫外参数
	enSwitch_newPowerPara,	//新电源监控参数
	enSwitch_newPowerLog,	//新电源日志
}enDevId;
// 录像保存路径
#define INFRARED_DIR "Infrared\\"
#define HIGHFREQ_DIR "HighFreq\\"
#define OVERALLVIEW_DIR "OverallView\\"


//各个码率的枚举变量
typedef enum 
{
	enCodeRateBiaoqing_highFreq = 0,	//标清高频
	enCodeRateBiaoqing_allview = 3,	//标清全景
	enCodeRateBiaoqing_infrared = 6,	//标清红外
}enCodeRate;

//报警类型
typedef enum 
{
	enAlarmType_daogao,	//导高
	enAlarmType_lachu,	//拉出值
	enAlarmType_wendu,	//温度
	enAlarmType_ziwai,	//紫外
	enAlarmType_six_onekilometer,  /// 一公里六次越限弧段
}enAlarmType;

#define DEFAULT_DATA_LEN 1400	//默认数据长度
#define MAX_DATA_LEN (1024)	//最大缓冲区长度
//#define MAX_DATA_H264_LEN (512*1024)	//最大编码完成H264
#define FRAME_PACK_SIZE 25	//保存帧的缓冲个数

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
		//这里的假定都已经分配内存了
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

	//防止一直申请内存，这里只进行直接赋值操作
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

//定义相机分析完结构体

typedef struct _txHighFreq	//高频
{
	int wireHeight;	//导高
	int pullout;	//拉出值
	int x1;         //左边X座标
	int y1;			//左边Y座标
	int x2;         //右边X座标
	int y2;			//右边Y座标
	int wirPix;     //线接触点X
	float rimgHig;  //图像高点
	float rimgLow;  //图像低点
	float rsdg2Wid; //受电弓宽
}_txHighFreq,*ptHighFreq;

typedef struct _Maoduan
{
	int bIsMaoduan;	//是否锚断
	int pullout2;	//第二个拉出值
	int nDistance;	//距离值
}_tMaoduan,*ptMaoduan;

typedef struct _tVideoParsedPara
{
	int type;		//相机类型 告警模块使用这个字段保存 文件索引
	int len;	//data 的长度 告警模块使用这个字段保存 文件偏移
	int width;	//图像宽度  告警模块使用这个字段保存 是否为关键帧
	int height;	//图像高度  
	int longitude;	//经度
	int latitude;	//纬度
	int moons;	//卫星个数
	int speed;	//速度
	char powerFeedSection[32];	//供电段
	char barNo[32];	//杆号
	union _unPara
	{
		struct _tInfrared  //红外相机
		{
			/*int hotTemperature;	//接触点温度值,通过分析
			int outerTemperature;	//环境温度,通过分析
			int innerTemperature;	//从外部获取，盒子的温度*/
			int  hotTemperature;	    //接触点温度值,通过分析
			int  outerTemperature;	//环境温度,通过分析    
			int    innerTemperature;	//从外部获取，盒子的温度
			int    maxposx;             //最高温位置X
			int    maxposy;             //最高温位置Y
			int    minposx;             //最低温位置X
			int    minposy;             //最低温位置Y
			int    ldrix;               //左下角x
			int    ldriy;               //左下角y
			int    rurix;               //右上角x
			int    ruriy;               //右上角y

		}tInfrared;

		struct _txHighFreq	//高频
		{
			int wireHeight;	//导高
			int pullout;	//拉出值
			int x1;         //左边X座标
			int y1;			//左边Y座标
			int x2;         //右边X座标
			int y2;			//右边Y座标
			int wirPix_x;   //线接触点X
			int wirPix_y;   //线接触点Y 
			float rimgHig;  //图像高点
			float rimgLow;  //图像低点
			float rsdg2Wid; //受电弓宽
			bool bIsDaogao;  //是否有导高
			bool bIsLachu;   //是否有拉出
			bool bIsMaoduan; //是否有锚断
			int wirPix2_x;   //2线接触点X 
			int wirPix2_y;   //2线接触点Y 
			int wireDistance;//双支接触线距离值

			int SDGStatus;   //受电弓运行状态  //0表示正常运行，1表示打弓状态，2表示降弓状态

		}tHighFreq;
		char resvered[64];	//保留
	}unPara;
	bool bHandled;	//是否分析完毕
	__int64 time;	//采集照片时间
	int analyseState;	//分析状态，置为0，分析成功
	unsigned char data[1]; //分析的图像数据JPEG
}tVideoParsedPara,*ptVideoParsedPara;