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
