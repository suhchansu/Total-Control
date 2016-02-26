
// WindowsClientDlg.h : 헤더 파일
//

#pragma once
//#include "trayicon.h"
#include "TrayIcon.h"
#include "KMy.h"
#include "SettingDlg.h"
#include <stdio.h>

// CWindowsClientDlg 대화 상자
class CWindowsClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CWindowsClientDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WINDOWSCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
//	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnTrayNotification(WPARAM wParam,LPARAM lParam);
	CTrayIcon m_TrayIcon;
	afx_msg void OnFileExit();
	afx_msg void OnFileShow();
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnReceive(WPARAM wParam,LPARAM lParam);
	int transScan(int scancode);
public:

	int postx,posty;
	SettingDlg m_Setting;
	KMy m_My;
	char *ip;
	int mPort;
	CString message;
	CString mIP;
	TCHAR szError[256];
	LPWSTR pcName;
	afx_msg void OnBnClickedButton3();
};
