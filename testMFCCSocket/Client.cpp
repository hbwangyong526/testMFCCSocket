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
	// TODO: �ڴ����ר�ô����/����û���
	TCHAR buf[128]={0};  
	int recelen=Receive(buf,1024);  
	CString str(buf);  

	((CtestMFCCSocketDlg*)theApp.GetMainWnd())->SetDlgItemText(IDC_EDIT_SEND, str);//IDC_EDIT_SEND��ʾ���ݵ��ı���ID  

	CSocket::OnReceive(nErrorCode);
}
