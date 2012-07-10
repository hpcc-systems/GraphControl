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

#include "DotViewCommon.h"

#include <XgmmlParser.h>
#include <DotParser.h>
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
#include "HPCCSystemsGraphViewControlAPI.h"

CDotViewCommon::CDotViewCommon()
{
	m_api = NULL;
	m_g = hpcc::CreateGraph();

	m_buffer = hpcc::CreateGraphBuffer(0, 0);
	m_hotItem = hpcc::CreateGraphHotItem();
	m_selection = hpcc::CreateGraphSelectionBag();

	m_gr = hpcc::CreateGraphRender(m_g, m_buffer, m_hotItem, m_selection);
	//m_gro = hpcc::CreateGraphRender(m_g, m_buffer, m_hotItem, m_selection, 0.05);

	m_mouseDown = MOUSEDOWN_UNKNOWN;
}

void CDotViewCommon::StartLayout(const std::string & layout)
{
	m_g->SetProperty(hpcc::PROP_LAYOUT, layout.c_str());
	hpcc::DoGraphvizLayout(m_g, m_dot, boost::ref(*this));
}

double CDotViewCommon::SetScale(double scale)
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

double CDotViewCommon::GetScale()
{
	return m_gr->GetScale();
}

void CDotViewCommon::CenterOnGraphItem(hpcc::IGraphItem * item)
{
	hpcc::RectD itemRect = m_gr->GetBoundingRect(item, true);
	hpcc::PointD itemCP;
	itemRect.GetCenter(&itemCP);
	CenterOn(itemCP);
}

void CDotViewCommon::CenterOnItem(int _item, bool sizeToFit, bool widthOnly)
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
		m_api->fire_Scaled((int)(m_gr->GetScale() * 100));
	}
	else
		CenterOnGraphItem(item);
}

void CDotViewCommon::SetMessage(const std::string & msg)
{
	m_gr->SetMessage(msg);
	CalcScrollbars(true);
	if (msg.empty())
		CenterOnGraphItem(NULL);
	Invalidate();
	UpdateWindow();
}

int CDotViewCommon::Find(const std::string & text, bool includeProperties, std::vector<int> & results)
{
	const hpcc::IVertexSet & vs = m_g->GetAllVertices();
	for(hpcc::IVertexSet::const_iterator itr = vs.begin(); itr != vs.end(); ++itr)
	{
		if (boost::algorithm::icontains(itr->get()->GetPropertyString(hpcc::DOT_LABEL), text))
			results.push_back(itr->get()->GetID());
	}
	return results.size();
}

bool CDotViewCommon::HasItems()
{
	return !m_g->GetAllVertices().empty() || !m_g->GetAllEdges().empty() || !m_g->GetClusters().empty();
}

int CDotViewCommon::GetSelection(std::vector<int> & results)
{
	return m_selection->GetSelection(results);
}

int CDotViewCommon::GetSelection(std::vector<std::string> & results)
{
	return m_selection->GetSelection(m_g, results);
}

bool CDotViewCommon::SetSelected(const std::vector<int> & _items, bool clearPrevious)
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

bool CDotViewCommon::SetSelected(const std::vector<std::string> & _items, bool clearPrevious)
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

const hpcc::IClusterSet & CDotViewCommon::GetClusters()
{
	return m_g->GetClusters();
}

int CDotViewCommon::GetProperties(int _item, hpcc::StringStringMap & results)
{
	hpcc::IGraphItemPtr item = m_g->GetGraphItem(_item);
	if (item)
		item->GetProperties(results);
	return results.size();
}

unsigned int CDotViewCommon::GetItem(const std::string &externalID)
{
	if (hpcc::IGraphItem * item = m_g->GetVertex(externalID, true))
		return item->GetID();
	if (hpcc::IGraphItem * item = m_g->GetEdge(externalID, true))
		return item->GetID();
	if (hpcc::IGraphItem * item = m_g->GetCluster(externalID, true))
		return item->GetID();
	if (hpcc::IGraphItem * item = m_g->GetGraph(externalID, true))
		return item->GetID();
	return 0;
}

const char * CDotViewCommon::GetGlobalID(int item)
{
	return m_g->GetExternalID(item);
}

int CDotViewCommon::GetVertices(std::vector<int> & results)
{
	const hpcc::IVertexSet & vertices = m_g->GetAllVertices();
	for(hpcc::IVertexSet::const_iterator itr = vertices.begin(); itr != vertices.end(); ++itr)
		results.push_back(itr->get()->GetID());
	return results.size();
}

void LoadTestData(hpcc::IGraph * g, hpcc::ICluster * c, hpcc::IVertex * v, int depth = 0)
{
	if (++depth > 14)
		return;

	hpcc::IClusterPtr c2 = (depth % 5 == 0) ? c : g->CreateCluster(c);
	c2->SetProperty(hpcc::DOT_LABEL, (boost::format("Cluster Depth %1%") % depth).str().c_str());
	int tot = (depth % 9 == 0) ? 5 : 1;
	for (int i = 0; i < tot; ++i)
	{
		hpcc::IVertexPtr v2 = g->CreateVertex(c2);
		v2->SetProperty(hpcc::DOT_LABEL, (boost::format("Depth %1%\\nVertex %2%") % depth % v2->GetIDString()).str().c_str());
		LoadTestData(g, c2, v2, depth);
		if (v)
		{
			hpcc::IEdgePtr e = g->CreateEdge(v, v2);
			e->SetProperty(hpcc::DOT_LABEL, (boost::format("Edge %1%") % e->GetIDString()).str().c_str());
		}
	}
}

void CDotViewCommon::LoadTestData()
{
	m_g->SetProperty(hpcc::DOT_LABEL, "Graph 1");
	::LoadTestData(m_g, NULL, NULL, 0);
}

void CDotViewCommon::LoadXML(const std::string & verticesXML, const std::string & edgesXML)
{
	std::string layout = m_g->GetPropertyString(hpcc::PROP_LAYOUT);
	m_hotItem->Set(NULL);
	m_selection->Clear();
	m_g->Clear();
	hpcc::LoadXML(m_g, verticesXML, edgesXML);
}

void CDotViewCommon::LoadXML2(const std::string & xml)
{
	std::string layout = m_g->GetPropertyString(hpcc::PROP_LAYOUT);
	m_hotItem->Set(NULL);
	m_selection->Clear();
	m_g->Clear();
	hpcc::LoadXML2(m_g, xml);
}

void CDotViewCommon::LoadXGMML(const std::string & xgmml)
{
	m_hotItem->Set(NULL);
	m_selection->Clear();
	m_g->Clear();
	hpcc::LoadXGMML(m_g, xgmml);
}

void CDotViewCommon::MergeXGMML(const std::string & xgmml)
{
	std::string layout = m_g->GetPropertyString(hpcc::PROP_LAYOUT);
	hpcc::MergeXGMML(m_g, xgmml);
	Invalidate();
}

void CDotViewCommon::MergeSVG(const std::string & svg)
{
	std::string layout = m_g->GetPropertyString(hpcc::PROP_LAYOUT);
	hpcc::MergeSVG(m_g, svg);
	Invalidate();
}

void CDotViewCommon::LoadDOT(const std::string & dot)
{
	std::string layout = m_g->GetPropertyString(hpcc::PROP_LAYOUT);
	m_hotItem->Set(NULL);
	m_selection->Clear();
	m_g->Clear();
	hpcc::LoadDOT(m_g, dot);
}

const char * CDotViewCommon::GetLocalisedXGMML(const std::vector<int> & items, int localisationDepth, int localisationDistance, std::string & xgmml)
{
	hpcc::IGraphItemSet graphItems;
	for(std::vector<int>::const_iterator itr = items.begin(); itr != items.end(); ++itr)
	{
		graphItems.insert(m_g->GetGraphItem(*itr));
	}
	hpcc::WriteLocalisedXGMML(m_g, graphItems, localisationDepth, localisationDistance, xgmml);
	return xgmml.c_str();
}

const std::string CDotViewCommon::GetSVG()
{
	return m_svg;
}

const std::string CDotViewCommon::GetDOT()
{
	return m_dot;
}

void CDotViewCommon::Clear()
{
	std::string layout = m_g->GetPropertyString(hpcc::PROP_LAYOUT);
	m_hotItem->Set(NULL);
	m_selection->Clear();
	m_g->Clear();
	Invalidate();
}

void CDotViewCommon::CalcScrollbars(bool redraw)
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

void CDotViewCommon::CenterOn(const hpcc::PointD & worldPoint)
{
	hpcc::PointD newCenter = m_gr->WorldToScreen(worldPoint);

	hpcc::RectD clientRect;
	GetClientRectangle(clientRect);

	SetScrollOffset((int)(newCenter.x - clientRect.Width / 2.0f), (int)(newCenter.y - clientRect.Height / 2.0f));
}

hpcc::PointD CDotViewCommon::GetCenterAsWorldPoint()
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

void CDotViewCommon::MoveTo(const hpcc::PointD & worldPoint, int x, int y)
{
	hpcc::PointD newCenter = m_gr->WorldToScreen(worldPoint);

	SetScrollOffset((int)(newCenter.x - x), (int)(newCenter.y - y));
}

