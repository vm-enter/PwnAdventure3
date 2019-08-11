#include "stdafx.h"

#include "CMainWindow.hpp"
#include "CAutoHack.hpp"
#include "CMsgHandler.hpp"
#include "extvars.hpp"
#include "utils.hpp"
#include "log.hpp"

#include <time.h>

BOOL Detour__RegisterClassW()
{
	static decltype(&RegisterClassW) _RegisterClassW = RegisterClassW;

	decltype(&RegisterClassW) RegisterClassW__Hook = [](
		_In_ CONST WNDCLASSW *lpWndClass) -> ATOM
	{
		if (lpWndClass->lpszClassName != NULL && wcsstr(
			lpWndClass->lpszClassName, L"UnrealWindow") != 0)
		{
			if (CMsgHandler::GetInstance()->GetHandle() == NULL)
			{
				CMsgHandler::GetInstance()->Init(g_hInstance);
				CAutoHack::GetInstance()->Init();

				g_GameLogicDLL = GetModuleHandle(L"GameLogic.dll");
				if (g_GameLogicDLL == NULL)
				{
					g_GameLogicDLL = LoadLibrary(L"GameLogic.dll");					
				}
			}
		}

		return _RegisterClassW(lpWndClass);
	};

	return DetourFunction(TRUE, reinterpret_cast<LPVOID*>(&_RegisterClassW), RegisterClassW__Hook);
}

BOOL WINAPI Initialize(__in HINSTANCE hInstance)
{
	DisableThreadLibraryCalls(hInstance);

	srand(time(nullptr));
	srand(rand());

	Detour__RegisterClassW();

	Q_INIT_RESOURCE(PwnAdventure3);

	QCoreApplication::setOrganizationName("Japanese1337hackers");
	QCoreApplication::setOrganizationDomain("jpn.hackers.com");
	QCoreApplication::setApplicationName("PwnNewbie 3");

	int args = 0;
	QApplication app(args, NULL);

	CMainWindow *mainWindow = CMainWindow::getInstance();
	mainWindow->setupApp(&app);
	mainWindow->show();
	app.exec();

	FreeLibraryAndExitThread(hInstance, 0);

	return TRUE;
}

BOOL APIENTRY DllMain(__in HINSTANCE hInstance, __in DWORD fdwReason, __in __reserved LPVOID lpvReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
		#ifdef _LOGGING
			AllocConsole();
			freopen("CONOUT$", "w", stdout);
		#endif

			g_hInstance = hInstance;

			HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Initialize, (LPVOID)hInstance, 0, NULL);
			if (hThread != NULL)
			{
				CloseHandle(hThread);
				break;
			}
			else
				return FALSE;
		}
		case DLL_PROCESS_DETACH:
		{
			FreeLibrary(hInstance);
			break;
		}
	}
	return TRUE;
}
