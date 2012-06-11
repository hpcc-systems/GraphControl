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

#include <SvgShapes.h>
#include <SvgParser.h>

#include "DotViewWin.h"
#include "HPCCSystemsGraphViewControlAPI.h"
#include <util.h>
#include <XgmmlParser.h>

CDotView::CDotView() : CDotViewCommon()
{
}

void CDotView::Invalidate()
{
	base::Invalidate();
}

void CDotView::UpdateWindow()
{
	base::UpdateWindow();
}

int CDotView::GetScrollOffsetX()
{
	return m_ptOffset.x;
}

int CDotView::GetScrollOffsetY()
{
	return m_ptOffset.y;
}

void CDotView::SetScrollOffset(int x, int y)
{
	base::SetScrollOffset(CPoint(x, y), true);
}

void CDotView::SetScrollSize(int w, int h, bool redraw)
{
	base::SetScrollSize(w, h, redraw);
}

bool CDotView::GetClientRectangle(hpcc::RectD & rect)
{
	CRect clientRect;
	HRESULT hResult = base::GetClientRect(clientRect);
	if (SUCCEEDED(hResult))
	{
		rect.x = clientRect.left;
		rect.y = clientRect.top;
		rect.Width = clientRect.Width();
		rect.Height = clientRect.Height();
		return true;
	}
	return false;
}

void CDotView::DoPaint(CDCHandle dc)
{
	CRect drc;
	dc.GetClipBox(drc);
	hpcc::RectI drcd(drc.left, drc.top, drc.right, drc.bottom);

	m_buffer->Resize(drc.Width(), drc.Height());
	m_gr->DoRender(drcd, true);

	hpcc::RectD winRect(drc.left, drc.top, drc.Width(), drc.Height());
	winRect = m_gr->ScreenToWorld(winRect);

	m_buffer->Draw(dc, drc);
}

BOOL CDotView::OnEraseBkgnd(CDCHandle dc)
{
	SetMsgHandled(true);
	return true;
}

void CDotView::OnSize(UINT nType, CSize size)
{
	ATLTRACE("size.cx:  %i\t", size.cx);
	ATLTRACE("size.cy:  %i\n", size.cy);
	//  Filter out silly sizes from web browser (dojo?)  ---
	if (size.cx >= 0 && size.cx < 10000 && size.cy >= 0 && size.cy < 10000)
		SetMsgHandled(false);
	else
		SetMsgHandled(true);
}

void CDotView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_mouseDown = MOUSEDOWN_NORMAL;
	m_mouseDownPosX = point.x;
	m_mouseDownPosY = point.y;
	m_scrollDownPosX = GetScrollPos(SB_HORZ);
	m_scrollDownPosY = GetScrollPos(SB_VERT);
	SetCapture();
}

void CDotView::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	switch (m_mouseDown)
	{
	case MOUSEDOWN_DBLCLK:
	case MOUSEDOWN_MOVED:
		m_mouseDown = MOUSEDOWN_UNKNOWN;
		return;
	}

	m_mouseDown = MOUSEDOWN_UNKNOWN;
	point.Offset(m_ptOffset);
	hpcc::IGraphItem * selectedItem = m_gr->GetItemAt(point.x, point.y);

	bool selChanged = false;
	if (selectedItem)
	{
		if ((GetKeyState(VK_CONTROL) & 0x8000) != 0)
		{
			if (m_selection->IsSelected(selectedItem))
				selChanged = m_selection->Deselect(selectedItem);
			else
				selChanged = m_selection->Select(selectedItem, false);
		}
		else
			selChanged = m_selection->Select(selectedItem);
	}

	if (selChanged)
	{
		InvalidateSelection();

		std::vector<int> selection;
		m_selection->GetSelection(selection);

		FB::VariantList items;
		for(std::vector<int>::const_iterator itr = selection.begin(); itr != selection.end(); ++itr)
			items.push_back(*itr);

		m_api->fire_SelectionChanged(items);
	}
}

void CDotView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	m_mouseDown = MOUSEDOWN_DBLCLK;
	point.Offset(m_ptOffset);
	hpcc::PointD worldDblClk(point.x, point.y);
	worldDblClk = m_gr->ScreenToWorld(worldDblClk);

	hpcc::IGraphItem * item = m_gr->GetItemAt(worldDblClk.x, worldDblClk.y, true);
	m_api->fire_MouseDoubleClick(item ? item->GetID() : 0);
}

bool CDotView::DoMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (!(nFlags & MK_CONTROL) && (GetFocus() == *this || GetFocus() == GetParent() || GetFocus() == GetParent().GetParent()))
	{
		ScreenToClient(&pt);
		CPoint point = pt;
		point.Offset(m_ptOffset);
		hpcc::PointD worldDblClk(point.x, point.y);
		worldDblClk = m_gr->ScreenToWorld(worldDblClk);

		double scale = m_gr->GetScale();
		if (zDelta > 0)
			m_gr->SetScale(scale + 0.05 * scale);
		else
			m_gr->SetScale(scale - 0.05 * scale);

		CalcScrollbars();
		MoveTo(worldDblClk, pt.x, pt.y);

		m_api->fire_Scaled((int)(m_gr->GetScale() * 100));
		return true;
	}
	return false;
}

BOOL CDotView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	ATLTRACE("CDotView::OnMouseWheel\n");
	if (!DoMouseWheel(nFlags, zDelta, pt))
		SetMsgHandled(false);

	return FALSE;
}

LRESULT CDotView::OnLayoutComplete(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam)
{
	assert(wParam && lParam);
	std::string * dot = (std::string *)wParam;
	std::string * svg = (std::string *)lParam;
	if (boost::algorithm::equals(m_dot, *dot))
	{
		m_svg = *svg;
		hpcc::MergeSVG(m_g, *svg);
		CalcScrollbars();
		CenterOnGraphItem(NULL);
		Invalidate();
		m_api->fire_LayoutFinished();
	}
	delete dot;
	delete svg;
	return 0;
}

void CDotView::InvalidateSelection()
{
	hpcc::RectD invalidateRect;
	if (m_selection->GetInvalidateRect(invalidateRect))
		InvalidateWorldRect(invalidateRect);
	if (m_selection->GetPrevInvalidateRect(invalidateRect))
		InvalidateWorldRect(invalidateRect);
}

void CDotView::InvalidateScreenRect(const hpcc::RectD & screenRect)
{
	CRect r;
	r.left = (LONG)screenRect.GetLeft() - GetScrollOffsetX();
	r.top = (LONG)screenRect.GetTop() - GetScrollOffsetY();
	r.right = (LONG)screenRect.GetRight() - GetScrollOffsetX() + 2;
	r.bottom = (LONG)screenRect.GetBottom() - GetScrollOffsetY() + 2;
	InvalidateRect(r);
}

void CDotView::InvalidateWorldRect(const hpcc::RectD & worldRect)
{
	InvalidateScreenRect(m_gr->WorldToScreen(worldRect));
}

void CDotView::OnMouseMove(UINT nFlags, CPoint point)
{
	SetFocus();
	switch (m_mouseDown)
	{
	case MOUSEDOWN_NORMAL:
	case MOUSEDOWN_MOVED:
		{
			ATLTRACE("mm_x:  %i\t", point.x);
			ATLTRACE("mm_y:  %i\n", point.y);

			int deltaX = point.x - m_mouseDownPosX;
			int deltaY = point.y - m_mouseDownPosY;

			SetScrollOffset(m_scrollDownPosX - deltaX, m_scrollDownPosY - deltaY);
			if (deltaX || deltaY)
				m_mouseDown = MOUSEDOWN_MOVED;
		}
		break;
	default:
		{
			point.Offset(m_ptOffset);
			hpcc::IGraphItem * hotItem = NULL;//m_gro->GetItemAt(point.x, point.y);
			if (!hotItem)
				hotItem = m_gr->GetItemAt(point.x, point.y);

			TRACKMOUSEEVENT tme = { 0 };
			tme.cbSize = sizeof(tme);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = m_hWnd;
			_TrackMouseEvent(&tme);

			if (m_hotItem->Set(hotItem))
			{
				hpcc::RectD invalidateRect;
				if (m_hotItem->GetInvalidateRect(invalidateRect))
					InvalidateWorldRect(invalidateRect);
				if (m_hotItem->GetPrevInvalidateRect(invalidateRect))
					InvalidateWorldRect(invalidateRect);
			}
		}
		break;
	}
}

void CDotView::OnMouseLeave()
{
	if (m_hotItem->Set(NULL))
	{
		hpcc::RectD invalidateRect;
		if (m_hotItem->GetInvalidateRect(invalidateRect))
			InvalidateWorldRect(invalidateRect);
		if (m_hotItem->GetPrevInvalidateRect(invalidateRect))
			InvalidateWorldRect(invalidateRect);
	}
}

void CDotView::operator()(const std::string & dot, const std::string & svg)
{
	PostMessage(UMDV_LAYOUT_COMPLETE, (WPARAM)new std::string(dot), (LPARAM)new std::string(svg));
}
