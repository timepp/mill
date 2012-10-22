#pragma once

#include "resource.h"
#include <string>

/// 一个阻塞性的模态对话框，当给定操作执行完后，自动结束

#define WM_WATING_OPERATION_COMPLETE WM_USER+0x11

class CWaitingDlg 
	: public CDialogImpl<CWaitingDlg>
{
public:
	enum {IDD = IDD_WAITING};

	BEGIN_MSG_MAP(CWaitingDlg)
		MESSAGE_HANDLER(WM_WATING_OPERATION_COMPLETE, OnWaitingOperationComplete)
		MSG_WM_INITDIALOG(OnInitDialog)
	END_MSG_MAP()

public:
	typedef void Operation(void* param);
	void WaitingOperation(LPCWSTR title, LPCWSTR info, Operation* op, void* param, HWND parent);

private:
	static unsigned int __stdcall ThreadFunc(void* param);
	LRESULT OnWaitingOperationComplete(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled);
	BOOL OnInitDialog(CWindow focus, LPARAM param);

private:
	std::wstring m_title;
	std::wstring m_text;
	Operation* m_op;
	void* m_param;
};

