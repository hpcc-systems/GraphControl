#pragma once

#include "DotViewCommon.h"

//#include "HPCCSystemsGraphViewControlAPI.h"

#include "x11_pixel_map.h"
#include <X11/PluginWindowX11.h>


class CDotView : public FB::PluginWindowX11, public CDotViewCommon, public boost::signals2::trackable
{
	typedef FB::PluginWindowX11 base;
protected:
    ln::PointD m_ptOffset;

public:
	CDotView(const FB::WindowContextX11 & ctx);

	virtual void Invalidate();
	virtual int GetScrollOffsetX();
	virtual int GetScrollOffsetY();
	virtual void SetScrollOffset(int x, int y);
	virtual void SetScrollSize(int w, int h, bool redraw);
	virtual bool GetClientRectangle(ln::RectD & rect);
	virtual void UpdateWindow();
	virtual void InvalidateSelection();
	virtual void operator()(const std::string & dot, const std::string & svg);

	//  --- IAPICallback ---
	//  --- IAPICallback ---
	void RenderCluster(ln::ICluster * cluster);
	void InvalidateScreenRect(const ln::RectD & screenRect);
	void InvalidateWorldRect(const ln::RectD & worldRect);
	//  Linux  ---
	void DoPaint(GdkEvent * evt);
	void OnLButtonDown(ln::PointD point);
	void OnLButtonUp(ln::PointD point, guint modifierState);
	void OnMouseMove(ln::PointD point);
	void OnLButtonDblClk(ln::PointD point);

	int OnLayoutComplete(void * wParam, void * lParam);

	//  Layot Callback  ---
};
