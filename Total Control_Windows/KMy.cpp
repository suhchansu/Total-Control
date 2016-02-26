// KMy.cpp : implementation file
//

#include "stdafx.h"
#include "WindowsClient.h"
#include "KMy.h"
#include "WindowsClientDlg.h"


#ifdef _DEBUG
#define UM_RECEIVE (WM_USER+11)
#define new DEBUG_NEW
#undef THIS_FILE

static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// KMy

KMy::KMy()
{
}

KMy::~KMy()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(KMy, CAsyncSocket)
	//{{AFX_MSG_MAP(KMy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// KMy member functions




void KMy::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pDlg->SendMessage(UM_RECEIVE);
	CAsyncSocket::OnReceive(nErrorCode);
}


 unsigned char * KMy::GetMACAddress()
{
	IP_ADAPTER_INFO AdapterInfo[16];       // Allocate information for up to 16 NICs
	DWORD dwBufLen = sizeof (AdapterInfo);  // Save memory size of buffer

	DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);                  // [in] size of receive data buffer
	if (dwStatus != ERROR_SUCCESS)
	{
		printf ("GetAdaptersInfo failed. err=%d\n", GetLastError ());
		return 0;
	}

	pAdapterInfo = AdapterInfo; // Contains pointer to  current adapter info
	//do 
	//{
	//	//PrintMACaddress(pAdapterInfo->Address); // Print MAC address
	//	pAdapterInfo = pAdapterInfo->Next;    // Progress through linked list
	//} while (pAdapterInfo);                    // Terminate if last adapter
	return pAdapterInfo->Address;



}