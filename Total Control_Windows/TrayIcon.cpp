#include "stdafx.h"
#include "TrayIcon.h"
#include <Windows.h>


CTrayIcon::CTrayIcon(void)
{
}


CTrayIcon::~CTrayIcon(void)
{
}


BOOL CTrayIcon::Create(CWnd * pWnd, UINT uCallbackMessage, LPCTSTR szToolTip, HICON icon, UINT uID)
{
	m_tnd.cbSize=sizeof(NOTIFYICONDATA);
	m_tnd.hWnd=pWnd->GetSafeHwnd();
	m_tnd.uID=uID;
	m_tnd.hIcon=icon;
	m_tnd.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
	m_tnd.uCallbackMessage=uCallbackMessage;
	wcscpy(m_tnd.szTip,szToolTip);


	return Shell_NotifyIcon(NIM_ADD,&m_tnd);;
}


BOOL CTrayIcon::SetIcon(HICON hIcon)
{
	m_tnd.uFlags=NIF_ICON;
	m_tnd.hIcon=hIcon;
	return Shell_NotifyIcon(NIM_MODIFY,&m_tnd);
}


BOOL CTrayIcon::SetIcon(LPCTSTR lpszIconName)
{
	HICON hIcon=AfxGetApp()-> LoadIcon(lpszIconName);
	return SetIcon(hIcon);
}


BOOL CTrayIcon::SetIcon(UINT nIDResource)
{
	HICON hIcon=AfxGetApp()->LoadIcon(nIDResource);
	return SetIcon(hIcon);
}


BOOL CTrayIcon::SetTooltipText(LPCTSTR pszTip)
{
	m_tnd.uFlags=NIF_TIP;
	_tcscpy(m_tnd.szTip,pszTip);
	return Shell_NotifyIcon(NIM_MODIFY,&m_tnd);
}


BOOL CTrayIcon::SetTooltipText(UINT nID)
{
	CString strText;
	VERIFY(strText.LoadString(nID));
	return SetTooltipText(strText);
}


void CTrayIcon::RemoveIcon(void)
{
	m_tnd.uFlags=0;
	Shell_NotifyIcon(NIM_DELETE,&m_tnd);
}
