#include "Platform.h"

#include <string.h>

#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

#include "SaxParser.h"
#include "GraphDB.h"
#include "SvgShapes.h"
#include "SvgParser.h"

namespace ln
{
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
			RectD viewBox = CreateRectD(e->m_attr["viewBox"], PointD());
			m_graph->SetProperty(SVG_PROP_VIEWBOX_X, viewBox.x);
			m_graph->SetProperty(SVG_PROP_VIEWBOX_Y, viewBox.y);
			m_graph->SetProperty(SVG_PROP_VIEWBOX_W, viewBox.Width);
			m_graph->SetProperty(SVG_PROP_VIEWBOX_H, viewBox.Height);
			for(ln::IClusterSet::const_iterator itr = m_graph->GetAllClusters().begin(); itr != m_graph->GetAllClusters().end(); ++itr)
			{
				itr->get()->SetProperty(SVG_PROP_ELEMENTG, (CUnknown *)NULL);
			}
			for(ln::IVertexSet::const_iterator itr = m_graph->GetAllVertices().begin(); itr != m_graph->GetAllVertices().end(); ++itr)
			{
				itr->get()->SetProperty(SVG_PROP_ELEMENTG, (CUnknown *)NULL);
			}
			for(ln::IEdgeSet::const_iterator itr = m_graph->GetAllEdges().begin(); itr != m_graph->GetAllEdges().end(); ++itr)
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
					const char * start = strstr(transform.c_str(), "translate(");
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

			unsigned int id = StringToUInt(e->m_attr["id"].c_str());
			if (id)
			{
				m_currentItem = m_graph->GetGraphItem(id);
				m_currentElementG = new ElementG();
				m_currentItem->SetProperty(SVG_PROP_ELEMENTG, m_currentElementG);
			}
			assert(m_currentItem);
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

GRAPHDB_API void MergeSVG(IGraph * graph, const std::string & svg)
{
	CSvgParser parser(graph);
	parser.Create();
	parser.Parse(svg.c_str(), svg.length());
}

GRAPHDB_API ElementG * GetElementG(IGraphItem * item)
{
	CUnknown * tmpProp = item->GetPropertyCUnknown(ln::SVG_PROP_ELEMENTG);
	if (tmpProp)
		return reinterpret_cast<ln::ElementG * >(tmpProp);
	
	RectD boundingBox;
	if (ICluster * cluster = dynamic_cast<ICluster *>(item))	//  Not all layouts support clusters!
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
