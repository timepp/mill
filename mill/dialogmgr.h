#pragma once

/// 非模态对话框管理器

#include "serviceid.h"
#include <tplib/include/service.h>
#include <map>

class CMedicationDlg;

class CDialogMgr : public tp::service_impl<SID_DialogMgr>
{
public:
	CDialogMgr();
	~CDialogMgr();

	/// 新创建一个医疗记录
	void NewMedicationDlg(HWND parent);

	bool RemoveWindow(HWND hwnd);
	
private:
	static LRESULT __stdcall HookProc(int code, WPARAM wp, LPARAM lp);

private:
	std::map<HWND, CMedicationDlg*> m_medicationWndMap;
	HHOOK m_hook;
};


DEFINE_SERVICE(CDialogMgr, L"对话框管理器");

