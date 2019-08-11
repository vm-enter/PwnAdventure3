#include "stdafx.h"

#include "log.hpp"

VOID DbgLog(__in_z __format_string LPCSTR lpcwszFormat, ...)
{
	CHAR  szBuffer[MAX_PATH * 4];
	ULONG uLength;
	PCHAR pszList;

	va_start(pszList, lpcwszFormat);
	uLength = wvsprintfA(szBuffer, lpcwszFormat, pszList);

	printf("%s\n", szBuffer);
}