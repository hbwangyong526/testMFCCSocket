#pragma once
#include <time.h>

void unixtime2systime(unsigned long unixtime, SYSTEMTIME &systime);
time_t systime_to_timet(const SYSTEMTIME& st);
time_t currentunixtime(void);
const char* newGUID();

class CHighPrecisionTime
{
public:
	CHighPrecisionTime();
	~CHighPrecisionTime();

	LARGE_INTEGER startTime();	//��ʼ��ʱ
	double getDValue();	//��ǰ��ʱ���ϴμ�ʱ��ֵ
	double getDValueRst();
private:
	double m_dqFreq;
	LARGE_INTEGER m_timeStart;
};

#pragma comment (lib, "Version.lib")   

BOOL getFileVersion(LPCTSTR strFile, CString& strVersion, unsigned short *softver=nullptr);  

BOOL getSelfVersion(CString& str);
//�õ�������汾�ţ��ĸ��ֽڵ�
BOOL getSelfVersion(unsigned short *softver);

bool systemRun(const char* str);