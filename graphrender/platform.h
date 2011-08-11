#pragma once

#pragma warning(disable:4251)
//#pragma warning(disable:4275)
#pragma warning(disable:4503)
//#pragma warning(disable:4127)

//  Leak Checking ---
#if defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#endif

#ifdef WIN32
#include "targetver.h"
#endif

#include <stdio.h>
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#include <tchar.h>
#else
#define TCHAR wchar_t
#define _T(x) L ## x
#include <inttypes.h>
#include <string.h>
#endif

#include <string>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <iostream>
#include <sstream>
namespace std
{
#ifdef _UNICODE
	#define	_tstring wstring
	#define	_tstringstream wstringstream
#else
	#define	_tstring string
	#define	_tstringstream stringstream
#endif
}

#if defined(_DEBUGXXX)
# include <stdlib.h>
# include <crtdbg.h>
# define GJS_DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
# define new GJS_DEBUG_NEW
#endif



