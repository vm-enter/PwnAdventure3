#pragma once

#include <map>

class CMemoryManager
{
public:
	CMemoryManager();
	~CMemoryManager();

	static CMemoryManager *GetInstance()
	{
		static CMemoryManager instance;
		return &instance;
	}

public:
	BOOL WriteMemory(__in BOOL fStatus, __in LPVOID lpvTarget, __in LPCVOID lpcvData, __in INT iSize);
	BOOL WriteFunction(__in BOOL fStatus, __in LPVOID* lppvFunction, __in LPVOID lpvRedirection, __in INT iSize);

private:
	void BackupMemory(__in LPVOID lpvTarget, __in INT iSize);
	void RestoreMemory(__in LPVOID lpvTarget);

private:
	std::map<LPVOID, LPVOID> m_mpMemory;
	std::map<LPVOID, INT> m_mpMemSize;
};

BOOL WINAPI WriteMemory(__in BOOL fStatus, __in LPVOID lpvTarget, __in LPCVOID lpcvData, __in INT iSize);
BOOL WINAPI WriteMemory(__in BOOL fStatus, __in DWORD dwTarget, __in LPCVOID lpcvData, __in INT iSize);
BOOL WINAPI WriteFunction(__in BOOL fStatus, __in LPVOID* lppvFunction, __in LPVOID lpvRedirection, __in INT iSize);