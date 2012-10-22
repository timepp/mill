#pragma once

/// ��ģ̬�Ի��������

#include "serviceid.h"
#include <tplib/include/service.h>
#include <map>

class CMedicationDlg;

class CDialogMgr : public tp::service_impl<SID_DialogMgr>
{
public:
	CDialogMgr();
	~CDialogMgr();

	/// �´���һ��ҽ�Ƽ�¼
	void NewMedicationDlg(HWND parent);

	bool RemoveWindow(HWND hwnd);
	
private:
	static LRESULT __stdcall HookProc(int code, WPARAM wp, LPARAM lp);

private:
	std::map<HWND, CMedicationDlg*> m_medicationWndMap;
	HHOOK m_hook;
};


DEFINE_SERVICE(CDialogMgr, L"�Ի��������");

