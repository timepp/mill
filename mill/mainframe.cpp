#include "stdafx.h"
#include "mainframe.h"
#include "medicinemgr.h"
#include "peoplemgr.h"
#include "dialogmgr.h"
#include "waitingdlg.h"

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

LRESULT CMainFrame::OnTest(UINT, UINT, HWND, BOOL& bHandled)
{
	{
		MedicineMgr* mgr = tp::servicemgr::get<MedicineMgr>();
		const Medicine* m = mgr->GetMedicine(L"决明子");
	}
	{
		PeopleMgr* mgr = tp::servicemgr::get<PeopleMgr>();
		People* p = mgr->GetPeople(L"张三");
		p->address += tp::cz(L"%u", p->address.length());
		std::vector<const People*> ps = mgr->Search(L"张");
		ps = mgr->Search(L"zh");
	}
	return 0;
}

LRESULT CMainFrame::OnEditMedicine(UINT, UINT, HWND, BOOL&)
{
	struct inner
	{
		static void EditData(void* param)
		{
			tp::servicemgr::get<MedicineMgr>()->ShellEditMedicineData();
		}
	};

	CWaitingDlg dlg;
	dlg.WaitingOperation(L"信息", L"请在EXCEL窗口中编辑药品信息，完成编辑后关闭EXCEL窗口。", &inner::EditData, NULL, m_hWnd);

	return 0;
}

LRESULT CMainFrame::OnEditPeople(UINT, UINT, HWND, BOOL&)
{
	struct inner
	{
		static void EditData(void* param)
		{
			tp::servicemgr::get<PeopleMgr>()->ShellEditPeopleData();
		}
	};

	CWaitingDlg dlg;
	dlg.WaitingOperation(L"信息", L"请在EXCEL窗口中编辑患者信息，完成编辑后关闭EXCEL窗口。", &inner::EditData, NULL, m_hWnd);

	return 0;
}

LRESULT CMainFrame::OnNewMedication(UINT, UINT, HWND, BOOL&)
{
	tp::servicemgr::get<CDialogMgr>()->NewMedicationDlg(m_hWnd);

	return 0;
}
