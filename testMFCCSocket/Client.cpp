#include "stdafx.h"
#include "Client.h"
#include "testMFCCSocket.h"
#include "testMFCCSocketDlg.h"

CClient::CClient(void)
{
}


CClient::~CClient(void)
{
}


void CClient::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	TCHAR buf[128]={0};  
	int recelen=Receive(buf,1024);  
	CString str(buf);  

	((CtestMFCCSocketDlg*)theApp.GetMainWnd())->SetDlgItemText(IDC_EDIT_SEND, str);//IDC_EDIT_SEND显示数据的文本框ID  

	CSocket::OnReceive(nErrorCode);
}
