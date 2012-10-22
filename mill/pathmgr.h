#pragma once

#include "serviceid.h"
#include <tplib/include/service.h>


class PathMgr : public tp::service_impl<SID_PathMgr>
{
public:
	std::wstring GetExeDir() const;
	std::wstring GetExePath() const;
	std::wstring GetDataDir() const;
	std::wstring GetLogDir() const;

	PathMgr();

private:
	std::wstring m_exedir;
	std::wstring m_exepath;
};

DEFINE_SERVICE(PathMgr, L"Â·¾¶¹ÜÀíÆ÷");
