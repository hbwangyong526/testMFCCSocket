#pragma once
#include <string>
using namespace std;
//配制文件以可执行文件名为准


typedef struct _tInitPara
{
	string id;			//本机ID号
	string rootPath;		//数据库路径
	string path2add;	//扩容磁盘
	string boardName;	//主板名称
	
	bool bConnectRemote; // 连接地面中心
	string remoteIp;	//地面中心IP
	int remotePort;	//地面中心port
	int period;      // 列车运行状态实时上报周期 秒

	bool bConnectRemotePush; // 连接地面推流中心
	string remoteIpPush;	//地面中心推流IP
	int remotePortPush;	//地面中心推流端口

	string localIp;		//本机IP
	string localInnerIp;	//本机内部IP
	string pairIp;		//对端IP，另一块板子的IP
	string locomotiveNumber;	//机车编号
	string pantographNumber;	//受电弓编号
	///各外设存在否
	bool bThermometer;	//温度计是否存在
	bool bGps;			//导航模块是否存在
	string broadcastip;	//广播IP
	bool bUltraviolet;	//紫外是否存在
	bool bPowerDev;		//电源设备是否存在
	bool bLights;		//闪光灯是否存在
	bool bInfraredCamera;	//红外相机是否存在
	bool b130HighFreqCamera;	//130万高频相机是否存在
	bool b200OverallViewCamera;	//200万全景相机是否存在

	//附加的其他参数
	string highFreqCameraPara;	//高频相机参数，暂存相机IP地址
	string infraCameraPara;		//红外相机参数，暂存相机IP地址
	string allviewCameraPara;	//全景相机参数，标识相机名
	string serialPortPeripGps;	//外设GPS IP 地址
	int serialPortPeripWendu;	//温度外设串口

	int ultravioletLahuInternal;	//拉弧脉冲最大间隔时间
	string url500Camera;	// 500万摄像机子码流地址
	string ipUltravilet;	//紫外IP地址
	int powerCommNo;		//电源通信串口设置
	///告警
	int ultravioletAlarm;		//拉弧报警时间
	int infraTemperature;	//红外相机检测的温度告警
	int alarmLachuMin;	//拉出下限
	int alarmLachuMax;	//拉出上限
	int alarmDaogaoMin;	//导出下限
	int alarmDaogaoMax;	//导出上限
	//相机配置参数
    int  nCameHighTrig;
	int  nCamePanoTrig;
	int  nCameHighExpo;
	int  nCamePanoExpo;
	int  nCameHighGain;
	int  nCamePanoGain;
	int  nCameHighEdge;
    int  nCamePanoEdge;

	//测试用
	int serNoHighFreq;	//高频用哪个类

	//是否传送报警等信息
	int bUploadAlarm;	
	//本机关机超时时间,单位秒
	int localShutDownTime;
	//电源关机超时时间,单位分
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

	int initXml();	//初始化XML
	int initOtherPara();	//初始化其他参数
	int initCrtDir();
	int creatMultidir(string &strPath);
private:
	ptInitPara m_pInitPara;
};