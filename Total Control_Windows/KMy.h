
#include <WinSock2.h>
#include <IPHlpApi.h>
#if !defined(AFX_KMY_H__9A942ABD_5FDB_40F5_8472_2574A1D46397__INCLUDED_)
#define AFX_KMY_H__9A942ABD_5FDB_40F5_8472_2574A1D46397__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KMy.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// KMy command target
class CWindowsClientDlg;

class KMy : public CAsyncSocket
{
// Attributes
public:
	CWindowsClientDlg* m_pDlg;
	PIP_ADAPTER_INFO pAdapterInfo;
// Operations
public:
	KMy();
	virtual ~KMy();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(KMy)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(KMy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation

	unsigned char * GetMACAddress();
protected:
public:
	virtual void OnReceive(int nErrorCode);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KMY_H__9A942ABD_5FDB_40F5_8472_2574A1D46397__INCLUDED_)
