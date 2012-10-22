#pragma once

#include <string>
#include <excelformat/ExcelFormat.h>


struct hlp
{
	static void SafeAssign(std::wstring& str, const ExcelFormat::BasicExcelCell* cell);
	static void ShellExecuteAndWait(LPCWSTR path, LPCWSTR param, LPCWSTR dir);

	static bool ExcelLoad(ExcelFormat::BasicExcel& excel, const std::wstring& path);
	static bool ExcelSave(ExcelFormat::BasicExcel& excel);
	static bool ExcelSave(ExcelFormat::BasicExcel& excel, const std::wstring& path);

	static bool FileExists(const std::wstring& path);

	// windows control
	static std::wstring GetDlgItemString(HWND hWnd, int cid);
	static void SetDlgItemString(HWND hWnd, int cid, const std::wstring& str);
};
