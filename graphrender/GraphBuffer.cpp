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
#include "precompiled_headers.h"

#include "GraphBuffer.h"

#ifdef WIN32
#include <platform/win32/agg_win32_bmp.h>
#elif FB_MACOSX
#include "x11_pixel_map.h"
#elif FB_X11
#include "x11_pixel_map.h"
#endif

namespace hpcc
{
class CGraphBuffer : public IGraphBuffer, public CUnknown
{
protected:
	agg::pixel_map m_pixelmap;

public:
	BEGIN_CUNKNOWN
	END_CUNKNOWN

	CGraphBuffer()
	{
	}

	virtual void Resize(unsigned int Width, unsigned int Height)
	{
		if (!m_pixelmap.buf() || m_pixelmap.width() != Width || m_pixelmap.height() != Height)
		{
			m_pixelmap.create(Width, Height, agg::org_color32);
		}
	}

	unsigned int Width() const
	{
		return m_pixelmap.width();
	}

	unsigned int Height() const
	{
		return m_pixelmap.height();
	}

    unsigned char* GetBuffer()
	{
		return m_pixelmap.buf();
	}

	virtual int Stride() const
	{
#if defined WIN32
		return -m_pixelmap.stride();
#elif FB_MACOSX
		return m_pixelmap.stride();
#elif FB_X11
		return m_pixelmap.stride();
#endif
	}

#ifdef WIN32
	void Draw(HDC h_dc, const RECT* device_rect=0, const RECT* bmp_rect=0) const
	{
		m_pixelmap.draw(h_dc, device_rect, bmp_rect);
	}
#elif FB_MACOSX
    void Draw(GtkWidget * widget, int dest_x, int dest_y) const
    {
        m_pixelmap.draw(widget, dest_x, dest_y);
    }
#elif FB_X11
    void Draw(GtkWidget * widget, int dest_x, int dest_y) const
    {
        m_pixelmap.draw(widget, dest_x, dest_y);
    }
#endif
};

GRAPHRENDER_API IGraphBuffer * CreateGraphBuffer(int width, int height)
{
	return new CGraphBuffer();
}
}
