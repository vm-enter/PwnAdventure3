#pragma once

#include "CMsgHandlerRequest.hpp"

#define CLASS_NAME "MsgHandler"

class CMsgHandler
{
public:
	CMsgHandler();
	~CMsgHandler();

	static CMsgHandler* GetInstance()
	{
		static CMsgHandler instance;
		return &instance;
	}

public:
	BOOL Init(__in HINSTANCE hInstance);

	HWND GetHandle();
	BOOL SendMsg(__in UINT uMsg, WPARAM wParam = NULL, LPARAM lParam = NULL);
	BOOL PostMsg(__in UINT uMsg, WPARAM wParam = NULL, LPARAM lParam = NULL);


private:
	VOID Destroy();

private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};