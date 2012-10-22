#include "stdafx.h"
#include "pathmgr.h"

PathMgr::PathMgr()
{
	WCHAR path[MAX_PATH];
	::GetModuleFileNameW(NULL, path, _countof(path));
	m_exepath = path;
	std::wstring::size_type pos = m_exepath.find_last_of(L"/\\");
	if (pos > 1 && pos < m_exepath.length())
	{
		m_exedir = m_exepath.substr(0, pos);
	}
	else
	{
		m_exedir = L".";
	}
}

std::wstring PathMgr::GetExePath() const
{
	return m_exepath;
}

std::wstring PathMgr::GetExeDir() const
{
	return m_exedir;
}

std::wstring PathMgr::GetDataDir() const
{
	return m_exedir + L"\\data";
}

std::wstring PathMgr::GetLogDir() const
{
	return m_exedir + L"\\log";
}
