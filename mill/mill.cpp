#include "stdafx.h"
#include "mill.h"
#include "mainframe.h"

WTL::CAppModule _Module;

int Run(LPTSTR lpstrCmdLine = NULL, int nCmdShow = SW_SHOWDEFAULT);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

	::OleInitialize(NULL);
	::LoadLibrary(L"Riched20.dll");

	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(iccx);
	iccx.dwICC = ICC_COOL_CLASSES | ICC_BAR_CLASSES | ICC_USEREX_CLASSES;
	::InitCommonControlsEx(&iccx);

	HRESULT hRes = _Module.Init(NULL, hInstance);

	int nRet = Run(lpCmdLine, nCmdShow);

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


/** TODO

1. peoplemgr, medicinemgr
2. autocomplete·þÎñ
3. autocomplete list ctrl
4. UI
5. ´òÓ¡

*/