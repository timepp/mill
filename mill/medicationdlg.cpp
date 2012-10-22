#include "stdafx.h"
#include "medicationdlg.h"
#include "dialogmgr.h"
#include "peoplemgr.h"
#include "hlp.h"

LRESULT CMedicationDlg::OnInitDialog(HWND hwnd, LPARAM param)
{
	RECT rc;
	GetDlgItem(IDC_STATIC_MEDICAL_RECORD).GetWindowRect(&rc);
	ScreenToClient(&rc);
	m_dlg.Create(m_hWnd, rc, NULL);
	m_dlg.SetDlgCtrlID(ID_MEDICAL_RECORD);
	m_dlg.MoveWindow(&rc);
	m_dlg.ShowWindow(SW_SHOW);

	CComboBox combo = ::GetDlgItem(m_hWnd, IDC_GENDER);
	combo.AddString(L"ÄÐ");
	combo.AddString(L"Å®");

	m_nameEdit.SetSuggestionProvider(tp::servicemgr::get<PeopleMgr>());
	m_nameEdit.SubclassWindow(GetDlgItem(IDC_NAME));
	
	DlgResize_Init();
	return 0;
}

void CMedicationDlg::OnClose()
{
	DestroyWindow();
}

void CMedicationDlg::OnFinalMessage(HWND hwnd)
{
	tp::servicemgr::get<CDialogMgr>()->RemoveWindow(hwnd);
}


LRESULT CMedicationDlg::OnEnChangeName(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	std::wstring name = hlp::GetDlgItemString(m_hWnd, IDC_NAME);
	const People* p = tp::servicemgr::get<PeopleMgr>()->GetPeople(name);
	LoadPeople(p);

	return 0;
}


LRESULT CMedicationDlg::OnDtnDatetimechangeBirthday(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	return 0;
}


LRESULT CMedicationDlg::OnEnChangeAge(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	std::wstring age = hlp::GetDlgItemString(m_hWnd, IDC_AGE);
	CDateTimePickerCtrl dtp = (HWND)GetDlgItem(IDC_BIRTHDAY);

	return 0;
}


LRESULT CMedicationDlg::OnBnClickedOk(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	std::wstring name = hlp::GetDlgItemString(m_hWnd, IDC_NAME);
	People* p = tp::servicemgr::get<PeopleMgr>()->GetPeople(name, true);
	SavePeople(p);
	return 0;
}

void CMedicationDlg::SavePeople(People* p)
{
	p->address = hlp::GetDlgItemString(m_hWnd, IDC_ADDRESS);
	p->comment = hlp::GetDlgItemString(m_hWnd, IDC_COMMENT);
	p->idnumber = hlp::GetDlgItemString(m_hWnd, IDC_COMMENT);
	p->contact = hlp::GetDlgItemString(m_hWnd, IDC_CONTACT);
	p->gender = hlp::GetDlgItemString(m_hWnd, IDC_GENDER);
}

void CMedicationDlg::LoadPeople(const People* p)
{
	People nullpeople;
	if (p == NULL)
	{
		p = &nullpeople;
	}

	hlp::SetDlgItemString(m_hWnd, IDC_COMMENT, p->comment);
	hlp::SetDlgItemString(m_hWnd, IDC_ADDRESS, p->address);
	hlp::SetDlgItemString(m_hWnd, IDC_IDNUMBER, p->idnumber);
	hlp::SetDlgItemString(m_hWnd, IDC_CONTACT, p->contact);
	CComboBox combo = ::GetDlgItem(m_hWnd, IDC_GENDER);
	combo.SelectString(0, p->gender.c_str());
}
