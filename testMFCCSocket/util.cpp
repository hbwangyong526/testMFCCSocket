#include "stdafx.h"
#include "util.h"
#include <math.h>
#include <string>

using namespace std;

void unixtime2systime( unsigned long unixtime, SYSTEMTIME &systime )
{
	FILETIME ft;
	SYSTEMTIME pst;
	LONGLONG nLL = Int32x32To64(unixtime, 10000000) + 116444736000000000;
	ft.dwLowDateTime = (DWORD)nLL;
	ft.dwHighDateTime = (DWORD)(nLL >> 32);
	FileTimeToSystemTime(&ft, &pst);

	SYSTEMTIME localTime;
	memset(&localTime, 0, sizeof(SYSTEMTIME));
	TIME_ZONE_INFORMATION zinfo;
	GetTimeZoneInformation(&zinfo);
	SystemTimeToTzSpecificLocalTime(&zinfo,&pst, &localTime);

	systime = localTime;
}

time_t systime_to_timet(const SYSTEMTIME& st)
{
	struct tm gm = {st.wSecond, st.wMinute, st.wHour, st.wDay, st.wMonth-1, st.wYear-1900, st.wDayOfWeek, 0, 0};
	return mktime(&gm);
}

const char* newGUID()
{
	static char buf[64] = {0};
	GUID guid;
	if (S_OK == ::CoCreateGuid(&guid))
	{
		_snprintf_s(buf, sizeof(buf)
			, "%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X"
			, guid.Data1
			, guid.Data2
			, guid.Data3
			, guid.Data4[0], guid.Data4[1]
		, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]
		, guid.Data4[6], guid.Data4[7]
		);
	}
	return (const char*)buf;
}

time_t currentunixtime( void )
{
	SYSTEMTIME pst;
	SYSTEMTIME localTime;
	memset(&localTime, 0, sizeof(SYSTEMTIME));
	TIME_ZONE_INFORMATION zinfo;
	GetTimeZoneInformation(&zinfo);
	GetSystemTime(&pst);
	SystemTimeToTzSpecificLocalTime(&zinfo,&pst, &localTime);
	return systime_to_timet(localTime);
}

BOOL getFileVersion(LPCTSTR strFile, CString& strVersion, unsigned short *softver)   
{   
	TCHAR szVersionBuffer[8192] = _T("");   
	DWORD dwVerSize;   
	DWORD dwHandle = 0;   

	dwVerSize = GetFileVersionInfoSize(strFile, &dwHandle);   
	if (dwVerSize == 0)   
		return FALSE;   

	if (GetFileVersionInfo(strFile, 0, dwVerSize, szVersionBuffer))   
	{   
		VS_FIXEDFILEINFO * pInfo;   
		unsigned int nInfoLen;   

		if (VerQueryValue(szVersionBuffer, _T("\\"), (void**)&pInfo, &nInfoLen))  
		{  
			strVersion.Format(_T("%d.%d.%d.%d"),   
				HIWORD(pInfo->dwFileVersionMS), LOWORD(pInfo->dwFileVersionMS),   
				HIWORD(pInfo->dwFileVersionLS), LOWORD(pInfo->dwFileVersionLS));   
			if (softver)
			{
				softver[0] = HIWORD(pInfo->dwFileVersionMS);
				softver[1] = LOWORD(pInfo->dwFileVersionMS);
				softver[2] = HIWORD(pInfo->dwFileVersionLS);
				softver[3] = LOWORD(pInfo->dwFileVersionLS);
			}
			return TRUE;   
		}   
	}   

	return FALSE;   
} 

BOOL getSelfVersion( CString& str )
{
	 TCHAR szFullPath[MAX_PATH];
	 GetModuleFileName(NULL, szFullPath, sizeof(szFullPath));
	 return getFileVersion(szFullPath, str);
}

BOOL getSelfVersion( unsigned short *softver )
{
	TCHAR szFullPath[MAX_PATH];
	CString strver;
	GetModuleFileName(NULL, szFullPath, sizeof(szFullPath));
	return getFileVersion(szFullPath, strver, softver);
}

bool systemRun(const char* str)
{
	string cmd;
	cmd += "cmd /c ";
	cmd += str;
	WinExec(cmd.c_str(), SW_HIDE);
	return true;
}

CHighPrecisionTime::CHighPrecisionTime()
{
	LARGE_INTEGER f;
	QueryPerformanceFrequency(&f);
	m_dqFreq = (double)f.QuadPart;
	
}

CHighPrecisionTime::~CHighPrecisionTime()
{

}

LARGE_INTEGER CHighPrecisionTime::startTime()
{
	QueryPerformanceCounter(&m_timeStart);
	return m_timeStart;
}

double CHighPrecisionTime::getDValue()
{
	LARGE_INTEGER time_over;
	QueryPerformanceCounter(&time_over);
	double dd = ceil((time_over.QuadPart - m_timeStart.QuadPart)*1000/m_dqFreq);
	return dd;
}

double CHighPrecisionTime::getDValueRst()
{
	double dd = getDValue();
	startTime();
	return dd;
}
