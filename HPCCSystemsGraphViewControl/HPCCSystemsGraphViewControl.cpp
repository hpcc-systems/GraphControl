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

#include "HPCCSystemsGraphViewControlAPI.h"

#include "HPCCSystemsGraphViewControl.h"
#if defined FB_WIN
#include "PluginWindowWin.h"
#elif defined FB_X11
#include "PluginWindowX11.h"
#elif defined FB_MACOSX
#include "PluginWindowMac.h"
#endif

#include <XgmmlParser.h>
#include <DotParser.h>
#include <boost/algorithm/string.hpp>

///////////////////////////////////////////////////////////////////////////////
/// @fn HPCCSystemsGraphViewControl::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginInitialize()
///
/// @see FB::FactoryBase::globalPluginInitialize
///////////////////////////////////////////////////////////////////////////////
void HPCCSystemsGraphViewControl::StaticInitialize()
{
    // Place one-time initialization stuff here; As of FireBreath 1.4 this should only
    // be called once per process
}

///////////////////////////////////////////////////////////////////////////////
/// @fn HPCCSystemsGraphViewControl::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginDeinitialize()
///
/// @see FB::FactoryBase::globalPluginDeinitialize
///////////////////////////////////////////////////////////////////////////////
void HPCCSystemsGraphViewControl::StaticDeinitialize()
{
    // Place one-time deinitialization stuff here. As of FireBreath 1.4 this should
    // always be called just before the plugin library is unloaded
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  HPCCSystemsGraphViewControl constructor.  Note that your API is not available
///         at this point, nor the window.  For best results wait to use
///         the JSAPI object until the onPluginReady method is called
///////////////////////////////////////////////////////////////////////////////
HPCCSystemsGraphViewControl::HPCCSystemsGraphViewControl()
{
	m_g = hpcc::CreateGraph();

	m_buffer = hpcc::CreateGraphBuffer(0, 0);
	m_hotItem = hpcc::CreateGraphHotItem();
	m_selection = hpcc::CreateGraphSelectionBag();

	m_gr = hpcc::CreateGraphRender(m_g, m_buffer, m_hotItem, m_selection);
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  HPCCSystemsGraphViewControl destructor.
///////////////////////////////////////////////////////////////////////////////
HPCCSystemsGraphViewControl::~HPCCSystemsGraphViewControl()
{
    // This is optional, but if you reset m_api (the shared_ptr to your JSAPI
    // root object) and tell the host to free the retained JSAPI objects then
    // unless you are holding another shared_ptr reference to your JSAPI object
    // they will be released here.
    releaseRootJSAPI();
    m_host->freeRetainedObjects();
}

void HPCCSystemsGraphViewControl::onPluginReady()
{
    // When this is called, the BrowserHost is attached, the JSAPI object is
    // created, and we are ready to interact with the page and such.  The
    // PluginWindow may or may not have already fire the AttachedEvent at
    // this point.
}

void HPCCSystemsGraphViewControl::shutdown()
{
    // This will be called when it is time for the plugin to shut down;
    // any threads or anything else that may hold a shared_ptr to this
    // object should be released here so that this object can be safely
    // destroyed. This is the last point that shared_from_this and weak_ptr
    // references to this object will be valid
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  Creates an instance of the JSAPI object that provides your main
///         Javascript interface.
///
/// Note that m_host is your BrowserHost and shared_ptr returns a
/// FB::PluginCorePtr, which can be used to provide a
/// boost::weak_ptr<HPCCSystemsGraphViewControl> for your JSAPI class.
///
/// Be very careful where you hold a shared_ptr to your plugin class from,
/// as it could prevent your plugin class from getting destroyed properly.
///////////////////////////////////////////////////////////////////////////////
FB::JSAPIPtr HPCCSystemsGraphViewControl::createJSAPI()
{
    // m_host is the BrowserHost
    return boost::make_shared<HPCCSystemsGraphViewControlAPI>(FB::ptr_cast<HPCCSystemsGraphViewControl>(shared_from_this()), m_host);
}

void HPCCSystemsGraphViewControl::Invalidate()
{
	FB::PluginWindow* window = GetWindow();
	if (window)
	{
		GetWindow()->InvalidateWindow();
	}
}

void HPCCSystemsGraphViewControl::InvalidateWorldRect(const hpcc::RectD & worldRect)
{
	Invalidate();
}

int HPCCSystemsGraphViewControl::GetScrollOffsetX()
{
	return m_ptOffset.x;
}

int HPCCSystemsGraphViewControl::GetScrollOffsetY()
{
	return m_ptOffset.y;
}

void HPCCSystemsGraphViewControl::SetScrollOffset(int x, int y)
{
    m_ptOffset.x = x < 0 ? 0 : (x > m_ptSize.x ? m_ptSize.x : x);
    m_ptOffset.y = y < 0 ? 0 : (y > m_ptSize.y ? m_ptSize.y : y);
    Invalidate();
}

void HPCCSystemsGraphViewControl::SetScrollSize(int w, int h, bool redraw)
{
	FB::PluginWindow* window = GetWindow();
	if (window)
	{
		int width = GetWindow()->getWindowWidth();
		int height = GetWindow()->getWindowHeight();

		m_ptSize.x = w - width;
		m_ptSize.y = h - height;
	}
}

bool HPCCSystemsGraphViewControl::GetClientRectangle(hpcc::RectD & rect)
{
	FB::PluginWindow* window = GetWindow();
	if (window)
	{
		FB::Rect rect2 = GetWindow()->getWindowPosition();
		rect.x = rect2.left;
		rect.y = rect2.top;
		rect.Width = rect2.right - rect2.left;
		rect.Height = rect2.bottom - rect2.top;
		return true;
	}
	return false;
}

void HPCCSystemsGraphViewControl::UpdateWindow()
{
}

void HPCCSystemsGraphViewControl::InvalidateSelection()
{
	Invalidate();
}

void HPCCSystemsGraphViewControl::operator()(const std::string & dot, const std::string & svg)
{
	//PostMessage(UMDV_LAYOUT_COMPLETE, (WPARAM)new std::string(dot), (LPARAM)new std::string(svg));
	OnLayoutComplete(new std::string(dot), new std::string(svg));
}

void HPCCSystemsGraphViewControl::CalcScrollbars(bool redraw)
{
	hpcc::RectD graphRect = m_gr->GetBoundingRect();

	hpcc::RectD clientRect;
	GetClientRectangle(clientRect);

	unsigned int scrollWidth = (unsigned int)(graphRect.Width + clientRect.Width);
	unsigned int scrollHeight = (unsigned int)(graphRect.Height + clientRect.Height);

	hpcc::PointD offset;
	offset.x = clientRect.Width / 2.0f;
	offset.y = clientRect.Height / 2.0f;

	m_gr->SetOffset(offset);

	SetScrollSize(scrollWidth, scrollHeight, redraw);
}
void HPCCSystemsGraphViewControl::CenterOn(const hpcc::PointD & worldPoint)
{
	hpcc::PointD newCenter = m_gr->WorldToScreen(worldPoint);

	hpcc::RectD clientRect;
	GetClientRectangle(clientRect);

	SetScrollOffset((int)(newCenter.x - clientRect.Width / 2.0f), (int)(newCenter.y - clientRect.Height / 2.0f));
}

hpcc::PointD HPCCSystemsGraphViewControl::GetCenterAsWorldPoint()
{
	hpcc::RectD rc;
	GetClientRectangle(rc);
	hpcc::PointD point;
	rc.GetCenter(&point);
	point.x += GetScrollOffsetX();
	point.y += GetScrollOffsetY();

	hpcc::PointD worldDblClk(point.x, point.y);
	return m_gr->ScreenToWorld(worldDblClk);
}

void HPCCSystemsGraphViewControl::MoveTo(const hpcc::PointD & worldPoint, int x, int y)
{
	hpcc::PointD newCenter = m_gr->WorldToScreen(worldPoint);

	SetScrollOffset((int)(newCenter.x - x), (int)(newCenter.y - y));
}


void HPCCSystemsGraphViewControl::Clear()
{
	std::string layout = m_g->GetPropertyString(hpcc::PROP_LAYOUT);
	m_hotItem->Set(NULL);
	m_selection->Clear();
	m_g->Clear();
	Invalidate();
}

void HPCCSystemsGraphViewControl::LoadTestData()
{
	m_g->SetProperty(hpcc::DOT_LABEL, "Graph 1");
	//::LoadTestData(m_g, NULL, NULL, 0);
}

void HPCCSystemsGraphViewControl::LoadXML(const std::string & verticesXML, const std::string & edgesXML)
{
	std::string layout = m_g->GetPropertyString(hpcc::PROP_LAYOUT);
	m_hotItem->Set(NULL);
	m_selection->Clear();
	m_g->Clear();
	hpcc::LoadXML(m_g, verticesXML, edgesXML);
}

void HPCCSystemsGraphViewControl::LoadXML2(const std::string & xml)
{
	std::string layout = m_g->GetPropertyString(hpcc::PROP_LAYOUT);
	m_hotItem->Set(NULL);
	m_selection->Clear();
	m_g->Clear();
	hpcc::LoadXML2(m_g, xml);
}

void HPCCSystemsGraphViewControl::LoadXGMML(const std::string & xgmml)
{
	std::string layout = m_g->GetPropertyString(hpcc::PROP_LAYOUT);
	m_hotItem->Set(NULL);
	m_selection->Clear();
	m_g->Clear();
	hpcc::LoadXGMML(m_g, xgmml);
}

void HPCCSystemsGraphViewControl::MergeXGMML(const std::string & xgmml)
{
	std::string layout = m_g->GetPropertyString(hpcc::PROP_LAYOUT);
	hpcc::MergeXGMML(m_g, xgmml);
	Invalidate();
}

bool HPCCSystemsGraphViewControl::MergeSVG(const std::string & svg)
{
	if (hpcc::MergeSVG(m_g, svg))
	{
		CalcScrollbars();
		CenterOnGraphItem(NULL);
		Invalidate();
		return true;
	}
	return false;
}

void HPCCSystemsGraphViewControl::LoadDOT(const std::string & dot)
{
	std::string layout = m_g->GetPropertyString(hpcc::PROP_LAYOUT);
	m_hotItem->Set(NULL);
	m_selection->Clear();
	m_g->Clear();
	hpcc::LoadDOT(m_g, dot);
}

const std::string HPCCSystemsGraphViewControl::GetSVG()
{
	return m_svg;
}

const std::string HPCCSystemsGraphViewControl::GetDOT()
{
	return m_dot;
}

const char * HPCCSystemsGraphViewControl::GetLocalisedXGMML(const std::vector<int> & items, int localisationDepth, int localisationDistance, std::string & xgmml)
{
	hpcc::IGraphItemSet graphItems;
	for(std::vector<int>::const_iterator itr = items.begin(); itr != items.end(); ++itr)
	{
		graphItems.insert(m_g->GetGraphItem(*itr));
	}
	hpcc::WriteLocalisedXGMML(m_g, graphItems, localisationDepth, localisationDistance, xgmml);
	return xgmml.c_str();
}

double HPCCSystemsGraphViewControl::SetScale(double scale)
{
	//  Keep center of screen in the middle
	hpcc::PointD worldDblClk = GetCenterAsWorldPoint();

	double oldScale = m_gr->SetScale(scale);
	if (oldScale != scale)
	{
		CalcScrollbars();
		CenterOn(worldDblClk);
	}
	Invalidate();
	return oldScale;
}

double HPCCSystemsGraphViewControl::GetScale()
{
	return m_gr->GetScale();
}

void HPCCSystemsGraphViewControl::CenterOnGraphItem(hpcc::IGraphItem * item)
{
	hpcc::RectD itemRect = m_gr->GetBoundingRect(item, true);
	hpcc::PointD itemCP;
	itemRect.GetCenter(&itemCP);
	CenterOn(itemCP);
}

void HPCCSystemsGraphViewControl::CenterOnItem(int _item, bool sizeToFit, bool widthOnly)
{
	hpcc::IGraphItemPtr item = m_g->GetGraphItem(_item);
	bool scaleChanged = false;
	if (sizeToFit)
	{
		hpcc::RectD rc;
		GetClientRectangle(rc);

		double oldScale = m_gr->ScaleToFit(item, rc, widthOnly);
		if (oldScale != m_gr->GetScale())
			scaleChanged = true;
	}

	if (scaleChanged)
	{
		CalcScrollbars();
		CenterOnGraphItem(item);
		boost::static_pointer_cast<HPCCSystemsGraphViewControlAPI>(getRootJSAPI())->fire_Scaled((int)(m_gr->GetScale() * 100));
	}
	else
		CenterOnGraphItem(item);
}

void HPCCSystemsGraphViewControl::StartLayout(const std::string & layout)
{
	m_g->SetProperty(hpcc::PROP_LAYOUT, layout.c_str());
	hpcc::DoGraphvizLayout(m_g, m_dot, boost::ref(*this));
}

void HPCCSystemsGraphViewControl::SetMessage(const std::string & msg)
{
	m_gr->SetMessage(msg);
	CalcScrollbars(true);
	if (msg.empty())
		CenterOnGraphItem(NULL);
	Invalidate();
	UpdateWindow();
}

int HPCCSystemsGraphViewControl::Find(const std::string & text, bool includeProperties, std::vector<int> & results)
{
	const hpcc::IVertexSet & vs = m_g->GetAllVertices();
	for(hpcc::IVertexSet::const_iterator itr = vs.begin(); itr != vs.end(); ++itr)
	{
		if (boost::algorithm::icontains(itr->get()->GetPropertyString(hpcc::DOT_LABEL), text))
			results.push_back(itr->get()->GetID());
	}
	return results.size();
}

bool HPCCSystemsGraphViewControl::HasItems()
{
	return !m_g->GetAllVertices().empty() || !m_g->GetAllEdges().empty() || !m_g->GetClusters().empty();
}

int HPCCSystemsGraphViewControl::GetSelection(std::vector<int> & results)
{
	return m_selection->GetSelection(results);
}

int HPCCSystemsGraphViewControl::GetSelection(std::vector<std::string> & results)
{
	return m_selection->GetSelection(m_g, results);
}

bool HPCCSystemsGraphViewControl::SetSelected(const std::vector<int> & _items, bool clearPrevious)
{
	hpcc::IGraphItemSet items;
	for(std::vector<int>::const_iterator itr = _items.begin(); itr != _items.end(); ++itr)
	{
		hpcc::IGraphItemPtr item = m_g->GetGraphItem(*itr);
		if (item)
			items.insert(item);
	}
	bool changed = m_selection->Select(items, clearPrevious);
	if (changed)
		InvalidateSelection();
	return changed;
}

bool HPCCSystemsGraphViewControl::SetSelected(const std::vector<std::string> & _items, bool clearPrevious)
{
	hpcc::IGraphItemSet items;
	for(std::vector<std::string>::const_iterator itr = _items.begin(); itr != _items.end(); ++itr)
	{
		hpcc::IGraphItemPtr item = m_g->GetGraphItem(GetItem(*itr));
		if (item)
			items.insert(item);
	}
	bool changed = m_selection->Select(items, clearPrevious);
	if (changed)
		InvalidateSelection();
	return changed;
}

const hpcc::IClusterSet & HPCCSystemsGraphViewControl::GetClusters()
{
	return m_g->GetClusters();
}

int HPCCSystemsGraphViewControl::GetProperties(int _item, hpcc::StringStringMap & results)
{
	hpcc::IGraphItemPtr item = m_g->GetGraphItem(_item);
	if (item)
		item->GetProperties(results);
	return results.size();
}

unsigned int HPCCSystemsGraphViewControl::GetItem(const std::string &externalID)
{
	if (hpcc::IGraphItem * item = m_g->GetVertex(externalID, true))
		return item->GetID();
	if (hpcc::IGraphItem * item = m_g->GetEdge(externalID, true))
		return item->GetID();
	if (hpcc::IGraphItem * item = m_g->GetCluster(externalID, true))
		return item->GetID();
	return 0;
}

const char * HPCCSystemsGraphViewControl::GetGlobalID(int item)
{
	return m_g->GetExternalID(item);
}

int HPCCSystemsGraphViewControl::GetVertices(std::vector<int> & results)
{
	const hpcc::IVertexSet & vertices = m_g->GetAllVertices();
	for(hpcc::IVertexSet::const_iterator itr = vertices.begin(); itr != vertices.end(); ++itr)
		results.push_back(itr->get()->GetID());
	return results.size();
}

bool HPCCSystemsGraphViewControl::onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *)
{
	m_mouseDown = MOUSEDOWN_NORMAL;
	m_mouseDownPosX = evt->m_x;
	m_mouseDownPosY = evt->m_y;
	m_scrollDownPosX = GetScrollOffsetX();
	m_scrollDownPosY = GetScrollOffsetY();
    return true;
}

bool HPCCSystemsGraphViewControl::onMouseDoubleClick(FB::MouseDoubleClickEvent *evt, FB::PluginWindow *)
{
	hpcc::PointD point(evt->m_x, evt->m_y);
	m_mouseDown = MOUSEDOWN_DBLCLK;
	point.Offset(m_ptOffset);
	hpcc::PointD worldDblClk(point.x, point.y);
	worldDblClk = m_gr->ScreenToWorld(worldDblClk);

	hpcc::IGraphItem * item = m_gr->GetItemAt(worldDblClk.x, worldDblClk.y, true);
	boost::static_pointer_cast<HPCCSystemsGraphViewControlAPI>(getRootJSAPI())->fire_MouseDoubleClick(item ? item->GetID() : 0);
	return true;
}

bool HPCCSystemsGraphViewControl::onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *)
{
	hpcc::PointD point(evt->m_x, evt->m_y);
	switch (m_mouseDown)
	{
	case MOUSEDOWN_DBLCLK:
	case MOUSEDOWN_MOVED:
		m_mouseDown = MOUSEDOWN_UNKNOWN;
		return true;
	}

	m_mouseDown = MOUSEDOWN_UNKNOWN;
	point.Offset(m_ptOffset);
	hpcc::IGraphItem * selectedItem = m_gr->GetItemAt(point.x, point.y);

	bool selChanged = false;
	if (selectedItem)
	{
		if (evt->m_state & FB::MouseButtonEvent::ModifierState_Control)
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

		boost::static_pointer_cast<HPCCSystemsGraphViewControlAPI>(getRootJSAPI())->fire_SelectionChanged(items);
	}
    return true;
}

bool HPCCSystemsGraphViewControl::onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *)
{
	hpcc::PointD point(evt->m_x, evt->m_y);
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
		}
		break;
	default:
		{
			point.Offset(m_ptOffset);
			hpcc::IGraphItem * hotItem = NULL;
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
	return true;
}

bool HPCCSystemsGraphViewControl::onMouseScroll(FB::MouseScrollEvent *evt, FB::PluginWindow *)
{
	hpcc::PointD pt(evt->m_x, evt->m_y);
	hpcc::PointD delta(evt->m_dx, evt->m_dy);
	if (evt->m_state & FB::MouseButtonEvent::ModifierState_Control)
	{
		hpcc::PointD point = pt;
		point.Offset(m_ptOffset);
		hpcc::PointD worldDblClk(point.x, point.y);
		worldDblClk = m_gr->ScreenToWorld(worldDblClk);
		double zDelta = delta.x != 0 ? delta.x : delta.y;
		double scale = m_gr->GetScale();
		if (zDelta > 0)
			m_gr->SetScale(scale + 0.05 * scale);
		else
			m_gr->SetScale(scale - 0.05 * scale);

		CalcScrollbars();
		MoveTo(worldDblClk, pt.x, pt.y);

		boost::static_pointer_cast<HPCCSystemsGraphViewControlAPI>(getRootJSAPI())->fire_Scaled((int)(m_gr->GetScale() * 100));
	} else {
		hpcc::PointD point = pt;
		point.Offset(m_ptOffset);
		hpcc::PointD worldDblClk(point.x, point.y);
		worldDblClk = m_gr->ScreenToWorld(worldDblClk);

		pt.x -= delta.x;
		pt.y -= delta.y;

		MoveTo(worldDblClk, pt.x, pt.y);
	}
    return true;
}

int HPCCSystemsGraphViewControl::OnLayoutComplete(void * wParam, void * lParam)
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
		boost::static_pointer_cast<HPCCSystemsGraphViewControlAPI>(getRootJSAPI())->fire_LayoutFinished();
	}
	delete dot;
	delete svg;
	return 0;
}

bool HPCCSystemsGraphViewControl::onResized(FB::ResizedEvent *evt, FB::PluginWindow *)
{
	CalcScrollbars();
	return true;
}

bool HPCCSystemsGraphViewControl::onRefresh(FB::RefreshEvent *evt, FB::PluginWindow *)
{
	hpcc::RectI bounds(0, 0, evt->bounds.right, evt->bounds.bottom);
	hpcc::RectI rect(bounds);
	rect.Offset(m_ptOffset.x, m_ptOffset.y);

	m_buffer->Resize(rect.Width(), rect.Height());
	m_gr->DoRender(rect, true);

#if defined FB_WIN
	m_buffer->Draw(((FB::PluginWindowWin*)GetWindow())->getHWND(), bounds.left, bounds.top);
#elif defined FB_MACOSX
	m_buffer->Draw(((FB::CoreGraphicsDraw *)evt)->context, bounds.left, bounds.top);
#elif defined FB_X11
	m_buffer->Draw(((FB::PluginWindowX11*)GetWindow())->getWidget(), bounds.left, bounds.top);
#endif

	return true;
}

bool HPCCSystemsGraphViewControl::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow *)
{
    // The window is attached; act appropriately
    return false;
}

bool HPCCSystemsGraphViewControl::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *)
{
    // The window is about to be detached; act appropriately
    return false;
}

