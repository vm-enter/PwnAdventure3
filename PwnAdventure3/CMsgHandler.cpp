#include "stdafx.h"

#include "CMsgHandler.hpp"
#include "headers.hpp"
#include "log.hpp"

CMsgHandler::CMsgHandler()
{
	m_hWnd = NULL;
	m_hInstance = NULL;
}

CMsgHandler::~CMsgHandler()
{
}

BOOL CMsgHandler::Init(__in HINSTANCE hInstance)
{
	WNDCLASSEX wc = { 0 };

	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = CMsgHandler::WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT(CLASS_NAME);

	if (!RegisterClassEx(&wc))
	{
		return FALSE;
	}

	this->m_hWnd = CreateWindowEx(0, TEXT(CLASS_NAME), NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, hInstance, NULL);
	if (!this->m_hWnd)
	{
		UnregisterClass(TEXT(CLASS_NAME), NULL);
		return FALSE;
	}

	this->m_hInstance = hInstance;

	// invisible window
	ShowWindow(this->m_hWnd, SW_HIDE);

	return TRUE;
}

VOID CMsgHandler::Destroy()
{
	if (this->m_hWnd != NULL)
	{
		DestroyWindow(this->m_hWnd);
		this->m_hWnd = NULL;
	}

	UnregisterClass(TEXT(CLASS_NAME), this->m_hInstance);
}

HWND CMsgHandler::GetHandle()
{
	return this->m_hWnd;
}

BOOL CMsgHandler::SendMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return SendMessageA(this->m_hWnd, uMsg, wParam, lParam);
}

BOOL CMsgHandler::PostMsg(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return PostMessageA(this->m_hWnd, uMsg, wParam, lParam);
}

LRESULT CMsgHandler::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Player *pLocalPlayer;
	World *pWorld;

	switch (uMsg)
	{
		case WM_CLOSE:
		{
			CMsgHandler::GetInstance()->Destroy();
			break;
		}
		case WM_GET_USER_POS:
		{
			ActorRef<IPlayer> pPlayer;

			pWorld = World::GetInstance();
			if (pWorld != NULL)
			{
				pPlayer = (*pWorld->m_players.begin());
				if (pPlayer != NULL)
				{
					pLocalPlayer = (Player *)pPlayer->vfptr->GetActorInterface(pPlayer);
					if (pLocalPlayer != NULL)
					{						
						pLocalPlayer->Actor.GetPosition((Vector3 *)lParam);
						return TRUE;
					}
				}
			}
			
			return FALSE;
		}
		case WM_TELEPORT:
		{
			ActorRef<IPlayer> pPlayer;

			pWorld = World::GetInstance();
			if (pWorld != NULL)
			{
				pPlayer = (*pWorld->m_players.begin());
				if (pPlayer != NULL)
				{
					pLocalPlayer = (Player *)pPlayer->vfptr->GetActorInterface(pPlayer);
					if (pLocalPlayer != NULL)
					{
						pLocalPlayer->Teleport((Vector3 *)wParam);
						return TRUE;
					}
				}
			}

			return FALSE;
		}
		case WM_GET_FIRE_BALL:
		{
			DEBUGLOG("Recv request => WM_GET_FIRE_BALL");

			ActorRef<IPlayer> pPlayer;

			pWorld = World::GetInstance();
			if (pWorld != NULL)
			{
				pPlayer = (*pWorld->m_players.begin());
				if (pPlayer != NULL)
				{
					pLocalPlayer = (Player *)pPlayer->vfptr->GetActorInterface(pPlayer);
					if (pLocalPlayer != NULL)
					{
						if (pLocalPlayer->IPlayer.vfptr->AddItem(&pLocalPlayer->IPlayer, GameAPI::GetInstance()->GetItemByName("GreatBallsOfFire"), 1, false))
						{
							MessageBox(0, 0, 0, 0);
							return TRUE;
						}
					}
				}
			}
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return TRUE;
}