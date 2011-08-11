#pragma once

#include <agg_math_stroke.h>
#include <agg2d.h>

#ifdef XP_WIN
#include <platform\win32\agg_win32_bmp.h>

#include <atlbase.h>
#include <atlapp.h>
#include <atlgdi.h>
#include <atltypes.h>
#include <atlscrl.h>
#endif

#ifdef XP_WIN
enum UM_APP
{
	UM_UNKNOWN = WM_APP,
	UM_RECENTER,
	UM_LAST
};

class CAgg2D : public Agg2D
{
protected:

public:
	CAgg2D()
	{
	}

    template<class Ctrl>
	void render_ctrl(Ctrl& c)
    {
		agg::render_ctrl(m_rasterizer, m_scanline, m_renBase, c);
   }
};

class CAggGDI : public CAgg2D, public CDCHandle
{
public:
	CAggGDI(HDC dc) : CDCHandle(dc)
	{
	}
};

class CAggCanvas : public CDC//, public CAgg2D, public CDC
{
protected:
	int m_bpp;
	agg::rendering_buffer m_rbuf_window;
	agg::pixel_map m_pmap_window;
	//CComPtr<CAgg2D> m_graphics;

	CDCHandle m_hDCOriginal;
	CBitmap m_bmp;
	HBITMAP m_hBmpOld;

	CRect m_rcPaint;
	CPoint m_ptOffset;
	double m_scale;

public:
	CAggCanvas(HDC dc, const CRect & rcPaint, const CPoint ptOffset, double scale) : m_hDCOriginal(dc), m_rcPaint(rcPaint), m_ptOffset(ptOffset), m_scale(scale), m_bpp(32)
	{
		CreateCompatibleDC(m_hDCOriginal);
		ATLASSERT(m_hDC != NULL);

		//m_bmp.CreateCompatibleBitmap(m_hDCOriginal, m_rcPaint.right - m_rcPaint.left, m_rcPaint.bottom - m_rcPaint.top);
		m_bmp = m_pmap_window.create_dib_section(m_hDC, m_rcPaint.Width(), m_rcPaint.Height(), agg::org_e(m_bpp));
		m_rbuf_window.attach(m_pmap_window.buf(), m_pmap_window.width(), m_pmap_window.height(), -m_pmap_window.stride());

		ATLASSERT(m_bmp.m_hBitmap != NULL);
		m_hBmpOld = SelectBitmap(m_bmp);

		//attach(m_rbuf_window.buf(), m_rbuf_window.width(), m_rbuf_window.height(), m_rbuf_window.stride());
		//antiAliasGamma(1.4);
		//flipText(true);

		////  Set transform for GDI
		//SetMapMode(MM_ANISOTROPIC);
		//SetWindowExt(rcPaint.Size());
		//SetViewportExt(rcPaint.Width() * m_scale, rcPaint.Height() * m_scale);
		//SetViewportOrg(-m_ptOffset.x - m_rcPaint.left, -m_ptOffset.y - m_rcPaint.top);

		////  Set transform for AGG
		//CAgg2D::scale(m_scale, m_scale);
		//viewport(m_ptOffset.x /*+ m_rcPaint.left*/, m_ptOffset.y /*+ m_rcPaint.top*/, m_ptOffset.x + m_rcPaint.Width(), m_ptOffset.y + m_rcPaint.Height(),
		// 		m_rcPaint.left, m_rcPaint.top, m_rcPaint.right, m_rcPaint.bottom, Agg2D::XMidYMid);

		//clipBox(m_rcPaint.left, m_rcPaint.top, m_rcPaint.right, m_rcPaint.bottom);
	}

	~CAggCanvas()
	{
		m_pmap_window.draw(m_hDCOriginal);
		SelectBitmap(m_hBmpOld);
		m_bmp.Detach();
	}

	CAggGDI * CreateCAggGDI(const CRect & rcPaint, const CPoint & ptOffset)
	{
		CAggGDI * retVal = new CAggGDI(m_hDC);
		retVal->attach(m_rbuf_window.buf(), m_rbuf_window.width(), m_rbuf_window.height(), m_rbuf_window.stride());
		retVal->antiAliasGamma(1.4);
		retVal->flipText(true);

		//  Set transform for GDI
		retVal->SetMapMode(MM_ANISOTROPIC);
		retVal->SetWindowExt(rcPaint.Size());
		retVal->SetViewportExt(rcPaint.Width() * m_scale, rcPaint.Height() * m_scale);
		retVal->SetViewportOrg(-m_ptOffset.x - m_rcPaint.left, -m_ptOffset.y - m_rcPaint.top);

		//  Set transform for AGG
		retVal->scale(m_scale, m_scale);
		retVal->viewport(m_ptOffset.x /*+ m_rcPaint.left*/, m_ptOffset.y /*+ m_rcPaint.top*/, m_ptOffset.x + m_rcPaint.Width(), m_ptOffset.y + m_rcPaint.Height(),
		 			m_rcPaint.left, m_rcPaint.top, m_rcPaint.right, m_rcPaint.bottom, Agg2D::XMidYMid);

		retVal->clipBox(m_rcPaint.left, m_rcPaint.top, m_rcPaint.right, m_rcPaint.bottom);
		return retVal;
	}
};
#endif
