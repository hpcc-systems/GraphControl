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

#include "SaxParser.h"
#include "GraphDB.h"
#include "SvgShapes.h"
#include "SvgParser.h"

namespace hpcc
{
//  ===========================================================================
class ParseException : public std::exception
{
public:
	ParseException() : std::exception()
	{
	}
};
//  ===========================================================================
class CSvgParser : public CStackParser
{
protected:
	PointD m_offset;
	IGraphPtr m_graph;

	bool m_valid;

	IGraphItemPtr m_currentItem;
	ElementGPtr m_currentElementG;

public:
	CSvgParser(IGraph * graph) : m_graph(graph)
	{
		m_valid = false;
		m_currentItem = NULL;
	}

	virtual void OnStartElement(const XML_Char *pszName, const XML_Char **papszAttrs)
	{
		CStackParser::OnStartElement(pszName, papszAttrs);
		CElementPtr e = m_stack.top();

		if (0 == e->m_tag.compare("svg"))
		{
			m_valid = true;
			for(hpcc::IClusterSet::const_iterator itr = m_graph->GetAllClusters().begin(); itr != m_graph->GetAllClusters().end(); ++itr)
			{
				itr->get()->SetProperty(SVG_PROP_ELEMENTG, (CUnknown *)NULL);
			}
			for(hpcc::IVertexSet::const_iterator itr = m_graph->GetAllVertices().begin(); itr != m_graph->GetAllVertices().end(); ++itr)
			{
				itr->get()->SetProperty(SVG_PROP_ELEMENTG, (CUnknown *)NULL);
			}
			for(hpcc::IEdgeSet::const_iterator itr = m_graph->GetAllEdges().begin(); itr != m_graph->GetAllEdges().end(); ++itr)
			{
				itr->get()->SetProperty(SVG_PROP_ELEMENTG, (CUnknown *)NULL);
			}
		}
		else if (m_valid && 0 == e->m_tag.compare("g"))
		{
			if (m_offset.Empty())
			{
				std::string transform = e->m_attr["transform"];
				if (!transform.empty())
				{
					static const char * const TRANSLATE = "translate(";
					static int TRANSLATE_SIZE = strlen(TRANSLATE);
					const char * start = strstr(transform.c_str(), TRANSLATE);
					const char * mid = strstr(start, " ");
					const char * end = strstr(mid, ")");
					if (start && mid && end)
					{
						char x[8], y[8];
						memset(x, 0, 8);
						memset(y, 0, 8);
						strncpy(x, start + TRANSLATE_SIZE, mid - (start + TRANSLATE_SIZE));
						strncpy(y, mid + 1, end - (mid + 1));
						m_offset = CreatePointD(x, y, PointD(), DOT_DPI);
					}
				}
			}

			GRAPH_TYPE type = GRAPH_TYPE_UNKNOWN;
			if (e->m_attr["class"].compare("graph") == 0)
				type = GRAPH_TYPE_GRAPH;
			else if (e->m_attr["class"].compare("cluster") == 0)
				type = GRAPH_TYPE_CLUSTER;
			else if (e->m_attr["class"].compare("node") == 0)
				type = GRAPH_TYPE_VERTEX;
			else if (e->m_attr["class"].compare("edge") == 0)
				type = GRAPH_TYPE_EDGE;
			m_currentItem = m_graph->GetGraphItem(type, e->m_attr["id"]);
			if (!m_currentItem) {
				throw ParseException();
			}
			m_currentElementG = new ElementG();
			m_currentItem->SetProperty(SVG_PROP_ELEMENTG, m_currentElementG);
		}

		return;
	}

	virtual void OnEndElement(const XML_Char *pszName)
	{
		CElementPtr e = m_stack.top();
		if (0 == e->m_tag.compare("svg"))
		{
		}

		if (m_valid == true && 0 == e->m_tag.compare("g"))
		{
		}
		else if (0 == e->m_tag.compare("title"))
		{
		}
		else if (0 == e->m_tag.compare("ellipse"))
		{
			assert(m_currentElementG);
			m_currentElementG->m_ellipses.push_back(new Ellipse(e->m_attr["fill"], e->m_attr["stroke"], e->m_attr["cx"], e->m_attr["cy"], e->m_attr["rx"], e->m_attr["ry"], m_offset));
		}
		else if (0 == e->m_tag.compare("path"))
		{
			assert(m_currentElementG);
			m_currentElementG->m_paths.push_back(new Path(e->m_attr["fill"], e->m_attr["stroke"], e->m_attr["stroke-dasharray"], e->m_attr["stroke-width"], e->m_attr["d"], m_offset));
		}
		else if (0 == e->m_tag.compare("polyline"))
		{
			assert(m_currentElementG);
			m_currentElementG->m_polylines.push_back(new Polygon(e->m_attr["fill"], e->m_attr["stroke"], e->m_attr["points"], m_offset));
		}
		else if (0 == e->m_tag.compare("polygon"))
		{
			assert(m_currentElementG);
			m_currentElementG->m_polygons.push_back(new Polygon(e->m_attr["fill"], e->m_attr["stroke"], e->m_attr["points"], m_offset));
		}
		else if (0 == e->m_tag.compare("text"))
		{
			assert(m_currentElementG);
			m_currentElementG->m_lines.push_back(new Text(e->m_attr["text-anchor"], e->m_attr["x"], e->m_attr["y"], e->m_attr["font-family"], e->m_attr["font-size"], e->m_attr["fill"], e->GetContent(), m_offset));
		}
		else
		{
		}

		CStackParser::OnEndElement(pszName);
		return;
	}

};

RectD GetBoundingRect(IGraphItem * item) 
{
	if (item)
	{
		if (ElementG * eg = GetElementG(item))
			return eg->GetBoundingBox();
	}
	return RectD();
}

void FixSubgraphSizes(ICluster * cluster, RectD  & parentRect)
{
	RectD childRect;
	for(IClusterSet::const_iterator itr = cluster->GetClusters().begin(); itr != cluster->GetClusters().end(); ++itr)
	{
		std::string cluster;
		FixSubgraphSizes(itr->get(), childRect);
	}

	for(IVertexSet::const_iterator itr = cluster->GetVertices().begin(); itr != cluster->GetVertices().end(); ++itr)
	{
		if (childRect.IsEmptyArea())
			childRect = GetBoundingRect(itr->get());
		else
			childRect.Union(GetBoundingRect(itr->get()));
	}

	//if (!GetBoundingRect(cluster).Contains(childRect))
	{
		if (childRect.IsEmptyArea())
			childRect = GetBoundingRect(cluster);
		else
			childRect.Union(GetBoundingRect(cluster));


		if (ElementG * eg = GetElementG(cluster))
		{
			assert(eg->m_polygons.size() == 1);
			if (eg->m_polygons.size() == 1)
			{
				eg->m_polygons[0]->m_points.clear();
				eg->m_polygons[0]->SetBoundingBox(RectD());
				eg->m_polygons[0]->m_points.push_back(PointD(childRect.GetLeft(), childRect.GetBottom()));
				eg->m_polygons[0]->m_points.push_back(PointD(childRect.GetLeft(), childRect.GetTop()));
				eg->m_polygons[0]->m_points.push_back(PointD(childRect.GetRight(), childRect.GetTop()));
				eg->m_polygons[0]->m_points.push_back(PointD(childRect.GetRight(), childRect.GetBottom()));
				eg->m_polygons[0]->m_points.push_back(PointD(childRect.GetLeft(), childRect.GetBottom()));
			}
			//eg->SetBoundingBox(childRect);
			eg->CalcBoundingBox();
		}

		//childRect.Union(GetBoundingRect(cluster));
		//ElementGPtr elementG = new ElementG(childRect);
		//cluster->SetProperty(SVG_PROP_ELEMENTG, elementG);
	}
	if (parentRect.IsEmptyArea())
		parentRect = childRect;
	else
		parentRect.Union(childRect);
}

GRAPHDB_API bool MergeSVG(IGraph * graph, const std::string & svg)
{
	CSvgParser parser(graph);
	parser.Create();
	try
	{
		parser.Parse(svg.c_str(), svg.length());
	} catch (ParseException & e) {
		return false;
	}
	RectD childRect;
	FixSubgraphSizes(graph, childRect);
	return true;
}

GRAPHDB_API ElementG * GetElementG(IGraphItem * item)
{
	CUnknown * tmpProp = item->GetPropertyCUnknown(hpcc::SVG_PROP_ELEMENTG);
	if (tmpProp)
		return reinterpret_cast<hpcc::ElementG * >(tmpProp);
	
	RectD boundingBox;
	if (const ICluster * cluster = dynamic_cast<const ICluster *>(item))	//  Not all layouts support clusters!
	{
		bool first = true;
		for(IClusterSet::const_iterator itr = cluster->GetClusters().begin(); itr != cluster->GetClusters().end(); ++itr)
		{
			ElementGPtr elementG = GetElementG(*itr);
			if (first)
			{
				first = false;
				boundingBox = elementG->GetBoundingBox();
			}
			else
				boundingBox.Union(elementG->GetBoundingBox());
		}

		for(IVertexSet::const_iterator itr = cluster->GetVertices().begin(); itr != cluster->GetVertices().end(); ++itr)
		{
			ElementGPtr elementG = GetElementG(*itr);
			if (first)
			{
				first = false;
				boundingBox = elementG->GetBoundingBox();
			}
			else
				boundingBox.Union(elementG->GetBoundingBox());
		}
	}
	ElementGPtr elementG = new ElementG(boundingBox);
	item->SetProperty(SVG_PROP_ELEMENTG, elementG);
	return elementG;
}
}
