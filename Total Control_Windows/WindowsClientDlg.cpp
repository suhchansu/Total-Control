
// WindowsClientDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "WindowsClient.h"
#include "WindowsClientDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define UM_RECEIVE WM_USER+11
#define WM_ICON_NOTIFY WM_USER+10
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CWindowsClientDlg 대화 상자



CWindowsClientDlg::CWindowsClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWindowsClientDlg::IDD, pParent)
{
	mIP = _T("127.0.0.1");   //Create할때 IP는 사용가능한 값으로
	mPort = 6000;  //최초포트세팅은 서버와 다른값으로 해주거나 Create()에서 첫번째 인자를 0U로 할것
	message = _T("hello");

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CWindowsClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWindowsClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CWindowsClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CWindowsClientDlg::OnBnClickedButton2)
//	ON_WM_SIZE()
	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification)
	ON_MESSAGE(UM_RECEIVE,OnReceive)
	ON_COMMAND(ID_FILE_EXIT, &CWindowsClientDlg::OnFileExit)
	ON_COMMAND(ID_FILE_SHOW, &CWindowsClientDlg::OnFileShow)

//	ON_WM_SHOWWINDOW()
ON_WM_SIZE()
ON_BN_CLICKED(IDC_BUTTON3, &CWindowsClientDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CWindowsClientDlg 메시지 처리기

BOOL CWindowsClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	if(!m_TrayIcon.Create(this,WM_ICON_NOTIFY,_T("트레이 아이콘 예제"),NULL,IDR_MAINFRAME))
	{
		return -1;
	}
	m_TrayIcon.SetIcon(IDR_MAINFRAME);

	
	m_My.m_pDlg=this;
	
	BOOL bRet=m_My.Create(0U,SOCK_DGRAM,FD_READ | FD_WRITE);
	//BOOL bRet = m_My.Create(m_port,SOCK_DGRAM,FD_READ | FD_WRITE);  
	if (bRet != TRUE)       
	{              
		UINT uErr = GetLastError();              
		TCHAR szError[256];              
		wsprintf(szError, L"Server Receive Socket Create() failed: %d", uErr);              
		AfxMessageBox(szError);       
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CWindowsClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CWindowsClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CWindowsClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWindowsClientDlg::OnBnClickedButton1()  //connect 버튼 클릭부입니다.
{

	m_Setting.input=fopen("settingIO.txt","rt");//setting정보를 저장하고 있는 파일을 연다.
	char *ip=(char*)malloc(sizeof(char)*16);  //아이피를 읽어옴
	memset(ip,0,10);  
	mPort=10000;
	fscanf(m_Setting.input,"%s %d",ip,&mPort);  //포트도 읽어옴
	
	fclose(m_Setting.input);  //파일 닫음
	if(ip==NULL || mPort==10000)  //잘못됐으면 애러호출
	{
		wsprintf(szError, _T("IP or Port not insert"));
			AfxMessageBox(szError);
	}
	else  //아니면 동작
	{
		int i;
		unsigned char *addressBuffer=m_My.GetMACAddress();//내 아이피 얻어옴
		unsigned char buff[160];  //전송용 버퍼
		LPDWORD nSize=new DWORD(MAX_COMPUTERNAME_LENGTH+1);//내 피시이름사이즈 저장변수
		pcName=new WCHAR();  //피시이름 저장변수 생성
		GetComputerName(pcName,nSize); //피시이름 얻어옴
		int pcXSize=GetSystemMetrics(SM_CXFULLSCREEN); //수평사이즈 얻어옴
		int pcYSize=GetSystemMetrics(SM_CYFULLSCREEN);  //수직사이즈 얻어옴

		for(i=0;i<wcslen(pcName);i++)
		{
			buff[i]=pcName[i];  //피시 이름을 버퍼에 집어넣음
		}
		buff[i++]='_';
		for(int j=0;j<6;j++)
		{
			buff[i++]=addressBuffer[j]/10;  //아이피에서 .으로 구분되는 각 자리를 2자리 수나 1자리 수로 분해해서 2인덱스에 각 각 저장함
			buff[i++]=addressBuffer[j]%10;
		}
		buff[i++]='_';
		buff[i++]=pcXSize/100;  //피시 사이즈도 분해해서 집어넣음
		buff[i++]=pcXSize%100;
		buff[i++]='_';
		buff[i++]=pcYSize/100;  //피시 사이즈도 분해해서 집어넣음
		buff[i++]=pcYSize%100;
		buff[i++]='_';
		SOCKADDR_IN saddr;
		memset(&saddr,0,sizeof(saddr));
		saddr.sin_family=AF_INET;
		saddr.sin_addr.s_addr=inet_addr(ip); //ip   
		saddr.sin_port=htons(mPort);  //포트

		//BOOL boolean=TRUE;// (WOL실험용변수)
		//m_My.SetSockOpt(SO_BROADCAST,(char*)&boolean,sizeof BOOL);  //브로드케스트로 전환(wol 실험용)

		m_My.Connect((SOCKADDR*)&saddr,sizeof(saddr));  //서버 연결시작
		//	m_My.SendTo(buff,sizeof(buff),(SOCKADDR*)&saddr,sizeof(saddr));
		m_My.Send(buff,sizeof(buff),0);  //시작 신호 보냄
		//m_My.SendTo(buff,102,mPort);
		unsigned char buff2[160]={0,};  //수신용 버퍼
		Sleep(1000);
		m_My.Receive(buff2,sizeof(buff2),0);  //수신
		//연결될시에 되돌아오는신호를 받음 (CAsyncSocket connect UDP클래스 라서 receive도 논블록킹)

		if(buff2[0]!=NULL)
		{
			wsprintf(szError, _T("Server Connect Success"));
			AfxMessageBox(szError);

			////////////////////////////////////
			//구현부분
		}
		else
		{
			wsprintf(szError, _T("Server Connect Fail"));
			AfxMessageBox(szError);
		}
	}
}


void CWindowsClientDlg::OnBnClickedButton2()  //disconnect 클릭부입니다.
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다. 클릭과 동시에 통신종료
	m_TrayIcon.RemoveIcon();
	m_My.Close();
	this->OnOK();
}


//void CWindowsClientDlg::OnSize(UINT nType, int cx, int cy)
//{
//	CDialogEx::OnSize(nType, cx, cy);
//	ShowWindow(SW_HIDE);
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//
//}

LRESULT CWindowsClientDlg::OnTrayNotification(WPARAM wParam,LPARAM lParam)  //트레이아이콘 생성부
{
	CMenu menu, *pSubMenu;

	if(LOWORD(lParam)==WM_RBUTTONUP)
	{
		if(!menu.LoadMenu(IDR_MENU1))
		{
			return 0;
		}
		if(!(pSubMenu=menu.GetSubMenu(0)))
		{
			return 0;
		}

		CPoint pos;
		GetCursorPos(&pos);
		SetForegroundWindow();
		pSubMenu->TrackPopupMenu(TPM_RIGHTALIGN, pos.x, pos.y, this);
		menu.DestroyMenu();
	}

	else if(LOWORD(lParam)==WM_LBUTTONDBLCLK)
	{
		//SendMessage(WM_COMMAND,ID_APP_ABOUT);
		ShowWindow(SW_SHOWNORMAL);
	}
	return 1;
}

void CWindowsClientDlg::OnFileExit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	OnOK();
}


void CWindowsClientDlg::OnFileShow()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ShowWindow(SW_SHOWNORMAL);

}

void CWindowsClientDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(nType==SIZE_RESTORED)
	{
		ShowWindow(SW_SHOW);
	}
	else
	{
		ShowWindow(SW_HIDE);
		
	}
}

LRESULT CWindowsClientDlg::OnReceive(WPARAM wParam,LPARAM lParam)  //데이터 수신부입니다.
{

	int mouseX,mouseY;
	int mouseState;
	char *px,*py,*ps;;
	char *ptr;
	char buff[160];
	m_My.Receive(buff,sizeof(buff),0);    //수신을 받는다.
	
	ptr=strtok(buff," ");
	px=strtok(NULL," ");
	py=strtok(NULL," ");
	ps=strtok(NULL," ");
	mouseX=atoi(px);
	mouseY=atoi(py);
	mouseState=atoi(ps);

	if(*ptr=='0')  //마우스
	{
		if(mouseState==1)  // 좌클릭
		{
			SetCursorPos(mouseX,mouseY);  //이동
			mouse_event(MOUSEEVENTF_LEFTDOWN,mouseX,mouseY,0,0);  //마우스 왼쪽키를 누름
			mouse_event(MOUSEEVENTF_LEFTUP,mouseX,mouseY,0,0);   //마우스 왼쪽키를 땜
		}
		else if(mouseState==2)  //우클릭
		{
			SetCursorPos(mouseX,mouseY);  //이동
			mouse_event(MOUSEEVENTF_RIGHTDOWN,mouseX,mouseY,0,0);  //마우스 우클릭키 누름
			mouse_event(MOUSEEVENTF_RIGHTUP,mouseX,mouseY,0,0);   //마우스 우클릭키 땜
		}
		else if(mouseState==4)  //휠이동
		{
			mouse_event(MOUSEEVENTF_WHEEL,postx,posty,mouseX,0);  //휠이동
		}
		else
		{
			SetCursorPos(mouseX,mouseY);  //그냥 이동만함
		}
		postx=mouseX;  //현재 좌표가 과거좌표가됨
		posty=mouseY;  //현재 좌표가 과거좌표가됨
	}
	else if(*ptr=='1') //키보드
	{
		if(mouseY==0)  //누를때
		{
			keybd_event(transScan(mouseX),mouseX,0,0);
		}
		else if(mouseX==1)  //땔때
		{
			keybd_event(transScan(mouseX),mouseX,KEYEVENTF_KEYUP,0);
		}
	}

	return 0L;
}

int CWindowsClientDlg::transScan(int scancode)  //키보드 스캔코드로변환함수 (미완성)
{
	if(scancode==11)
	{
		return scancode+37;
	}
	else if(2<=scancode && scancode<=10)
	{
		return scancode+47;
	}
	else
	{
		switch(scancode)
		{
		case 16:
			return 81;
			break;
		case 17:
			return 87;
			break;
		case 18:
			return 69;
			break;
		case 19:
			return 82;
			break;
		case 20:
			return 84;
			break;
		case 21:
			return 89;
			break;
		case 22:
			return 85;
			break;
		case 23:
			return 73;
			break;
		case 24:
			return 79;
			break;
		case 25:
			return 80;
			break;
		case 30:
			return 65;
			break;
		case 31:
			return 83;
			break;
		case 32:
			return 68;
			break;
		case 33:
			return 70;
			break;
		case 34:
			return 71;
			break;
		case 35:
			return 72;
			break;
		case 36:
			return 74;
			break;
		case 37:
			return 75;
			break;
		case 38:
			return 76;
			break;
		case 44:
			return 90;
			break;
		case 45:
			return 88;
			break;
		case 46:
			return 67;
			break;
		case 47:
			return 86;
			break;
		case 48:
			return 66;
			break;
		case 49:
			return 78;
			break;
		case 50:
			return 77;
			break;
		case 12:
			return 45;
			break;
		case 13:
			return 43; 
			break;
		case 26:
			return 91;
			break;
		case 27:
			return 93;
			break;
		case 39:
			return 58;
			break;
		case 40:
			return 34;
			break;
		case 51:
			return 44;
			break;


		}
	}
}
void CWindowsClientDlg::OnBnClickedButton3()  //setting버튼을 누르면 setting클래스가 호출됨
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_Setting.DoModal();  //setting창아 보여라!!!!!!!!!
}
