#include "stdafx.h"
#include "mainframe.h"

BOOL CMainFrame::PreTranslateMessage(MSG* msg)
{
	return FALSE;
}

BOOL CMainFrame::OnIdle()
{
	return TRUE;
}

void CMainFrame::OnDestroy()
{
	::PostQuitMessage(0);
}