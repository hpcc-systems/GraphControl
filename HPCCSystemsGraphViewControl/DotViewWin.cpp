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
#include "Platform.h"

#include <SvgShapes.h>
#include <SvgParser.h>

#include "DotViewWin.h"
#include "HPCCSystemsGraphViewControlAPI.h"
#include <util.h>
#include <XgmmlParser.h>

#include <boost/algorithm/string.hpp> 
#include <boost/format.hpp> 
namespace boost
{
#ifdef _UNICODE
	#define _tformat wformat
#else
	#define _tformat format
#endif
}

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

bool CDotView::GetClientRectangle(ln::RectD & rect)
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
	ln::RectI drcd(drc.left, drc.top, drc.right, drc.bottom);

	m_buffer->Resize(drc.Width(), drc.Height());
	m_gr->DoRender(drcd, true);

	ln::RectD winRect(drc.left, drc.top, drc.Width(), drc.Height());
	winRect = m_gr->ScreenToWorld(winRect);

	m_buffer->Draw(dc, drc);
}

BOOL CDotView::OnEraseBkgnd(CDCHandle dc)
{
	SetMsgHandled(true);
	return true;
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
	if (m_mouseDown == MOUSEDOWN_DBLCLK)
	{
		m_mouseDown = MOUSEDOWN_UNKNOWN;
		return;
	}
	m_mouseDown = MOUSEDOWN_UNKNOWN;
	point.Offset(m_ptOffset);
	ln::IGraphItem * selectedItem = m_gr->GetItemAt(point.x, point.y);
	if (ln::IGraph * graph = dynamic_cast<ln::IGraph *>(selectedItem))
		return;

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
		m_api->fireSelChanged(selection);
	}
}

void CDotView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	m_mouseDown = MOUSEDOWN_DBLCLK;
	point.Offset(m_ptOffset);
	ln::PointD worldDblClk(point.x, point.y);
	worldDblClk = m_gr->ScreenToWorld(worldDblClk);

	ln::IGraphItem * item = m_gr->GetItemAt(worldDblClk.x, worldDblClk.y, true);
	m_api->fireMouseDoubleClicked(item ? item->GetID() : 0);
}

bool CDotView::DoMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (!(nFlags & MK_CONTROL) && (GetFocus() == *this || GetFocus() == GetParent() || GetFocus() == GetParent().GetParent()))
	{
		ScreenToClient(&pt);
		CPoint point = pt;
		point.Offset(m_ptOffset);
		ln::PointD worldDblClk(point.x, point.y);
		worldDblClk = m_gr->ScreenToWorld(worldDblClk);

		double scale = m_gr->GetScale();
		if (zDelta > 0)
			m_gr->SetScale(scale + 0.05 * scale);
		else
			m_gr->SetScale(scale - 0.05 * scale);

		CalcScrollbars();
		MoveTo(worldDblClk, pt.x, pt.y);

		m_api->fireScaled((int)(m_gr->GetScale() * 100));
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
		MergeSVG(m_g, *svg);
		CalcScrollbars();
		CenterOnGraphItem(NULL);
		Invalidate();
		m_api->fireLayoutFinished();
	}
	delete dot;
	delete svg;
	return 0;
}

void CDotView::InvalidateSelection()
{
	ln::RectD invalidateRect;
	if (m_selection->GetInvalidateRect(invalidateRect))
		InvalidateWorldRect(invalidateRect);
	if (m_selection->GetPrevInvalidateRect(invalidateRect))
		InvalidateWorldRect(invalidateRect);
}

void CDotView::InvalidateScreenRect(const ln::RectD & screenRect)
{
	CRect r;
	r.left = (LONG)screenRect.GetLeft() - GetScrollOffsetX();
	r.top = (LONG)screenRect.GetTop() - GetScrollOffsetY();
	r.right = (LONG)screenRect.GetRight() - GetScrollOffsetX() + 2;
	r.bottom = (LONG)screenRect.GetBottom() - GetScrollOffsetY() + 2;
	InvalidateRect(r);
}

void CDotView::InvalidateWorldRect(const ln::RectD & worldRect)
{
	InvalidateScreenRect(m_gr->WorldToScreen(worldRect));
}

void CDotView::OnMouseMove(UINT nFlags, CPoint point)
{
	switch (m_mouseDown)
	{
	case MOUSEDOWN_NORMAL:
		{
			ATLTRACE("mm_x:  %i\t", point.x);
			ATLTRACE("mm_y:  %i\n", point.y);

			int deltaX = point.x - m_mouseDownPosX;
			int deltaY = point.y - m_mouseDownPosY;

			SetScrollOffset(m_scrollDownPosX - deltaX, m_scrollDownPosY - deltaY);
			//UpdateWindow();
		}
		break;
	default:
		{
			point.Offset(m_ptOffset);
			ln::IGraphItem * hotItem = NULL;//m_gro->GetItemAt(point.x, point.y);
			if (!hotItem)
				hotItem = m_gr->GetItemAt(point.x, point.y);
			if (m_hotItem->Set(hotItem))
			{
				ln::RectD invalidateRect;
				if (m_hotItem->GetInvalidateRect(invalidateRect))
					InvalidateWorldRect(invalidateRect);
				if (m_hotItem->GetPrevInvalidateRect(invalidateRect))
					InvalidateWorldRect(invalidateRect);
			}
		}
		break;
	}
}

void CDotView::operator()(const std::string & dot, const std::string & svg)
{
	PostMessage(UMDV_LAYOUT_COMPLETE, (WPARAM)new std::string(dot), (LPARAM)new std::string(svg));
}
