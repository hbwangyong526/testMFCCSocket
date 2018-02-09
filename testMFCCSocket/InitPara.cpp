#include "stdafx.h"
#include "InitPara.h"
#include "macro.h"
#include "util.h"
#include "tinyxml/tinyxml.h"

#define INIT_PARA_FILENAME "initpara.xml"


int CInitPara::init()
{
	int ret = en_success;
	m_pInitPara = new tInitPara;
	assert(m_pInitPara);

	initXml();
	initCrtDir();
	return ret;
}

int CInitPara::deInit()
{
	int ret = en_success;
	SAFE_DEL(m_pInitPara);
	return ret;
}

string CInitPara::getModleName()
{
	TCHAR strCurPath[MAX_PATH];
	TCHAR *pt;
	GetModuleFileName(NULL, strCurPath, MAX_PATH);
	int len = _tcslen(strCurPath);
	pt = strCurPath + len;
	while (--pt)
	{
		if (*pt == _T('\\'))
		{
			pt++;
			break;
		}
	}
	USES_CONVERSION;
	return string( W2A(pt) );
}

string CInitPara::getModlePath()
{
	TCHAR strCurPath[MAX_PATH];
	GetModuleFileName(NULL, strCurPath, MAX_PATH);
	TCHAR *ch = _tcsrchr(strCurPath, _T('\\'));
	ch[0] = 0;
	USES_CONVERSION;
	return string( W2A(strCurPath) );
}

int CInitPara::initXml()
{
	int err = en_success;
	int ret = en_fail;
	string strFileName;
	string strSrcFileName;
	strSrcFileName = strFileName = CInitPara::getModlePath();
	strFileName += "\\";
	strFileName += INIT_PARA_FILENAME;
	//1.判断XML文件是否存在，若不存在直接按规则创建
	if (false == isFileExists(strFileName))
	{
		strSrcFileName += "\\";
		strSrcFileName += "initpara.xj";
		CopyFileA(strSrcFileName.c_str(), INIT_PARA_FILENAME, FALSE);
	}
	//读取各配制参数
	string pValue;
	TiXmlDocument *pDoc = new TiXmlDocument();
	string sFileName(strFileName);
	ret = pDoc->LoadFile(sFileName.c_str());
	if (ret)
	{
		string strNodeName;
		TiXmlElement *rootElem = pDoc->RootElement();
		TiXmlElement* pNode = nullptr;
		for (pNode = rootElem->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
		{
			strNodeName = pNode->Value();
			if (strNodeName == "board")
			{
				pValue = pNode->Attribute("name");
				m_pInitPara->boardName = pValue;

				m_pInitPara->id = pNode->FirstChildElement()->FirstChild()->Value();
			}
			else if ("locomotive" == strNodeName)
			{
				m_pInitPara->locomotiveNumber = pNode->FirstChildElement()->FirstChild()->Value();
			}
			else if ("pantograph" == strNodeName)
			{
				m_pInitPara->pantographNumber = pNode->FirstChildElement()->FirstChild()->Value();
			}
			else if ("remote" == strNodeName)
			{
				int value = 0;
				pNode->QueryIntAttribute("connect",&value);
				m_pInitPara->bConnectRemote = value;
				TiXmlElement *pNode2;
				for (pNode2 = pNode->FirstChildElement(); pNode2; pNode2 = pNode2->NextSiblingElement())
				{
					strNodeName = pNode2->Value();
					if ("ip" == strNodeName)
					{
						m_pInitPara->remoteIp = pNode2->FirstChild()->Value();
					}
					else if ("port" == strNodeName)
					{
						m_pInitPara->remotePort = atoi(pNode2->FirstChild()->Value());
					}
					else if ("period" == strNodeName)
					{
						m_pInitPara->period = atoi(pNode2->FirstChild()->Value());
					}
				}
			}
			else if ("remotepush" == strNodeName)
			{
				int value = 0;
				pNode->QueryIntAttribute("connect",&value);
				m_pInitPara->bConnectRemotePush = value;
				TiXmlElement *pNode2;
				for (pNode2 = pNode->FirstChildElement(); pNode2; pNode2 = pNode2->NextSiblingElement())
				{
					strNodeName = pNode2->Value();
					if ("ip" == strNodeName)
					{
						m_pInitPara->remoteIpPush = pNode2->FirstChild()->Value();
					}
					else if ("port" == strNodeName)
					{
						m_pInitPara->remotePortPush = atoi(pNode2->FirstChild()->Value());
					}
				}
			}
			else if ("local" == strNodeName)
			{
				TiXmlElement *pNode2;
				for (pNode2 = pNode->FirstChildElement(); pNode2; pNode2 = pNode2->NextSiblingElement())
				{
					strNodeName = pNode2->Value();
					if ("outip" == strNodeName)
					{
						m_pInitPara->localIp = pNode2->FirstChild()->Value();
					}
					else if ("innerip" == strNodeName)
					{
						m_pInitPara->localInnerIp = pNode2->FirstChild()->Value();
					}
					else if ("pairip" == strNodeName)
					{
						m_pInitPara->pairIp = pNode2->FirstChild()->Value();
					}
					else if ("highFreqCameraPara" == strNodeName)
					{
						m_pInitPara->highFreqCameraPara = pNode2->FirstChild()->Value();
					}
					else if ("infraCameraPara" == strNodeName)
					{
						m_pInitPara->infraCameraPara = pNode2->FirstChild()->Value();
					}
					else if ("allviewCameraPara" == strNodeName)
					{
						m_pInitPara->allviewCameraPara = pNode2->FirstChild()->Value();
					}
					else if ("serialPortPeripGps" == strNodeName)
					{
						m_pInitPara->serialPortPeripGps = pNode2->FirstChild()->Value();
					}
					else if ("serialPortPeripWendu" == strNodeName)
					{
						m_pInitPara->serialPortPeripWendu = atoi(pNode2->FirstChild()->Value());
					}
					else if ("ultravioletLahuInternal" == strNodeName)
					{
						m_pInitPara->ultravioletLahuInternal = atoi(pNode2->FirstChild()->Value());
					}
					
					else if ("url500Camera" == strNodeName)
					{
						m_pInitPara->url500Camera = pNode2->FirstChild()->Value();
					}
					else if ("powerCommNo" == strNodeName)
					{
						m_pInitPara->powerCommNo = atoi(pNode2->FirstChild()->Value());
					}
					else if ("serNoHighFreq" == strNodeName)
					{
						m_pInitPara->serNoHighFreq = atoi(pNode2->FirstChild()->Value());
					}
					else if ("bUploadAlarm" == strNodeName)
					{
						m_pInitPara->bUploadAlarm = atoi(pNode2->FirstChild()->Value());
					}
					else if ("localShutDownTime" == strNodeName)
					{
						m_pInitPara->localShutDownTime = atoi(pNode2->FirstChild()->Value());
					}
					else if ("powerShutDownTime" == strNodeName)
					{
						m_pInitPara->powerShutDownTime = atoi(pNode2->FirstChild()->Value());
					}
				}
			}
			else if ("CameraSet" == strNodeName)
			{
				TiXmlElement *pNode2;
				for (pNode2 = pNode->FirstChildElement(); pNode2; pNode2 = pNode2->NextSiblingElement())
				{
					strNodeName = pNode2->Value();
					if ("CameHighTrig" == strNodeName)
					{
						m_pInitPara->nCameHighTrig = atoi(pNode2->FirstChild()->Value());
					}
					else if ("CamePanoTrig" == strNodeName)
					{
						m_pInitPara->nCamePanoTrig = atoi(pNode2->FirstChild()->Value());
					}
					else if ("CameHighExpo" == strNodeName)
					{
						m_pInitPara->nCameHighExpo = atoi(pNode2->FirstChild()->Value());
					}
					else if ("CamePanoExpo" == strNodeName)
					{
						m_pInitPara->nCamePanoExpo = atoi(pNode2->FirstChild()->Value());
					}
					else if ("CameHighGain" == strNodeName)
					{
						m_pInitPara->nCameHighGain = atoi(pNode2->FirstChild()->Value());
					}
					else if ("CamePanoGain" == strNodeName)
					{
						m_pInitPara->nCamePanoGain = atoi(pNode2->FirstChild()->Value());
					}
					else if ("CameHighEdge" == strNodeName)
					{
						m_pInitPara->nCameHighEdge = atoi(pNode2->FirstChild()->Value());
					}
					else if ("CamePanoEdge" == strNodeName)
					{
						m_pInitPara->nCamePanoEdge = atoi(pNode2->FirstChild()->Value());
					}
				}
			}
			else if ("alarm" == strNodeName)
			{
				TiXmlElement *pNode2;
				for (pNode2 = pNode->FirstChildElement(); pNode2; pNode2 = pNode2->NextSiblingElement())
				{
					strNodeName = pNode2->Value();
					if ("ultravioletAlarm" == strNodeName)
					{
						m_pInitPara->ultravioletAlarm = atoi(pNode2->FirstChild()->Value());
					}
					else if ("infraTemperature" == strNodeName)
					{
						m_pInitPara->infraTemperature = atoi(pNode2->FirstChild()->Value());
					}
					else if ("daogao" == strNodeName)
					{
						for (TiXmlElement *pNode3 = pNode2->FirstChildElement(); pNode3; pNode3 = pNode3->NextSiblingElement())
						{
							strNodeName = pNode3->Value();
							if ("max" == strNodeName)
							{
								m_pInitPara->alarmDaogaoMax = atoi(pNode3->FirstChild()->Value());
							}
							else if ("min" == strNodeName)
							{
								m_pInitPara->alarmDaogaoMin = atoi(pNode3->FirstChild()->Value());
							}
						}
					}
					else if ("lachu" == strNodeName)
					{
						for (TiXmlElement *pNode3 = pNode2->FirstChildElement(); pNode3; pNode3 = pNode3->NextSiblingElement())
						{
							strNodeName = pNode3->Value();
							if ("max" == strNodeName)
							{
								m_pInitPara->alarmLachuMax = atoi(pNode3->FirstChild()->Value());
							}
							else if ("min" == strNodeName)
							{
								m_pInitPara->alarmLachuMin = atoi(pNode3->FirstChild()->Value());
							}
						}
					}
				}
			}
			else if ("dbpath" == strNodeName)
			{
				m_pInitPara->rootPath = pNode->FirstChild()->Value();
			}
			else if ("path2add" == strNodeName)
			{
				m_pInitPara->path2add = pNode->FirstChild()->Value();
			}
			else if ("sensors" == strNodeName)
			{
				TiXmlElement *pNode2;
				for (pNode2 = pNode->FirstChildElement(); pNode2; pNode2 = pNode2->NextSiblingElement())
				{
					int value = 0;
					ret = pNode2->QueryIntAttribute("id",&value);
					if (TIXML_SUCCESS == ret)
					{
						int value2 = 0;
						ret = pNode2->QueryIntAttribute("exist",&value2);
						if (TIXML_SUCCESS == ret)
						{
							switch (value)
							{
							case 1:
								m_pInitPara->bThermometer = value2;
								break;
							case 2:
								m_pInitPara->bGps = value2;
								{
									TiXmlElement *pNode3;
									for (pNode3 = pNode2->FirstChildElement(); pNode3; pNode3 = pNode3->NextSiblingElement())
									{
										strNodeName = pNode3->Value();
										if ("broadcastip" == strNodeName)
										{
											m_pInitPara->broadcastip = pNode3->FirstChild()->Value();
										}
									}
								}
								break;
							case 3:
								m_pInitPara->bUltraviolet = value2;
								{
									TiXmlElement *pNode3;
									for (pNode3 = pNode2->FirstChildElement(); pNode3; pNode3 = pNode3->NextSiblingElement())
									{
										strNodeName = pNode3->Value();
										if ("ip" == strNodeName)
										{
											m_pInitPara->ipUltravilet = pNode3->FirstChild()->Value();
										}
									}
								}
								break;
							case 4:
								m_pInitPara->bPowerDev = value2;
								break;
							case 5:
								m_pInitPara->bLights = value2;
								break;
							case 6:
								m_pInitPara->bInfraredCamera = value2;
								//urlFun(pNode2, m_pInitPara->infraredCamera_biaoqing, m_pInitPara->infraredCamera_gaoqing, m_pInitPara->infraredCamera_chaoqing);
								break;
							case 7:
								m_pInitPara->b130HighFreqCamera = value2;
								//urlFun(pNode2, m_pInitPara->highFreqCamera_biaoqing, m_pInitPara->highFreqCamera_gaoqing, m_pInitPara->highFreqCamera_chaoqing);
								break;
							case 8:
								m_pInitPara->b200OverallViewCamera = value2;
								//urlFun(pNode2, m_pInitPara->overallViewCamera_biaoqing, m_pInitPara->overallViewCamera_gaoqing, m_pInitPara->overallViewCamera_chaoqing);
								break;
							default:
								break;
							}
						}
					}
				}
			}
		}
	}
	return err;
}

bool CInitPara::isFileExists( string lpszFileName )
{
	return _access_s(lpszFileName.c_str(), 0) == 0;
}

void CInitPara::getHardInfo( int &nFreeSpace, int& nTotalSpace )
{
	DWORD dwSectorsPerCluster=0;//每簇中扇区数
	DWORD dwBytesPerSector=0;//每扇区中字节数
	DWORD dwFreeClusters=0;//剩余簇数
	DWORD dwTotalClusters=0;//总簇数
	
	nTotalSpace = 0;
	nFreeSpace = 0;

	if (GetDiskFreeSpace(_T("d:\\"),&dwSectorsPerCluster,&dwBytesPerSector,
		&dwFreeClusters,&dwTotalClusters))
	{
		//m_dwVolSize=dwTotalClusters*dwSectorsPerCluster*dwBytesPerSector;//不能这样，否则越界
		double dd=dwSectorsPerCluster*dwBytesPerSector/(1024.*1024.);//转换为 M
//		dd=dd/1024.;//转换为 G
		nTotalSpace += dwTotalClusters*dd;//该磁盘总大小
		nFreeSpace  += dwFreeClusters*dd;
	}

	if (GetDiskFreeSpace(_T("e:\\"),&dwSectorsPerCluster,&dwBytesPerSector,
		&dwFreeClusters,&dwTotalClusters))
	{
		//m_dwVolSize=dwTotalClusters*dwSectorsPerCluster*dwBytesPerSector;//不能这样，否则越界
		double dd=dwSectorsPerCluster*dwBytesPerSector/(1024.*1024.);//转换为 M
		//		dd=dd/1024.;//转换为 G
		nTotalSpace += dwTotalClusters*dd;//该磁盘总大小
		nFreeSpace  += dwFreeClusters*dd;
	}
}

int CInitPara::initOtherPara()
{
	int nRet = 0;
	m_pInitPara->bUploadAlarm = 1;
	return nRet;
}

int CInitPara::writeOtherPara()
{
	int err = en_success;
	int ret = en_fail;
	string strFileName;
	string strSrcFileName;
	strSrcFileName = strFileName = CInitPara::getModlePath();
	strFileName += "\\";
	strFileName += INIT_PARA_FILENAME;
	//1.判断XML文件是否存在，若不存在直接按规则创建
	if (false == isFileExists(strFileName))
	{
		strSrcFileName += "\\";
		strSrcFileName += "initpara.xj";
		CopyFileA(strSrcFileName.c_str(), INIT_PARA_FILENAME, FALSE);
	}
	//读取各配制参数
	string pValue;
	TiXmlDocument *pDoc = new TiXmlDocument();
	string sFileName(strFileName);
	ret = pDoc->LoadFile(sFileName.c_str());
	if (ret)
	{
		string strNodeName;
		TiXmlElement *rootElem = pDoc->RootElement();
		TiXmlElement* pNode = nullptr;
		for (pNode = rootElem->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement())
		{
			strNodeName = pNode->Value();
			
			if ("local" == strNodeName)
			{
				TiXmlElement *pNode2;
				for (pNode2 = pNode->FirstChildElement(); pNode2; pNode2 = pNode2->NextSiblingElement())
				{
					strNodeName = pNode2->Value();
					
					if ("bUploadAlarm" == strNodeName)
					{
						TiXmlNode* pNodeChild = pNode2->FirstChild();
						char str[32] = {};
						_itoa_s(m_pInitPara->bUploadAlarm, str, 10);
						pNodeChild->SetValue(str);
					}
				}
			}
		}
	}
	pDoc->SaveFile();
	return err;
}

int CInitPara::initCrtDir()
{
	int err = en_success;
	string strBase = getPara()->rootPath;
	err = creatMultidir(string(strBase + "\\x3c\\" + INFRARED_DIR));
	if (err == en_success)
	{
		creatMultidir(string(strBase + "\\x3c\\" + HIGHFREQ_DIR));
		creatMultidir(string(strBase + "\\x3c\\" + OVERALLVIEW_DIR));
		strBase = getPara()->path2add;
		creatMultidir(string(strBase + "\\x3c\\" + INFRARED_DIR));
		creatMultidir(string(strBase + "\\x3c\\" + HIGHFREQ_DIR));
		creatMultidir(string(strBase + "\\x3c\\" + OVERALLVIEW_DIR));
		strBase = getPara()->rootPath + "\\video";
		creatMultidir(string(strBase + "\\alarm"));
		creatMultidir(string(strBase + "\\tmp"));
		string strCmd = "mklink /j ";
		strCmd += getPara()->rootPath + "\\video\\diskA ";
		strCmd += getPara()->rootPath + "\\x3c";
		systemRun(strCmd.c_str());
		strCmd = "mklink /j ";
		strCmd += getPara()->rootPath + "\\video\\diskB ";
		strCmd += getPara()->path2add + "\\x3c";
		systemRun(strCmd.c_str());

		CString str;
		str.Format(_T("%S\\x3c"),getPara()->rootPath.c_str());
		SetFileAttributes(str, FILE_ATTRIBUTE_HIDDEN);
		str.Format(_T("%S\\x3c"),getPara()->path2add.c_str());
		SetFileAttributes(str, FILE_ATTRIBUTE_HIDDEN);
	}
	return err;
}

int CInitPara::creatMultidir(string &strPath)
{
	int err = en_success;
	CString strDir;
	strDir.Format(_T("%S"),strPath.c_str());
	if (strDir.GetAt(strDir.GetLength() - 1) != _T('\\'))
	{
		strDir.AppendChar(_T('\\'));
	}

	vector<CString> vPath;
	CString strTmp;
	bool bSuccess = false;

	for (int i = 0; i < strDir.GetLength(); ++i)
	{
		if (strDir.GetAt(i) != _T('\\'))
		{
			strTmp.AppendChar(strDir.GetAt(i));
		}
		else
		{
			vPath.push_back(strTmp);
			strTmp.AppendChar(_T('\\'));
		}
	}

	vector<CString>::const_iterator vIter;
	for (vIter = vPath.begin(); vIter != vPath.end(); vIter++)
	{
		if (!PathIsDirectory(*vIter))
		{
			bSuccess = CreateDirectory(*vIter,NULL)? true:false;
		}
	}
	if (bSuccess == false)
	{
		err = en_fail;
	}
	return err;
}
