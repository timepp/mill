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
	DECLARE_FRAME_WND_CLASS(L"mill", IDR_MAINFRAME);

	BEGIN_MSG_MAP(CMainFrame)
		MSG_WM_DESTROY(OnDestroy)
		COMMAND_ID_HANDLER(IDM_TEST, OnTest)
		COMMAND_ID_HANDLER(ID_EDIT_MEDICINE, OnEditMedicine)
		COMMAND_ID_HANDLER(ID_EDIT_PEOPLE, OnEditPeople)
		COMMAND_ID_HANDLER(ID_NEW_MEDICATION, OnNewMedication)
	END_MSG_MAP()

	BEGIN_UPDATE_UI_MAP(CMainFrame)
	END_UPDATE_UI_MAP()

private:


private:
	virtual BOOL PreTranslateMessage(MSG *msg);
	virtual BOOL OnIdle();

private:
	void OnDestroy();
	LRESULT OnTest(UINT, UINT, HWND, BOOL& bHandled);
	LRESULT OnEditMedicine(UINT, UINT, HWND, BOOL& bHandled);
	LRESULT OnEditPeople(UINT, UINT, HWND, BOOL& bHandled);
	LRESULT OnNewMedication(UINT, UINT, HWND, BOOL& bHandled);
};
