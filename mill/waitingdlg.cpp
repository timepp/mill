#include "stdafx.h"
#include "waitingdlg.h"

void CWaitingDlg::WaitingOperation(LPCWSTR title, LPCWSTR info, Operation* op, void* param, HWND parent)
{
	m_title = title;
	m_text = info;
	m_op = op;
	m_param = param;
	DoModal(parent);
}

BOOL CWaitingDlg::OnInitDialog(CWindow focus, LPARAM param)
{
	SetWindowTextW(m_title.c_str());
	SetDlgItemText(IDC_STATIC_INFO, m_text.c_str());
	HANDLE thread = (HANDLE)_beginthreadex(NULL, 0, &CWaitingDlg::ThreadFunc, this, 0, NULL);
	CloseHandle(thread);
	CenterWindow(GetParent());
	return TRUE;
}

LRESULT CWaitingDlg::OnWaitingOperationComplete(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled)
{
	EndDialog(IDOK);
	return 0;
}

unsigned int __stdcall CWaitingDlg::ThreadFunc(void* param)
{
	CWaitingDlg* dlg = (CWaitingDlg*)param;
	(*dlg->m_op)(dlg->m_param);
	dlg->PostMessageW(WM_WATING_OPERATION_COMPLETE);
	return 0;
}
