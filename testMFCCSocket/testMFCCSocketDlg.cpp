
// testMFCCSocketDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "testMFCCSocket.h"
#include "testMFCCSocketDlg.h"
#include "afxdialogex.h"
#include "globalRes.h"

//#pragma comment(lib,"log4cplusD.lib")   
//#pragma comment(lib,"log4cplus/lib/log4cplusUD.lib")
//#pragma comment(lib,"log4cplus.lib")
//#pragma comment(lib,"log4cplusU.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool g_bExit;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

UINT ServerThread(LPVOID lpPara)
{

	//��ʼ��Winscok
	if (!AfxSocketInit())
	{
		//AfxMessageBox(L"��ʼ��ʧ��");
		return 1;
	}

	g_bExit = false;

	CtestMFCCSocketDlg *aDlg = (CtestMFCCSocketDlg *)lpPara;

	//��ȡ�˿�
	/*CString strPort;
	aDlg->GetDlgItemText(IDC_EDIT_PORT, strPort);*/
	UINT nPort = 6000/*atoi(strPort)*/;

	//socket----����2��socket--------------------------------------------
	CSocket aSocket, serverSocket;
	//��ò�Ҫʹ��aSocket.Create��������Ϊ���׻����10048����
	if (!aSocket.Socket())
	{
		char szError[256] = {0};
		sprintf_s(szError, "Create Faild: %d", GetLastError());
		//AfxMessageBox( szError );
		return 1; 
	}

	BOOL bOptVal = TRUE;
	int bOptLen = sizeof(BOOL);
	//����Socket��ѡ��, ���10048�������Ĳ���
	aSocket.SetSockOpt(SO_REUSEADDR, (void *)&bOptVal, bOptLen, SOL_SOCKET);

	//��
	if (!aSocket.Bind(nPort))
	{
		char szError[256] = {0};
		sprintf_s(szError, "Bind Faild: %d", GetLastError());
		//AfxMessageBox(szError);	
		return 1; 
	}

	//����
	if(!aSocket.Listen(10))
	{	
		char szError[256] = {0};
		sprintf_s(szError, "Listen Faild: %d", GetLastError());
		//AfxMessageBox(szError);
		
		return 1;
	}

	CLog::getSingleton()->setLogMode(true,wstring(L"111111.log"));

	Logger _logger = Logger::getInstance(L"test");
	
	LOG4CPLUS_INFO(CLog::getSingleton()->_logger=_logger,"ins data overflow , buff_len = 0 ");
	CString strText;
	aDlg->GetDlgItemText(IDC_EDIT_RECV, strText);
	strText += "�����Ѿ�����! \r\n";
	aDlg->SetDlgItemText(IDC_EDIT_RECV, strText);

	//�����ⲿ����
	if(!aSocket.Accept(serverSocket))
	{
		
		return 0;
	}
	while(!g_bExit)
	{
		////�����ⲿ����
		//if(!aSocket.Accept(serverSocket))
		//{
		//	continue;
		//}
		//else
		{
			TCHAR szRecvMsg[256] = {0};

			ZeroMemory(szRecvMsg,256);
			
			TCHAR szOutMsg[256] = {0};

			ZeroMemory(szOutMsg,256);
			
			serverSocket.Receive(szRecvMsg, 256); //���տͻ�������:����
			
			_stprintf_s(szOutMsg, _T("���ܵ��Ĳ�����: %s \r\n"), szRecvMsg);
			
			strText += szOutMsg;
			
			aDlg->SetDlgItemText(IDC_EDIT_RECV, strText);
			
			TCHAR szSndMsg[256];
			
			ZeroMemory(szSndMsg,256);
			
			int nHanzi = _tcslen(_T("��"));
			
			_tcscpy_s(szSndMsg,_T("�������Ѿ��յ����Ѿ�����������"));
			
			int nLenSnd = _tcslen(szSndMsg);
			
			serverSocket.Send( szSndMsg, 2*nHanzi*nLenSnd);//�������ݸ��ͻ���
			
			//serverSocket.Close();//�ر�
		}

	}

	aSocket.Close();
	serverSocket.Close();
	aDlg->GetDlgItemText(IDC_EDIT_RECV, strText);
	strText += "Have Close!";
	aDlg->SetDlgItemText(IDC_EDIT_RECV, strText);
	return 0;
}

// CtestMFCCSocketDlg �Ի���
CtestMFCCSocketDlg::CtestMFCCSocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtestMFCCSocketDlg::IDD, pParent)
	, m_sendtxt(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	AfxBeginThread(ServerThread,this);
}

void CtestMFCCSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEND, m_sendtxt);
}

BEGIN_MESSAGE_MAP(CtestMFCCSocketDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CtestMFCCSocketDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CtestMFCCSocketDlg ��Ϣ�������

BOOL CtestMFCCSocketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	client1.Create();  
	client1.Connect(_T("127.0.0.1"),6000);  
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CtestMFCCSocketDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtestMFCCSocketDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtestMFCCSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestMFCCSocketDlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);  
	TCHAR buf[20];
	ZeroMemory(buf,20);
	for(int i=0;i<m_sendtxt.GetLength();i++)//m_sendtxt���ı����������  
	{  
		buf[i] = m_sendtxt.GetAt(i);  
	}  

	int nLen = m_sendtxt.GetLength();
	
	client1.Send(buf,2*nLen);
}
