#pragma once

#include <Unknown.h>

#ifdef WIN32
#  ifdef STATIC_LIB
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
#include <Platform.h>
#else
#include <X11/Xlib.h>
#include <gtk/gtk.h>
#endif

namespace ln
{
interface GRAPHRENDER_API IGraphBuffer : public IUnknown
{
	virtual void Resize(unsigned int width, unsigned int Height) = 0;
	virtual unsigned int Width() const = 0;
	virtual unsigned int Height() const = 0;
	virtual int Stride() const = 0;
    virtual unsigned char* GetBuffer() = 0;

#ifdef WIN32
	virtual void Draw(HDC h_dc, const RECT* device_rect=0, const RECT* bmp_rect=0) const = 0;
#else
    virtual void Draw(GtkWidget * widget, int dest_x, int dest_y) const = 0;
#endif

};
typedef CUnknownPtr<IGraphBuffer> IGraphBufferPtr;

GRAPHRENDER_API IGraphBuffer * CreateGraphBuffer(int width, int height);
}
