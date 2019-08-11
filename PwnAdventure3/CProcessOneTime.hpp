#pragma once

class CProcessOneTime
{
public:
	CProcessOneTime(DWORD tTimeout);
	~CProcessOneTime();

public:
	BOOL Try();

private:
	DWORD m_tStartTime;
	DWORD m_tTimeout;
};