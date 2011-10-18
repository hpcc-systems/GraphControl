#include "Platform.h"

#include "GraphBuffer.h"

#ifdef WIN32
#include <platform/win32/agg_win32_bmp.h>
#else
#include "x11_pixel_map.h"
#endif

#include <assert.h>

namespace ln
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
#else
		return m_pixelmap.stride();
#endif
	}

#ifdef WIN32
	void Draw(HDC h_dc, const RECT* device_rect=0, const RECT* bmp_rect=0) const
	{
		m_pixelmap.draw(h_dc, device_rect, bmp_rect);
	}
#else
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
