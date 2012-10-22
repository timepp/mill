#include "stdafx.h"
#include <excelformat/ExcelFormat.h>
#include "hlp.h"

void hlp::SafeAssign(std::wstring& str, const ExcelFormat::BasicExcelCell* cell)
{
	const wchar_t* s = cell->GetWString();
	if (s)
	{
		str = s;
		return;
	}

	const char* as = cell->GetString();
	if (as)
	{
		str.assign(as, as + strlen(as));
		return;
	}
}

void hlp::ShellExecuteAndWait(LPCWSTR path, LPCWSTR param, LPCWSTR dir)
{
	SHELLEXECUTEINFOW sei = {};
	sei.cbSize = sizeof(sei);
	sei.lpVerb = L"open";
	sei.lpFile = path;
	sei.lpParameters = param;
	sei.lpDirectory = dir;
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;
	sei.nShow = SW_SHOW;
	if (::ShellExecuteExW(&sei))
	{
		::WaitForSingleObject(sei.hProcess, INFINITE);
		::CloseHandle(sei.hProcess);
	}
	else
	{
		// throw
	}
}

bool hlp::ExcelLoad(ExcelFormat::BasicExcel& excel, const std::wstring& path)
{
	LOG_FUNCTION(path.c_str());

	bool ret = excel.Load(path.c_str());
	return ret;
}

bool hlp::ExcelSave(ExcelFormat::BasicExcel& excel)
{
	LOG_FUNCTION();

	bool ret = excel.Save();
	return ret;
}

bool hlp::ExcelSave(ExcelFormat::BasicExcel& excel, const std::wstring& path)
{
	LOG_FUNCTION(path.c_str());

	bool ret = excel.SaveAs(path.c_str());
	return ret;
}

bool hlp::FileExists(const std::wstring& path)
{
	DWORD attr = GetFileAttributesW(path.c_str());

	return (attr != INVALID_FILE_ATTRIBUTES) && (!(attr & FILE_ATTRIBUTE_DIRECTORY));
}

std::wstring hlp::GetDlgItemString(HWND hWnd, int cid)
{
	WCHAR text[1024];
	::GetDlgItemTextW(hWnd, cid, text, _countof(text));
	return text;
}

void hlp::SetDlgItemString(HWND hWnd, int cid, const std::wstring& str)
{
	::SetDlgItemTextW(hWnd, cid, str.c_str());
}
