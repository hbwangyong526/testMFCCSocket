#pragma once
#include "afxsock.h"
class CClient :
	public CSocket
{
public:
	CClient(void);
	~CClient(void);
	virtual void OnReceive(int nErrorCode);
};

