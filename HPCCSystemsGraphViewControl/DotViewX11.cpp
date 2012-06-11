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

#include "DotViewX11.h"
#include "HPCCSystemsGraphViewControlAPI.h"
#include <util.h>
#include <XgmmlParser.h>

CDotView::CDotView(const FB::WindowContextX11 & ctx) : FB::PluginWindowX11(ctx), CDotViewCommon()
{
}

void CDotView::Invalidate()
{
	gdk_window_invalidate_rect(m_canvas->window, NULL, true);
}

void CDotView::UpdateWindow()
{
	//base::UpdateWindow();
}

int CDotView::GetScrollOffsetX()
{
	//return gtk_adjustment_get_value(gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(m_scrolled_window)));
	return m_ptOffset.x;
}

int CDotView::GetScrollOffsetY()
{
	//return gtk_adjustment_get_value(gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(m_scrolled_window)));
	return m_ptOffset.y;
}

void CDotView::SetScrollOffset(int x, int y)
{
	//gtk_adjustment_set_value(gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(m_scrolled_window)), x);
	//gtk_adjustment_set_value(gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(m_scrolled_window)), y);
    m_ptOffset.x = x < 0 ? 0 : (x > m_ptSize.x ? m_ptSize.x : x);
    m_ptOffset.y = y < 0 ? 0 : (y > m_ptSize.y ? m_ptSize.y : y);
    Invalidate();
}

void CDotView::SetScrollSize(int w, int h, bool redraw)
{
	gint width;
	gint height;
	gdk_window_get_size(m_canvas->window, &width, &height);

	m_ptSize.x = w - width;
	m_ptSize.y = h - height;
    //gtk_widget_set_size_request(m_canvas, w, h);
}

bool CDotView::GetClientRectangle(hpcc::RectD & rect)
{
	gint x, y;
	gdk_window_get_position(m_container->window, &x, &y);
	gint width, height;
	gdk_window_get_size(m_container->window, &width, &height);

	rect.x = x;
	rect.y = y;
	rect.Width = width;
	rect.Height = height;

	return true;
}

void CDotView::DoPaint(GdkEvent *evt)
{
	GdkEventExpose * event = reinterpret_cast<GdkEventExpose *>(evt);
	//GtkAdjustment * hadj = gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(win->m_scrolled_window));
	//GtkAdjustment * vadj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(win->m_scrolled_window));

	//hpcc::RectI rect(hadj->value, vadj->value, hadj->value + hadj->page_size, vadj->value + vadj->page_size);
	m_buffer->Resize(event->area.width, event->area.height);
	hpcc::RectI rect(event->area.x, event->area.y, event->area.x + event->area.width, event->area.y + event->area.height);
	rect.Offset(m_ptOffset.x, m_ptOffset.y);
	m_gr->DoRender(rect, true);
	m_buffer->Draw(m_canvas, event->area.x, event->area.y);
}

void CDotView::OnLButtonDown(hpcc::PointD point)
{
	m_mouseDown = MOUSEDOWN_NORMAL;
	m_mouseDownPosX = point.x;
	m_mouseDownPosY = point.y;
	m_scrollDownPosX = GetScrollOffsetX();
	m_scrollDownPosY = GetScrollOffsetY();
	//SetCapture();
}

void CDotView::OnLButtonUp(hpcc::PointD point, guint modifierState)
{
	//ReleaseCapture();
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
		if (modifierState & FB::MouseButtonEvent::ModifierState_Control)
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

void CDotView::OnLButtonDblClk(hpcc::PointD point)
{
	m_mouseDown = MOUSEDOWN_DBLCLK;
	point.Offset(m_ptOffset);
	hpcc::PointD worldDblClk(point.x, point.y);
	worldDblClk = m_gr->ScreenToWorld(worldDblClk);

	hpcc::IGraphItem * item = m_gr->GetItemAt(worldDblClk.x, worldDblClk.y, true);
	m_api->fire_MouseDoubleClick(item ? item->GetID() : 0);
}

int CDotView::OnLayoutComplete(void * wParam, void * lParam)
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
	gdk_window_invalidate_rect(m_canvas->window, NULL, true);
	/*	hpcc::RectD invalidateRect;
	if (m_selection->GetInvalidateRect(invalidateRect))
		InvalidateWorldRect(invalidateRect);
	if (m_selection->GetPrevInvalidateRect(invalidateRect))
		InvalidateWorldRect(invalidateRect);
	 */
}

void CDotView::InvalidateScreenRect(const hpcc::RectD & screenRect)
{
	gdk_window_invalidate_rect(m_canvas->window, NULL, true);
	/*
	GdkRectangle r;
	r.x = screenRect.GetLeft() - GetScrollOffsetX();
	r.y = screenRect.GetTop() - GetScrollOffsetY();
	r.width = screenRect.Width + 2;
	r.height = screenRect.Height + 2;
	gdk_window_invalidate_rect(m_canvas->window, &r, true);
	 */
}

void CDotView::InvalidateWorldRect(const hpcc::RectD & worldRect)
{
	gdk_window_invalidate_rect(m_canvas->window, NULL, true);
	/*
	InvalidateScreenRect(m_gr->WorldToScreen(worldRect));
	*/
}

void CDotView::OnMouseMove(hpcc::PointD point)
{
	switch (m_mouseDown)
	{
	case MOUSEDOWN_NORMAL:
	case MOUSEDOWN_MOVED:
		{
			int deltaX = point.x - m_mouseDownPosX;
			int deltaY = point.y - m_mouseDownPosY;

			SetScrollOffset(m_scrollDownPosX - deltaX, m_scrollDownPosY - deltaY);
			if (deltaX || deltaY)
				m_mouseDown = MOUSEDOWN_MOVED;
/*			
			g_object_freeze_notify(G_OBJECT(m_scrolled_window));
			gtk_adjustment_set_value(gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(m_scrolled_window)), m_scrollDownPosX - deltaX);
			gtk_adjustment_set_value(gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(m_scrolled_window)), m_scrollDownPosY - deltaY);
			gdk_window_invalidate_rect(m_scrolled_window->window, NULL, true);
			g_object_thaw_notify(G_OBJECT(m_scrolled_window));

			m_scrollDownPosX -= deltaX;
			m_scrollDownPosY -= deltaY;
*/
		}
		break;
	default:
		{
			point.Offset(m_ptOffset);
			hpcc::IGraphItem * hotItem = NULL;//m_gro->GetItemAt(point.x, point.y);
			if (!hotItem)
				hotItem = m_gr->GetItemAt(point.x, point.y);
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

void CDotView::operator()(const std::string & dot, const std::string & svg)
{
	//PostMessage(UMDV_LAYOUT_COMPLETE, (WPARAM)new std::string(dot), (LPARAM)new std::string(svg));
	OnLayoutComplete(new std::string(dot), new std::string(svg));
}
