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

#include <atlbase.h>
#include <atltypes.h>

#define _WTL_NO_CSTRING
#define _WTL_NO_WTYPES
#include <atlapp.h>
#include <atlgdi.h>
#include <atlscrl.h>
#include <atlcrack.h>

enum UMDV
{
	UMDV_FIRST = WM_APP + 1,
	UMDV_LAYOUT_COMPLETE, 
	UMDV_LAST
};

class CDotView : public CScrollWindowImpl<CDotView>, public CDotViewCommon, public boost::signals2::trackable
{
	typedef CScrollWindowImpl<CDotView> base;

public:
	CDotView();

	virtual void Invalidate();
	virtual int GetScrollOffsetX();
	virtual int GetScrollOffsetY();
	virtual void SetScrollOffset(int x, int y);
	virtual void SetScrollSize(int w, int h, bool redraw);
	virtual bool GetClientRectangle(hpcc::RectD & rect);
	virtual void UpdateWindow();
	virtual void InvalidateSelection();
	virtual void operator()(const std::string & dot, const std::string & svg);

	//  --- IAPICallback ---
	//  --- IAPICallback ---
	void RenderCluster(hpcc::ICluster * cluster);
	void InvalidateScreenRect(const hpcc::RectD & screenRect);
	void InvalidateWorldRect(const hpcc::RectD & worldRect);

	//  Windows  ---
	void DoPaint(CDCHandle dc);

	BEGIN_MSG_MAP(CDotView)
		MSG_WM_ERASEBKGND(OnEraseBkgnd)
		MSG_WM_SIZE(OnSize)

		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_LBUTTONDBLCLK(OnLButtonDblClk)
		MSG_WM_MOUSEWHEEL(OnMouseWheel)
		MSG_WM_MOUSELEAVE(OnMouseLeave)

		REFLECTED_NOTIFY_ID_HANDLER_EX(WM_MOUSEWHEEL, OnReflectedNotifyIDHandlerEX)

		MESSAGE_HANDLER_EX(UMDV_LAYOUT_COMPLETE, OnLayoutComplete);

		CHAIN_MSG_MAP(CScrollWindowImpl<CDotView>)
	END_MSG_MAP()

	BOOL OnEraseBkgnd(CDCHandle dc);
	void OnSize(UINT nType, CSize size);

	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonDblClk(UINT nFlags, CPoint point);
	bool DoMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void OnMouseLeave();

	LRESULT OnReflectedNotifyIDHandlerEX(LPNMHDR pnmh)
	{
		return 0;
	}


	LRESULT OnLayoutComplete(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/);

	//  Layot Callback  ---
};
