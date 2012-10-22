#include "stdafx.h"
#include "mill.h"
#include "mainframe.h"
#include "pathmgr.h"
#include <bdlog/include/bdlog_impl.h>


WTL::CAppModule _Module;

static void InitLog();
static int Run(LPTSTR lpstrCmdLine = NULL, int nCmdShow = SW_SHOWDEFAULT);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	InitLog();

	::OleInitialize(NULL);
	::LoadLibrary(L"Riched20.dll");

	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(iccx);
	iccx.dwICC = ICC_COOL_CLASSES | ICC_BAR_CLASSES | ICC_USEREX_CLASSES;
	::InitCommonControlsEx(&iccx);

	HRESULT hRes = _Module.Init(NULL, hInstance);

	try
	{
		Run(lpCmdLine, nCmdShow);
	}
	catch (...)
	{
		MessageBoxW(NULL, L"未知异常", L"错误", MB_OK|MB_ICONWARNING);
	}

	_Module.Term();

	::OleUninitialize();

	tp::servicemgr::instance().destroy_all_services();
 	return 0;
}

int Run(LPTSTR lpstrCmdLine, int nCmdShow)
{
	CMessageLoop theLoop;

	_Module.AddMessageLoop(&theLoop);

	CMainFrame g_mainframe;
	if(g_mainframe.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	g_mainframe.ShowWindow(nCmdShow);


	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

void InitLog()
{
	PathMgr* pm = tp::servicemgr::get<PathMgr>();
	std::wstring dir = pm->GetLogDir();

	ILogController* ctrl = GetLogController();
	ctrl->Init(NULL);
	ctrl->AddOutputDevice(L"pipe", LODT_PIPE, L"enable:true");
	ctrl->AddOutputDevice(L"file", LODT_FILE, tp::cz(L"enable:true path:'%s\\mill_${T}.bdlog'", dir.c_str()));

	Log(LL_EVENT, TAG_DEFAULT, L"日志系统初始化完毕");
}


/** TODO

1. peoplemgr, medicinemgr
2. autocomplete服务
3. autocomplete list ctrl
4. UI
5. 打印

*/