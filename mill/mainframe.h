#pragma once

#include <wtl/include/atlapp.h>
#include <wtl/include/atlframe.h>
#include <wtl/include/atlcrack.h>
#include "resource.h"

class CMainFrame 
	: public CFrameWindowImpl<CMainFrame>
	, public CUpdateUI<CMainFrame>
	, public CMessageFilter
	, public CIdleHandler
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	BEGIN_MSG_MAP(CMainFrame)
		MSG_WM_DESTROY(OnDestroy)
	END_MSG_MAP()

	BEGIN_UPDATE_UI_MAP(CMainFrame)
	END_UPDATE_UI_MAP()

private:
	virtual BOOL PreTranslateMessage(MSG *msg);
	virtual BOOL OnIdle();

private:
	void OnDestroy();
};
