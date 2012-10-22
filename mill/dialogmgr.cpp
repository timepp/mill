#include "stdafx.h"
#include "dialogmgr.h"
#include "medicationdlg.h"

CDialogMgr::CDialogMgr() : m_hook(NULL)
{
//	m_hook = SetWindowsHookExW(WH_CALLWNDPROCRET, &CDialogMgr::HookProc, NULL, GetCurrentThreadId());
//	BD_CHECK(m_hook, LOGERROR_WIN);
}

CDialogMgr::~CDialogMgr()
{
	if (m_hook)
	{
		::UnhookWindowsHookEx(m_hook);
	}
}

LRESULT CDialogMgr::HookProc(int code, WPARAM wp, LPARAM lp)
{
	if (code < 0)
	{
		return ::CallNextHookEx(NULL, code, wp, lp);
	}
	else
	{
		//LPCWPRETSTRUCT wpr = (LPCWPRETSTRUCT)lp;
		//if (wpr->message == WM_DESTROY)
		//{
		//	tp::servicemgr::get<CDialogMgr>()->RemoveWindow(wpr->hwnd);
		//}
	}
	return 0;
}

void CDialogMgr::NewMedicationDlg(HWND parent)
{
	CMedicationDlg* dlg = new CMedicationDlg;
	dlg->Create(parent);
	dlg->CenterWindow(GetActiveWindow());
	dlg->ShowWindow(SW_SHOW);
	m_medicationWndMap[dlg->m_hWnd] = dlg;
}

bool CDialogMgr::RemoveWindow(HWND hwnd)
{
	auto it = m_medicationWndMap.find(hwnd);
	if (it != m_medicationWndMap.end())
	{
		delete it->second;
		m_medicationWndMap.erase(it);
		return true;
	}

	return false;
}
