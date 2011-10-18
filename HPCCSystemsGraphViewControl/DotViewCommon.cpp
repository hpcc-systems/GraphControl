#include "DotViewCommon.h"

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
#include "HPCCSystemsGraphViewControlAPI.h"

void CDotViewCommon::StartLayout(const std::string & layout)
{
	m_g->SetProperty(ln::PROP_LAYOUT, layout.c_str());
	ln::DoGraphvizLayout(m_g, m_dot, boost::ref(*this));
}

double CDotViewCommon::SetScale(double scale)
{
	//  Keep center of screen in the middle
	ln::PointD worldDblClk = GetCenterAsWorldPoint();

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

void CDotViewCommon::CenterOnGraphItem(ln::IGraphItem * item)
{
	ln::RectD itemRect = m_gr->GetBoundingRect(item, true);
	ln::PointD itemCP;
	itemRect.GetCenter(&itemCP);
	CenterOn(itemCP);
}

void CDotViewCommon::CenterOnItem(int _item, bool sizeToFit, bool widthOnly)
{
	ln::IGraphItemPtr item = m_g->GetGraphItem(_item);
	bool scaleChanged = false;
	if (sizeToFit)
	{
		ln::RectD rc;
		GetClientRectangle(rc);

		double oldScale = m_gr->ScaleToFit(item, rc, widthOnly);
		if (oldScale != m_gr->GetScale())
			scaleChanged = true;
	}

	if (scaleChanged)
	{
		CalcScrollbars();
		CenterOnGraphItem(item);
		m_api->fireScaled((int)(m_gr->GetScale() * 100));
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
	const ln::IVertexSet & vs = m_g->GetAllVertices();
	for(ln::IVertexSet::const_iterator itr = vs.begin(); itr != vs.end(); ++itr)
	{
		if (boost::algorithm::icontains(itr->get()->GetPropertyString(ln::DOT_LABEL), text))
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
	ln::IGraphItemSet items;
	for(std::vector<int>::const_iterator itr = _items.begin(); itr != _items.end(); ++itr)
	{
		ln::IGraphItemPtr item = m_g->GetGraphItem(*itr);
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
	ln::IGraphItemSet items;
	for(std::vector<std::string>::const_iterator itr = _items.begin(); itr != _items.end(); ++itr)
	{
		ln::IGraphItemPtr item = m_g->GetGraphItem(GetItem(*itr));
		if (item)
			items.insert(item);
	}
	bool changed = m_selection->Select(items, clearPrevious);
	if (changed)
		InvalidateSelection();
	return changed;
}

const ln::IClusterSet & CDotViewCommon::GetClusters()
{
	return m_g->GetClusters();
}

int CDotViewCommon::GetProperties(int _item, ln::StringStringMap & results)
{
	ln::IGraphItemPtr item = m_g->GetGraphItem(_item);
	if (item)
		item->GetProperties(results);
	return results.size();
}

unsigned int CDotViewCommon::GetItem(const std::string &externalID)
{
	if (ln::IGraphItem * item = m_g->GetVertex(externalID, true))
		return item->GetID();
	if (ln::IGraphItem * item = m_g->GetEdge(externalID, true))
		return item->GetID();
	if (ln::IGraphItem * item = m_g->GetCluster(externalID, true))
		return item->GetID();
	return 0;
}

const char * CDotViewCommon::GetGlobalID(int item)
{
	return m_g->GetExternalID(item);
}

int CDotViewCommon::GetVertices(std::vector<int> & results)
{
	const ln::IVertexSet & vertices = m_g->GetAllVertices();
	for(ln::IVertexSet::const_iterator itr = vertices.begin(); itr != vertices.end(); ++itr)
		results.push_back(itr->get()->GetID());
	return results.size();
}

void LoadTestData(ln::IGraph * g, ln::ICluster * c, ln::IVertex * v, int depth = 0)
{
	if (++depth > 14)
		return;

	ln::IClusterPtr c2 = (depth % 5 == 0) ? c : g->CreateCluster(c);
	c2->SetProperty(ln::DOT_LABEL, (boost::format("Cluster Depth %1%") % depth).str().c_str());
	int tot = (depth % 9 == 0) ? 5 : 1;
	for (int i = 0; i < tot; ++i)
	{
		ln::IVertexPtr v2 = g->CreateVertex(c2);
		v2->SetProperty(ln::DOT_LABEL, (boost::format("Depth %1%\\nVertex %2%") % depth % v2->GetIDString()).str().c_str());
		LoadTestData(g, c2, v2, depth);
		if (v)
		{
			ln::IEdgePtr e = g->CreateEdge(v, v2);
			e->SetProperty(ln::DOT_LABEL, (boost::format("Edge %1%") % e->GetIDString()).str().c_str());
		}
	}
}

void CDotViewCommon::LoadTestData()
{
	m_g->SetProperty(ln::DOT_LABEL, "Graph 1");
	::LoadTestData(m_g, NULL, NULL, 0);
}

void CDotViewCommon::LoadXML(const std::string & verticesXML, const std::string & edgesXML)
{
	std::string layout = m_g->GetPropertyString(ln::PROP_LAYOUT);
	m_hotItem->Set(NULL);
	m_selection->Clear();
	m_g->Clear();
	ln::LoadXML(m_g, verticesXML, edgesXML);
}

void CDotViewCommon::LoadXML2(const std::string & xml)
{
	std::string layout = m_g->GetPropertyString(ln::PROP_LAYOUT);
	m_hotItem->Set(NULL);
	m_selection->Clear();
	m_g->Clear();
	ln::LoadXML2(m_g, xml);
}

void CDotViewCommon::LoadXGMML(const std::string & xgmml)
{
	std::string layout = m_g->GetPropertyString(ln::PROP_LAYOUT);
	m_hotItem->Set(NULL);
	m_selection->Clear();
	m_g->Clear();
	ln::LoadXGMML(m_g, xgmml);
}

void CDotViewCommon::MergeXGMML(const std::string & xgmml)
{
	std::string layout = m_g->GetPropertyString(ln::PROP_LAYOUT);
	ln::MergeXGMML(m_g, xgmml);
	Invalidate();
}

const char * CDotViewCommon::GetLocalisedXGMML(int _item, std::string & xgmml)
{
	ln::IGraphItemPtr item = m_g->GetGraphItem(_item);
	ln::WriteLocalisedXGMML(m_g, item, xgmml);
	return xgmml.c_str();
}

const std::string CDotViewCommon::GetSVG()
{
	return m_svg;
}

void CDotViewCommon::Clear()
{
	std::string layout = m_g->GetPropertyString(ln::PROP_LAYOUT);
	m_hotItem->Set(NULL);
	m_selection->Clear();
	m_g->Clear();
	Invalidate();
}

void CDotViewCommon::CalcScrollbars(bool redraw)
{
	ln::RectD graphRect = m_gr->GetBoundingRect();

	ln::RectD clientRect;
	GetClientRectangle(clientRect);

	unsigned int scrollWidth = (int)graphRect.Width + clientRect.Width;
	unsigned int scrollHeight = (int)graphRect.Height + clientRect.Height;

	ln::PointD offset;
	offset.x = clientRect.Width / 2.0f;
	offset.y = clientRect.Height / 2.0f;

	m_gr->SetOffset(offset);

	SetScrollSize(scrollWidth, scrollHeight, redraw);
}

void CDotViewCommon::CenterOn(const ln::PointD & worldPoint)
{
	ln::PointD newCenter = m_gr->WorldToScreen(worldPoint);

	ln::RectD clientRect;
	GetClientRectangle(clientRect);

	SetScrollOffset((int)(newCenter.x - clientRect.Width / 2.0f), (int)(newCenter.y - clientRect.Height / 2.0f));
}

ln::PointD CDotViewCommon::GetCenterAsWorldPoint()
{
	ln::RectD rc;
	GetClientRectangle(rc);
	ln::PointD point;
	rc.GetCenter(&point);
	point.x += GetScrollOffsetX();
	point.y += GetScrollOffsetY();

	ln::PointD worldDblClk(point.x, point.y);
	return m_gr->ScreenToWorld(worldDblClk);
}

void CDotViewCommon::MoveTo(const ln::PointD & worldPoint, int x, int y)
{
	ln::PointD newCenter = m_gr->WorldToScreen(worldPoint);

	SetScrollOffset((int)(newCenter.x - x), (int)(newCenter.y - y));
}

