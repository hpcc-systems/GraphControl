#pragma once

#include "DotViewCommon.h"

#include <platform/win32/agg_win32_bmp.h>
//#include "HPCCSystemsGraphViewControlAPI.h"

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
	virtual bool GetClientRectangle(ln::RectD & rect);
	virtual void UpdateWindow();
	virtual void InvalidateSelection();
	virtual void operator()(const std::string & dot, const std::string & svg);

	//  --- IAPICallback ---
	//  --- IAPICallback ---
	void RenderCluster(ln::ICluster * cluster);
	void InvalidateScreenRect(const ln::RectD & screenRect);
	void InvalidateWorldRect(const ln::RectD & worldRect);

	//  Windows  ---
	void DoPaint(CDCHandle dc);

	BEGIN_MSG_MAP(CDotView)
		MSG_WM_ERASEBKGND(OnEraseBkgnd)

		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_LBUTTONDBLCLK(OnLButtonDblClk)
		MSG_WM_MOUSEWHEEL(OnMouseWheel)

		REFLECTED_NOTIFY_ID_HANDLER_EX(WM_MOUSEWHEEL, OnReflectedNotifyIDHandlerEX)

		MESSAGE_HANDLER_EX(UMDV_LAYOUT_COMPLETE, OnLayoutComplete);

		CHAIN_MSG_MAP(CScrollWindowImpl<CDotView>)
	END_MSG_MAP()

	BOOL OnEraseBkgnd(CDCHandle dc);

	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonDblClk(UINT nFlags, CPoint point);
	bool DoMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	LRESULT OnReflectedNotifyIDHandlerEX(LPNMHDR pnmh)
	{
		return 0;
	}


	LRESULT OnLayoutComplete(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/);

	//  Layot Callback  ---
};
