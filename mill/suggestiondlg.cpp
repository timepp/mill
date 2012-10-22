#include "stdafx.h"
#include "suggestiondlg.h"
#include "mill.h"
#include <tplib/include/msg_crack.h>

extern CAppModule _Module;

// 根据列表里的内容调整大小
void CSuggestionDlg::Resize()
{
	RECT rc;
	m_list.GetItemRect(0, &rc, LVIR_BOUNDS);
	int height = m_list.GetItemCount() * (rc.bottom - rc.top + 1);
	if (height > 150) height = 150;

	m_list.GetClientRect(&rc);
	m_list.ResizeClient(rc.right - rc.left, height);
	m_list.GetWindowRect(&rc);
	height = rc.bottom - rc.top;

	GetClientRect(&rc);
	ResizeClient(rc.right - rc.left, height);
	ResizeList();
//	::SetFocus(m_pair);
}

void CSuggestionDlg::ResizeList()
{
	if (m_list.IsWindow())
	{
		RECT rc;
		GetClientRect(&rc);
		m_list.MoveWindow(&rc);
		m_list.GetClientRect(&rc);
		m_list.SetColumnWidth(0, rc.right - rc.left);
	}
}

void CSuggestionDlg::MoveNext()
{
	int count = m_list.GetItemCount();
	if (count == 0) return;

	int index = m_list.GetSelectedIndex();
	index = (index + 1) % count;
	m_list.SelectItem(index);
}

void CSuggestionDlg::MovePrev()
{
	int count = m_list.GetItemCount();
	if (count == 0) return;

	int index = m_list.GetSelectedIndex();
	index = (index + count - 1) % count;
	m_list.SelectItem(index);
}

std::wstring CSuggestionDlg::GetSelectedString()
{
	int index = m_list.GetSelectedIndex();
	if (index >= 0)
	{
		WCHAR text[1024];
		m_list.GetItemText(index, 0, text, _countof(text));
		return text;
	}
	return L"";
}

LRESULT CSuggestionDlg::OnSize(UINT , WPARAM , LPARAM , BOOL &)
{
	ResizeList();
	return TRUE;
}

LRESULT CSuggestionDlg::OnExitSizeMove(UINT , WPARAM , LPARAM , BOOL &handled)
{
	handled = TRUE;
//	::SetFocus(m_pair);
	return TRUE;
}

LRESULT CSuggestionDlg::OnMouseActivate(UINT , WPARAM , LPARAM , BOOL &)
{
	return MA_NOACTIVATE;
}

LRESULT CSuggestionDlg::OnInitDialog(UINT , WPARAM , LPARAM , BOOL &)
{
//	_Module.GetMessageLoop()->AddMessageFilter(this);
	//m_list = GetDlgItem(IDC_LIST);
	m_list.SubclassWindow(GetDlgItem(IDC_LIST));
	m_list.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_BORDERSELECT);
	m_list.AddColumn(L"", 0);
	m_list.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

//	m_il.Create(16, 16, ILC_COLOR32 | ILC_MASK, 4, 4);
//	m_il.SetBkColor(CLR_NONE);
//	HBITMAP bmp = AtlLoadBitmap(IDB_UD);
//	m_il.Add(bmp); DeleteObject(bmp);

	return FALSE;
}

LRESULT CSuggestionDlg::OnActivate(UINT , WPARAM , LPARAM , BOOL& handled)
{
	handled = TRUE;
	return TRUE;
}

LRESULT CSuggestionDlg::OnCreate(UINT , WPARAM , LPARAM , BOOL &)
{
	return TRUE;
}

LRESULT CSuggestionDlg::OnDestroy(UINT , WPARAM , LPARAM , BOOL &)
{
//	_Module.GetMessageLoop()->RemoveMessageFilter(this);
	return 0;
}

LRESULT CSuggestionDlg::OnNMCustomdrawList(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
	LPNMLVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (pNMCD->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		return CDRF_NOTIFYITEMDRAW;
	}
	if (pNMCD->nmcd.dwDrawStage == CDDS_ITEMPREPAINT &&
		pNMCD->nmcd.dwItemSpec == (DWORD_PTR)m_list.GetSelectedIndex())
	{
		pNMCD->clrText   = GetSysColor(COLOR_HIGHLIGHTTEXT);
		pNMCD->clrTextBk = GetSysColor(COLOR_HIGHLIGHT);
	}
	return 0;
}

LRESULT CSuggestionDlg::OnNMDblclkList(int /*idCtrl*/, LPNMHDR , BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	GetParent().SendMessageW(WM_COMMAND, IDOK);
	return 0;
}

void CSuggestionDlg::UpdateSuggestion(const std::vector<std::wstring>& ss)
{
	m_list.SetRedraw(FALSE);

	m_list.DeleteAllItems();
	for (size_t i = 0; i < ss.size(); i++)
	{
		m_list.AddItem((int)i, 0, ss[i].c_str(), 0);
	}

	if (m_list.GetItemCount() > 0)
	{
		m_list.SelectItem(0);
	}

	m_list.SetRedraw(TRUE);

	Resize();
}

void CSuggestionDlg::SetEditWindow(HWND hwnd)
{
	m_list.SetEditWindow(hwnd);
}



CSuggestionEdit::CSuggestionEdit()
{
}

void CSuggestionEdit::OnEditChange(UINT id, int code, HWND hwnd)
{
	
}

LRESULT CSuggestionEdit::OnChar(UINT message, WPARAM wp, LPARAM lp, BOOL& handled)
{
	LRESULT ret = DefWindowProc(message, wp, lp);

	if (wp != VK_TAB)
	{
		wchar_t text[1024];
		GetWindowTextW(text, _countof(text));
		UpdateSuggestion(m_provider->GetSuggestion(text));
	}

	handled = TRUE;
	return ret;
}

void CSuggestionEdit::UpdateSuggestion(const std::vector<std::wstring>& ss)
{
	if (ss.size() == 0)
	{
		if (m_list.IsWindow())
		{
			m_list.ShowWindow(SW_HIDE);
		}
	}
	else
	{
		if (!m_list.IsWindow())
		{
			m_list.Create(GetParent());
			m_list.SetEditWindow(m_hWnd);
		}
		m_list.UpdateSuggestion(ss);

		RECT rc;
		GetWindowRect(&rc);
		m_list.SetWindowPos(NULL, rc.left, rc.bottom + 1, 0, 0, SWP_NOSIZE|SWP_SHOWWINDOW|SWP_NOACTIVATE);
	}
}

// 根据列表里的内容调整大小
void CSuggestionEdit::Resize()
{
	m_list.Resize();
}

void CSuggestionEdit::ResizeList()
{
	m_list.ResizeList();
}

void CSuggestionEdit::SetSuggestionProvider(SuggestionProvider* provider)
{
	m_provider = provider;
}

LRESULT CSuggestionEdit::OnCreate(UINT , WPARAM , LPARAM , BOOL &)
{
	_Module.GetMessageLoop()->AddMessageFilter(this);
	return TRUE;
}

LRESULT CSuggestionEdit::OnDestroy(UINT , WPARAM , LPARAM , BOOL &)
{
	_Module.GetMessageLoop()->RemoveMessageFilter(this);
	return 0;
}

BOOL CSuggestionEdit::PreTranslateMessage(MSG *pMsg)
{
	return FALSE;
}

LRESULT CSuggestionEdit::OnKeyDown(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled)
{
	switch (wp)
	{
	case VK_ESCAPE:
		PostMessage(WM_COMMAND, Command_HideList);
		break;
	case VK_UP:
		m_list.MovePrev();
		break;
	case VK_DOWN:
	case VK_TAB:
		m_list.MoveNext();
		break;
	case VK_RETURN:
		SendMessage(WM_COMMAND, Command_ApplySuggestion);
		break;
	default:
		handled = FALSE;
		break;
	}
	return TRUE;
}

LRESULT CSuggestionEdit::OnCommand(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled)
{
	switch (wp)
	{
	case Command_HideList:
		HideList();
		break;
	case Command_ApplySuggestion:
		{
		std::wstring text = m_list.GetSelectedString();
		SetWindowText(text.c_str());
		SetSel(0, -1);
		PostHideListMsg();
		}
		break;
	default:
		handled = FALSE;
		break;
	}

	return TRUE;
}
LRESULT CSuggestionEdit::OnKillFocus(UINT msg, WPARAM wp, LPARAM lp, BOOL& handled)
{
	PostMessage(WM_COMMAND, Command_HideList);
	handled = FALSE;
	return TRUE;
}

void CSuggestionEdit::HideList()
{
	if (m_list.IsWindow() && m_list.IsWindowVisible())
	{
		m_list.ShowWindow(SW_HIDE);
	}
}

void CSuggestionEdit::PostHideListMsg()
{
	PostMessage(WM_COMMAND, Command_HideList);
}