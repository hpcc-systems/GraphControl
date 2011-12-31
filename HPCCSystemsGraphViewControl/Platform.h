/*******************************************************************************
 * Copyright (C) 2011 HPCC Systems.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/
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
namespace std
{
#ifdef _UNICODE
	#define	_tstring wstring
#else
	#define	_tstring string
#endif
}

#if defined(_DEBUGXXX)
# include <stdlib.h>
# include <crtdbg.h>
# define GJS_DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
# define new GJS_DEBUG_NEW
#endif



