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

#include <Unknown.h>

#ifdef WIN32
#  ifdef GRAPHRENDER_STATIC
#    define GRAPHRENDER_API
#  elif defined GRAPHRENDER_EXPORTS
#    define GRAPHRENDER_API __declspec(dllexport)
#  else
#    define GRAPHRENDER_API __declspec(dllimport)
#  endif
#else
#	if __GNUC__ >= 4
#		define GRAPHRENDER_API __attribute__ ((visibility("default")))
#	else
#		define GRAPHRENDER_API
#	endif
#endif

#ifdef WIN32
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#elif FB_MACOSX
#include <Carbon/Carbon.h>
#elif FB_X11
#include <X11/Xlib.h>
#include <gtk/gtk.h>
#endif

namespace hpcc
{
hpcc_interface GRAPHRENDER_API IGraphBuffer : public IUnknown
{
	virtual void Resize(unsigned int width, unsigned int Height) = 0;
	virtual unsigned int Width() const = 0;
	virtual unsigned int Height() const = 0;
	virtual int Stride() const = 0;
    virtual unsigned char* GetBuffer() = 0;

#ifdef WIN32
    virtual void Draw(HWND hwnd, int dest_x, int dest_y) const = 0;
#elif FB_MACOSX
    virtual void Draw(CGContextRef context, int dest_x, int dest_y) const = 0;
#elif FB_X11
    virtual void Draw(GtkWidget * widget, int dest_x, int dest_y) const = 0;
#endif

};
typedef CUnknownPtr<IGraphBuffer> IGraphBufferPtr;

GRAPHRENDER_API IGraphBuffer * CreateGraphBuffer(int width, int height);
}
