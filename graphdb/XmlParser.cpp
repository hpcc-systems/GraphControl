#include "Platform.h"

#include <string.h>

#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp> 

#include "SaxParser.h"
#include "XmlParser.h"
#include "GraphGraph.h"

namespace ln
{
//  ===========================================================================
typedef std::map<std::string, IVertexPtr> StringVertexMap;
typedef StringStringMap StringStringMap;

typedef std::deque<IClusterPtr> ClusterStack;
typedef std::deque<StringStringMap> CellDataStack;
class CXmlParser : public CStackParser
{
protected:
	CGraphPtr m_graph;
	ClusterStack m_clusterStack;
	CellDataStack m_cellDataStack;

	bool m_vertices;
	bool m_inSchema;

public:

	CXmlParser(CGraph * graph, bool vertices) : m_graph(graph), m_vertices(vertices)
	{
		m_inSchema = false;
	}

	const std::string & constGet(const StringStringMap & map, const std::string & key, const std::string & defVal  = "")
	{
		StringStringMap::const_iterator found = map.find(key);
		if (found == map.end())
			return defVal;
		return found->second;
	}

	virtual void OnStartElement(const XML_Char *pszName, const XML_Char **papszAttrs)
	{
		CStackParser::OnStartElement(pszName, papszAttrs);

		CElementPtr e = m_stack.top();
		if (e->m_tag.compare("XmlSchema") == 0)
		{
			m_inSchema = true;
		}
		else if (!m_inSchema)
		{
			if (e->m_tag.compare("Dataset") == 0)
			{
				if (m_vertices)
				{
					if (m_clusterStack.size())
						m_clusterStack.push_front(m_graph->CreateCluster(m_clusterStack.begin()->get()));
					else
						m_clusterStack.push_front(m_graph->CreateCluster());
				}
			}
			else if (e->m_tag.compare("Row") == 0)
				m_cellDataStack.push_front(StringStringMap());
		}

		return;
	}

	bool equals(const char * str, const char * cmp)
	{
		if (str == NULL)
			return false;
		return boost::algorithm::equals(str, cmp);
	}

	virtual void OnEndElement(const XML_Char *pszName)
	{
		CElementPtr e = m_stack.top();
		if (e->m_tag.compare("XmlSchema") == 0)
		{
			m_inSchema = false;
		}
		else if (!m_inSchema)
		{
			if (e->m_tag.compare("Dataset") == 0)
			{
				if (m_vertices)
					m_clusterStack.pop_front();
			}
			else if (e->m_tag.compare("Row") == 0)
			{
				IGraphItem * gi = NULL;
				if (m_vertices)
				{
					if (m_clusterStack.size())
						gi = m_graph->CreateVertex(m_clusterStack.begin()->get());
					else
						gi = m_graph->CreateVertex();
					assert(m_cellDataStack.size());
					m_graph->SetExternalID(GRAPH_TYPE_VERTEX, (*m_cellDataStack.begin())["vertex_id"], gi);
				}
				else
				{
					std::string v_from_str = (*m_cellDataStack.begin())["edge_from_id"];
					std::string v_to_str = (*m_cellDataStack.begin())["edge_to_id"];
					if (v_from_str.size() && v_to_str.size())
					{
						IVertex * v_from = m_graph->GetVertex(v_from_str, true);
						IVertex * v_to = m_graph->GetVertex(v_to_str, true);
						if (v_from && v_to)
						{
							gi = m_graph->CreateEdge(v_from, v_to);
						}
							//if (!(*m_cellDataStack.begin())["edge_id"].empty())
							//	m_graph->SetExternalID(GRAPH_TYPE_EDGE, (*m_cellDataStack.begin())["edge_id"], gi);
					}
				}

				if (gi)
				{
					for(StringStringMap::const_iterator itr = m_cellDataStack.begin()->begin(); itr != m_cellDataStack.begin()->end(); ++itr)
					{
						if (boost::algorithm::equals(itr->first, "vertex_id"))
							gi->SetProperty(DOT_ID, itr->second.c_str());
						else if (boost::algorithm::equals(itr->first, "vertex_label"))
							gi->SetProperty(DOT_LABEL, itr->second.c_str());
						else if (boost::algorithm::equals(itr->first, "vertex_shape"))
							gi->SetProperty(DOT_VERTEX_SHAPE, itr->second.c_str());
						else if (boost::algorithm::equals(itr->first, "vertex_color"))
							gi->SetProperty(DOT_VERTEX_COLOR, itr->second.c_str());
						else if (boost::algorithm::equals(itr->first, "vertex_style"))
							gi->SetProperty(DOT_VERTEX_STYLE, itr->second.c_str());
						else if (boost::algorithm::equals(itr->first, "vertex_fillcolor"))
							gi->SetProperty(DOT_VERTEX_FILLCOLOR, itr->second.c_str());
						else if (boost::algorithm::equals(itr->first, "edge_from_id"))
							gi->SetProperty(DOT_EDGE_FROMID, itr->second.c_str());
						else if (boost::algorithm::equals(itr->first, "edge_to_id"))
							gi->SetProperty(DOT_EDGE_TOID, itr->second.c_str());
						else if (boost::algorithm::equals(itr->first, "edge_label"))
							gi->SetProperty(DOT_LABEL, itr->second.c_str());
						else if (boost::algorithm::equals(itr->first, "edge_weight"))
							gi->SetProperty(DOT_EDGE_WEIGHT, itr->second.c_str());
						else if (boost::algorithm::equals(itr->first, "edge_penwidth"))
							gi->SetProperty(DOT_EDGE_PENWIDTH, itr->second.c_str());
						else if (boost::algorithm::equals(itr->first, "edge_arrowhead"))
							gi->SetProperty(DOT_EDGE_ARROWHEAD, itr->second.c_str());
						else if (boost::algorithm::equals(itr->first, "edge_arrowtail"))
							gi->SetProperty(DOT_EDGE_ARROWTAIL, itr->second.c_str());
						else if (boost::algorithm::equals(itr->first, "edge_color"))
							gi->SetProperty(DOT_EDGE_COLOR, itr->second.c_str());
						else if (boost::algorithm::equals(itr->first, "edge_style"))
							gi->SetProperty(DOT_EDGE_STYLE, itr->second.c_str());
						else
							gi->SetProperty(itr->first.c_str(), itr->second.c_str());
					}
				}
				m_cellDataStack.pop_front();
			}
			else
			{
				assert(m_cellDataStack.size());
				m_cellDataStack.begin()->operator[](e->m_tag) = e->GetContent();
			}
		}

		CStackParser::OnEndElement(pszName);
		return;
	}
};

GRAPHDB_API bool LoadXML(IGraph * graph, const std::string & verticesXML, const std::string & edgesXML)
{
	CXmlParser vparser(static_cast<CGraph *>(graph), true);
	vparser.Create();
	bool retVal = vparser.Parse(verticesXML.c_str(), verticesXML.length());
	if (retVal)
	{
		CXmlParser eparser(static_cast<CGraph *>(graph), false);
		eparser.Create();
		retVal = eparser.Parse(edgesXML.c_str(), edgesXML.length());
	}
	return retVal;
}
//  ===========================================================================
typedef std::map<std::string, IEdgePtr> StringEdgeMap;
class CXml2Parser : public CStackParser
{
public:
	CGraphPtr m_graph;
	std::string m_attr;
	StringVertexMap m_vertices;
	StringEdgeMap m_edges;

	CXml2Parser(CGraph * graph) : m_graph(graph)
	{
	}

	virtual void OnStartElement(const XML_Char *pszName, const XML_Char **papszAttrs)
	{
		CStackParser::OnStartElement(pszName, papszAttrs);

		CElementPtr e = m_stack.top();

		switch (m_stack.size())
		{
		case 2:
			{
				m_attr = e->m_attr["module"] + "." + e->m_attr["name"];
				StringVertexMap::const_iterator found = m_vertices.find(m_attr);
				if (found == m_vertices.end())
				{
					m_vertices[m_attr] = m_graph->CreateVertex();
					m_vertices[m_attr]->SetProperty(DOT_LABEL, m_attr.c_str());
				}
			}
			break;

		case 3:
			break;
		}
	}

	virtual void OnEndElement(const XML_Char *pszName)
	{
		CElementPtr e = m_stack.top();

		switch (m_stack.size())
		{
		case 2:
			break;

		case 3:
			{
				std::string attr = e->m_attr["module"] + "." + e->m_attr["name"];
				StringVertexMap::const_iterator found = m_vertices.find(attr);
				if (found == m_vertices.end())
				{
					m_vertices[attr] = m_graph->CreateVertex();
					m_vertices[attr]->SetProperty(DOT_LABEL, attr.c_str());
				}
				std::string edge = m_attr + "->" + attr;
				StringEdgeMap::const_iterator foundE = m_edges.find(edge);
				if (foundE == m_edges.end())
				{
					m_edges[edge] = m_graph->CreateEdge(m_vertices[m_attr], m_vertices[attr]);
				}
			}
			break;
		}
		CStackParser::OnEndElement(pszName);
		return;
	}
};

GRAPHDB_API bool LoadXML2(IGraph * graph, const std::string & xml)
{
	CXml2Parser vparser(static_cast<CGraph *>(graph));
	vparser.Create();
	bool retVal = vparser.Parse(xml.c_str(), xml.length());
	return retVal;
}
}
