
// testMFCCSocketDlg.h : ͷ�ļ�
//

#pragma once

#include "Client.h"

// CtestMFCCSocketDlg �Ի���
class CtestMFCCSocketDlg : public CDialogEx
{
// ����
public:
	CtestMFCCSocketDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTMFCCSOCKET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSend();

private:
	CClient client1;
public:
	CString m_sendtxt;
};
