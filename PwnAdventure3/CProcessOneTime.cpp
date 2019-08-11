#include "stdafx.h"

#include "CProcessOneTime.hpp"

#pragma comment(lib, "winmm.lib")

CProcessOneTime::CProcessOneTime(DWORD tTimeout)
{
	this->m_tStartTime = timeGetTime();
	this->m_tTimeout = tTimeout;
}

CProcessOneTime::~CProcessOneTime()
{
}

BOOL CProcessOneTime::Try()
{
	if (timeGetTime() > this->m_tStartTime + this->m_tTimeout)
	{
		this->m_tStartTime = timeGetTime();
		return TRUE;
	}

	return FALSE;
}