#pragma once

#include "resource.h"
#include <vector>
#include <string>
#include <tplib\include\msg_crack.h>

enum EditCommandID
{
	Command_HideList = 0x100,
	Command_ApplySuggestion,
};

class CSuggestionListCtrl : 
	public CWindowImpl<CSuggestionListCtrl, CListViewCtrl> 
{
public:
	BEGIN_MSG_MAP(CSuggestionListCtrl)
		MESSAGE_HANDLER(WM_MOUSEACTIVATE, OnMouseActivate)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnMouseAction)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnMouseAction)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnMouseAction)
		MESSAGE_HANDLER(WM_RBUTTONUP, OnMouseAction)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnMouseAction)
	END_MSG_MAP()

	void SetEditWindow(HWND hwnd)
	{
		m_edit = hwnd;
	}

private:
	LRESULT OnMouseActivate(UINT, WPARAM, LPARAM, BOOL&)
	{
		return MA_NOACTIVATE;
	}
	LRESULT OnMouseAction(UINT msg, WPARAM , LPARAM lp, BOOL& handled)
	{
		if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN)
		{
			int xPos = GET_X_LPARAM(lp);
			int yPos = GET_Y_LPARAM(lp);
			POINT pt = {xPos, yPos};
			int item = this->HitTest(pt, NULL);
			if (item >= 0)
			{
				this->SelectItem(item);
			}
		}
		if (msg == WM_LBUTTONDBLCLK)
		{
			::PostMessage(m_edit, WM_COMMAND, Command_ApplySuggestion, 0);
		}

		handled = TRUE;
		return 0;
	}

	HWND m_edit;
};


class CSuggestionDlg
	: public CDialogImpl<CSuggestionDlg>
{
public:
	enum {IDD = IDD_SUGGESTION};

	BEGIN_MSG_MAP(CSuggestionDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_MOUSEACTIVATE, OnMouseActivate)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_NCACTIVATE, OnActivate)
		MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)
		MESSAGE_HANDLER(WM_ACTIVATEAPP, OnActivate)
		MESSAGE_HANDLER(WM_EXITSIZEMOVE, OnExitSizeMove)
		NOTIFY_HANDLER(IDC_LIST, NM_CUSTOMDRAW, OnNMCustomdrawList)
		NOTIFY_HANDLER(IDC_LIST, NM_DBLCLK, OnNMDblclkList)
	END_MSG_MAP()


	LRESULT OnMouseActivate(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled);
	LRESULT OnInitDialog(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled);
	LRESULT OnKeyDown(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled);
	LRESULT OnCreate(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled);
	LRESULT OnDestroy(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled);
	LRESULT OnActivate(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled);
	LRESULT OnSize(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled);
	LRESULT OnExitSizeMove(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled);
	LRESULT OnNMCustomdrawList(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
	LRESULT OnNMDblclkList(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);

public:
	void Resize();
	void ResizeList();
	void UpdateSuggestion(const std::vector<std::wstring>& ss);

	void MovePrev();
	void MoveNext();

	void SetEditWindow(HWND hwnd);
	std::wstring GetSelectedString();

private:
	CSuggestionListCtrl m_list;
};

__interface SuggestionProvider;

// 上，下
// 失去焦点时隐藏list

class CSuggestionEdit 
	: public CWindowImpl<CSuggestionEdit, CEdit>
	, public CMessageFilter
{
public:
	CSuggestionEdit();
	void SetSuggestionProvider(SuggestionProvider* provider);

	BEGIN_MSG_MAP(CSuggestionEdit)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_CHAR, OnChar)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_COMMAND, OnCommand)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		
	END_MSG_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
	void OnEditChange(UINT id, int code, HWND hwnd);
	LRESULT OnChar(UINT message, WPARAM wp, LPARAM lp, BOOL& handled);
	LRESULT OnCreate(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled);
	LRESULT OnDestroy(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled);
	LRESULT OnKeyDown(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled);
	LRESULT OnCommand(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled);
	LRESULT OnKillFocus(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled);

	void UpdateSuggestion(const std::vector<std::wstring>& ss);
	void Resize();
	void ResizeList();
	void HideList();
	void PostHideListMsg();

	CSuggestionDlg m_list;
	SuggestionProvider* m_provider;
};
