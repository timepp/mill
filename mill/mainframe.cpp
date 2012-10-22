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
		const Medicine* m = mgr->GetMedicine(L"������");
	}
	{
		PeopleMgr* mgr = tp::servicemgr::get<PeopleMgr>();
		People* p = mgr->GetPeople(L"����");
		p->address += tp::cz(L"%u", p->address.length());
		std::vector<const People*> ps = mgr->Search(L"��");
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
	dlg.WaitingOperation(L"��Ϣ", L"����EXCEL�����б༭ҩƷ��Ϣ����ɱ༭��ر�EXCEL���ڡ�", &inner::EditData, NULL, m_hWnd);

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
	dlg.WaitingOperation(L"��Ϣ", L"����EXCEL�����б༭������Ϣ����ɱ༭��ر�EXCEL���ڡ�", &inner::EditData, NULL, m_hWnd);

	return 0;
}

LRESULT CMainFrame::OnNewMedication(UINT, UINT, HWND, BOOL&)
{
	tp::servicemgr::get<CDialogMgr>()->NewMedicationDlg(m_hWnd);

	return 0;
}
