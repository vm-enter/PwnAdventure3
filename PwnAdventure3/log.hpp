#pragma once

#define _LOGGING

#ifdef _LOGGING
#define DEBUGLOG DbgLog
#else
#define DEBUGLOG(msg)
#endif

VOID DbgLog(__in_z __format_string LPCSTR lpcwszFormat, ...);