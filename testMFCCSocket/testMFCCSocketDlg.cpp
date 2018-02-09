
// testMFCCSocketDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

	//初始化Winscok
	if (!AfxSocketInit())
	{
		//AfxMessageBox(L"初始化失败");
		return 1;
	}

	g_bExit = false;

	CtestMFCCSocketDlg *aDlg = (CtestMFCCSocketDlg *)lpPara;

	//获取端口
	/*CString strPort;
	aDlg->GetDlgItemText(IDC_EDIT_PORT, strPort);*/
	UINT nPort = 6000/*atoi(strPort)*/;

	//socket----创建2个socket--------------------------------------------
	CSocket aSocket, serverSocket;
	//最好不要使用aSocket.Create创建，因为容易会出现10048错误
	if (!aSocket.Socket())
	{
		char szError[256] = {0};
		sprintf_s(szError, "Create Faild: %d", GetLastError());
		//AfxMessageBox( szError );
		return 1; 
	}

	BOOL bOptVal = TRUE;
	int bOptLen = sizeof(BOOL);
	//设置Socket的选项, 解决10048错误必须的步骤
	aSocket.SetSockOpt(SO_REUSEADDR, (void *)&bOptVal, bOptLen, SOL_SOCKET);

	//绑定
	if (!aSocket.Bind(nPort))
	{
		char szError[256] = {0};
		sprintf_s(szError, "Bind Faild: %d", GetLastError());
		//AfxMessageBox(szError);	
		return 1; 
	}

	//监听
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
	strText += "服务已经开启! \r\n";
	aDlg->SetDlgItemText(IDC_EDIT_RECV, strText);

	//接收外部连接
	if(!aSocket.Accept(serverSocket))
	{
		
		return 0;
	}
	while(!g_bExit)
	{
		////接收外部连接
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
			
			serverSocket.Receive(szRecvMsg, 256); //接收客户端内容:阻塞
			
			_stprintf_s(szOutMsg, _T("接受到的参数是: %s \r\n"), szRecvMsg);
			
			strText += szOutMsg;
			
			aDlg->SetDlgItemText(IDC_EDIT_RECV, strText);
			
			TCHAR szSndMsg[256];
			
			ZeroMemory(szSndMsg,256);
			
			int nHanzi = _tcslen(_T("服"));
			
			_tcscpy_s(szSndMsg,_T("服务器已经收到，已经做出操作！"));
			
			int nLenSnd = _tcslen(szSndMsg);
			
			serverSocket.Send( szSndMsg, 2*nHanzi*nLenSnd);//发送内容给客户端
			
			//serverSocket.Close();//关闭
		}

	}

	aSocket.Close();
	serverSocket.Close();
	aDlg->GetDlgItemText(IDC_EDIT_RECV, strText);
	strText += "Have Close!";
	aDlg->SetDlgItemText(IDC_EDIT_RECV, strText);
	return 0;
}

// CtestMFCCSocketDlg 对话框
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


// CtestMFCCSocketDlg 消息处理程序

BOOL CtestMFCCSocketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	
	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	client1.Create();  
	client1.Connect(_T("127.0.0.1"),6000);  
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtestMFCCSocketDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtestMFCCSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestMFCCSocketDlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);  
	TCHAR buf[20];
	ZeroMemory(buf,20);
	for(int i=0;i<m_sendtxt.GetLength();i++)//m_sendtxt是文本框关联变量  
	{  
		buf[i] = m_sendtxt.GetAt(i);  
	}  

	int nLen = m_sendtxt.GetLength();
	
	client1.Send(buf,2*nLen);
}
