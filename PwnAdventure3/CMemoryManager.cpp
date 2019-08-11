#include "stdafx.h"

#include "CMemoryManager.hpp"
#include "utils.hpp"

CMemoryManager::CMemoryManager()
{
}

CMemoryManager::~CMemoryManager()
{
	for (auto it = this->m_mpMemory.begin(); it != this->m_mpMemory.end(); it++)
		free(it->second);
}

BOOL CMemoryManager::WriteMemory(__in BOOL fStatus, __in LPVOID lpvTarget, __in LPCVOID lpcvData, __in INT iSize)
{
	if (fStatus)
	{
		this->BackupMemory(lpvTarget, iSize);
	}
	else
	{
		this->RestoreMemory(lpvTarget);
		return TRUE;
	}

	MEMORY_BASIC_INFORMATION mbi;

	if (VirtualQuery(lpvTarget, &mbi, sizeof(MEMORY_BASIC_INFORMATION)) != sizeof(MEMORY_BASIC_INFORMATION))
		return FALSE;

	if (!mbi.Protect || (mbi.Protect & PAGE_GUARD))
		return FALSE;

	if (iSize == 0)
		iSize = m_mpMemSize[lpvTarget];

	if (mbi.Protect & PAGE_EXECUTE_READWRITE)
	{
		memcpy(lpvTarget, lpcvData, iSize);

		return TRUE;
	}
	else
	{
		DWORD flOldProtect;

		if (!VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &flOldProtect))
			return FALSE;

		memcpy(lpvTarget, lpcvData, iSize);

		return VirtualProtect(mbi.BaseAddress, mbi.RegionSize, flOldProtect, &flOldProtect);
	}

}

BOOL CMemoryManager::WriteFunction(BOOL fStatus, LPVOID *lppvFunction, LPVOID lpvRedirection, INT iSize)
{
	if (fStatus)
	{
		this->BackupMemory(*lppvFunction, iSize);
	}
	else
	{
		this->RestoreMemory(*lppvFunction);
		return TRUE;
	}

	return DetourFunction(fStatus, lppvFunction, lpvRedirection);
}

void CMemoryManager::BackupMemory(__in LPVOID lpvTarget, __in INT iSize)
{
	PBYTE pbData;

	if (this->m_mpMemory[lpvTarget] == NULL)
	{
		pbData = (BYTE *)malloc(iSize);
		memcpy(pbData, lpvTarget, iSize);

		this->m_mpMemSize[lpvTarget] = iSize;
		this->m_mpMemory[lpvTarget] = pbData;
	}
}

void CMemoryManager::RestoreMemory(__in LPVOID lpvTarget)
{
	if (this->m_mpMemory[lpvTarget] != NULL &&
		this->m_mpMemSize[lpvTarget] != NULL)
	{
		memcpy(lpvTarget, this->m_mpMemory[lpvTarget], this->m_mpMemSize[lpvTarget]);
	}
}

BOOL WINAPI WriteMemory(__in BOOL fStatus, __in LPVOID lpvTarget, __in LPCVOID lpcvData, __in INT iSize)
{
	return CMemoryManager::GetInstance()->WriteMemory(fStatus, lpvTarget, lpcvData, iSize);
}

BOOL WINAPI WriteMemory(__in BOOL fStatus, __in DWORD dwTarget, __in LPCVOID lpcvData, __in INT iSize)
{
	return CMemoryManager::GetInstance()->WriteMemory(fStatus, (LPVOID)dwTarget, lpcvData, iSize);
}

BOOL WINAPI WriteFunction(__in BOOL fStatus, __in  LPVOID *lppvFunction, __in LPVOID lpvRedirection, __in INT iSize)
{
	return CMemoryManager::GetInstance()->WriteFunction(fStatus, lppvFunction, lpvRedirection, iSize);
}
