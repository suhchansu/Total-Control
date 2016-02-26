// SettingDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "WindowsClient.h"
#include "SettingDlg.h"
#include "afxdialogex.h"


// SettingDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(SettingDlg, CDialogEx)

	SettingDlg::SettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(SettingDlg::IDD, pParent)
{

}

SettingDlg::~SettingDlg()
{
}

void SettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_addressControl);
	DDX_Control(pDX, IDC_EDIT2, m_port);
}


BEGIN_MESSAGE_MAP(SettingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &SettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// SettingDlg 메시지 처리기입니다.


void SettingDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BYTE B_ip[4];
	int I_ip[4];
	char *temp_ip=new char;
	CString temp_str_port;

	m_addressControl.GetAddress(B_ip[0],B_ip[1],B_ip[2],B_ip[3]);

	input=fopen("settingIO.txt","wt");
	for(int i=0;i<4;i++)
	{
		I_ip[i]=B_ip[i];
		itoa(I_ip[i],temp_ip,10);
		//fprintf(input,"%s",temp_ip);
		ip+=temp_ip;
		if(i<3)
		{
			ip.AppendChar('.');
			//fprintf(input,".");
		}
	}
//	fprintf(input,"\n");
	m_port.GetWindowTextW(temp_str_port);
	port=_ttoi(temp_str_port);
	
	//fprintf(input,"%d",port);


	char *str;
	int length=ip.GetLength();
	str=new char[length+1];

	WideCharToMultiByte(CP_ACP,0,(LPCWSTR)ip,length+1,str,length+1,NULL,NULL);
	str[length+1]='\0';
	fprintf(input,"%s\n",str);
	fprintf(input,"%d",port);
	
	fclose(input);

	CDialogEx::OnOK();
}


CString SettingDlg::getIp()
{
	return ip;
}

int SettingDlg::getPort()
{
	return port;
}