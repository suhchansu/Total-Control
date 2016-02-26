#pragma once
#include "afx.h"
class CTrayIcon :
	public CObject
{
public:
	CTrayIcon(void);
	~CTrayIcon(void);
	BOOL Create(CWnd * pWnd, UINT uCallbackMessage, LPCTSTR szToolTip, HICON icon, UINT uID);
	NOTIFYICONDATA m_tnd;
	BOOL SetIcon(HICON hIcon);
	BOOL SetIcon(LPCTSTR lpszIconName);
	BOOL SetIcon(UINT nIDResource);
	BOOL SetTooltipText(LPCTSTR pszTip);
	BOOL SetTooltipText(UINT nID);
	void RemoveIcon(void);
};

