#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <stdlib.h>
#include <stdio.h>

// SettingDlg 대화 상자입니다.

class SettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SettingDlg)

public:
	SettingDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~SettingDlg();
	FILE *input;
	CString getIp();
	int getPort();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETTINGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString ip;
	int port;
	afx_msg void OnBnClickedOk();
	CIPAddressCtrl m_addressControl;
	CEdit m_port;
};
