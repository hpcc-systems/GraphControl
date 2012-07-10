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

#include "GraphGraph.h"
#include "util.h"
#include "XgmmlParser.h"
#include "DotParser.h"

namespace hpcc
{
GRAPHDB_API IGraph * CreateGraph()
{
	return new CGraph();
}

const char * const GraphTpl = 
"digraph G {\r\n"
"id=\"%1%\";\r\n"
//"pad=\"0.0,0.0\";\r\n"
"graph[fontname=\"Verdana\",fontsize=11,fontcolor=\"#000000\"];\r\n"
"graph[bgcolor=\"#FFFFFF\"];\r\n"
//"graph[nodesep=\"\"];\r\n"
//"graph[ranksep=\".3\"];\r\n"
//"graph[pad=\"0.01, 0.01\"];\r\n"
"graph[rankdir=\"TB\"%2%];\r\n"
"graph[remincross=true];\r\n"
"graph[mclimit=\"2.0\"];\r\n"
//"graph[sep=\"0.1\"];\r\n"
//"graph[overlap=\"scalexy\"];\r\n"
//"graph[smoothing=\"spring\"];\r\n"
//"graph[splines=\"line\"];\r\n"
"\r\n"
"node[fontname=\"Verdana\",fontsize=11,fontcolor=\"#000000\"];\r\n"
"node[shape=\"box\"];\r\n"
//"node[margin=\"0.1,0.05\"];\r\n"
//"node[height=.3];\r\n"
//"node[width=.3];\r\n"
"node[style=\"filled,solid\"];\r\n"
"node[fillcolor=\"#E6E6E6\",color=\"#000000\"];\r\n"
"\r\n"
"edge[fontname=\"Verdana\",fontsize=11,fontcolor=\"#000000\"];\r\n"
"edge[arrowhead=\"normal\"]; \r\n"
"edge[style=\"solid\"];\r\n"
"edge[color=\"#000000\"];\r\n"
"edge[arrowsize=\"1\"];\r\n"
"\r\n"
"%3%\r\n"
"}\r\n";

const char * const ClusterTpl = 
"subgraph cluster_%1% {\r\n"
"id=\"%1%\";\r\n"
"label=\"%2%\";\r\n"
"fontname=\"Verdana\";\r\n"
"fontsize=\"11\";\r\n"
"fontcolor=\"#808080\";\r\n"
"style=\"%4%filled,solid\";\r\n"
"fillcolor=\"#FFFFFF\";\r\n"
"color=\"#000000\";\r\n"
"labeljust=\"l\";\r\n"
"\r\n"
"%3%\r\n"
"}\r\n";

const char * const PropTpl = 
" %1%=\"%2%\"";

const char * const VertexTpl = 
"%1%[id=\"%1%\" label=\"%2%\"%3%];\r\n";

const char * const EdgeTpl = 
"%1%->%2%[id=\"%3%\" label=\"%4%\"%5%];\r\n";

void WalkClusters(const ICluster * cluster, std::string & dot, int depth)
{
	std::string content;
	for(IClusterSet::const_iterator itr = cluster->GetClusters().begin(); itr != cluster->GetClusters().end(); ++itr)
	{
		std::string cluster;
		WalkClusters(itr->get(), cluster, depth + 1);
		content += cluster;
	}

	for(IVertexSet::const_iterator itr = cluster->GetVertices().begin(); itr != cluster->GetVertices().end(); ++itr)
	{
		IVertex * v = itr->get();
		if (v->GetPropertyCUnknown(DOT_PROP_CDOTITEM))
		{
			CDotItem * dotItem = (CDotItem *)v->GetPropertyCUnknown(DOT_PROP_CDOTITEM);
			content += dotItem->ToDot(v->GetIDString(), "");
		}
		else 
		{
			std::string props;
			if (v->HasPropertyString(DOT_VERTEX_SHAPE))
				props += (boost::format(PropTpl) % "shape" % v->GetPropertyString(DOT_VERTEX_SHAPE)).str();
			if (v->HasPropertyString(DOT_VERTEX_COLOR))
				props += (boost::format(PropTpl) % "color" % v->GetPropertyString(DOT_VERTEX_COLOR)).str();
			if (v->HasPropertyString(DOT_VERTEX_FILLCOLOR))
				props += (boost::format(PropTpl) % "fillcolor" % v->GetPropertyString(DOT_VERTEX_FILLCOLOR)).str();
			if (v->HasPropertyString(DOT_VERTEX_STYLE))
				props += (boost::format(PropTpl) % "style" % v->GetPropertyString(DOT_VERTEX_STYLE)).str();

			content += (boost::format(VertexTpl) % v->GetIDString() % v->GetPropertyString(DOT_LABEL) % props.c_str()).str();
		}
	}

	if (depth > 0)
	{
		if (cluster->GetPropertyCUnknown(DOT_PROP_CDOTITEM))
		{
			CDotItem * dotItem = (CDotItem *)cluster->GetPropertyCUnknown(DOT_PROP_CDOTITEM);
			dot += dotItem->ToDot(cluster->GetIDString(), content);
		}
		else
		{
			std::string label = cluster->GetPropertyString(DOT_LABEL);
			if (label.empty())
				label = cluster->GetPropertyString(DOT_ID);
			dot += (boost::format(ClusterTpl) % cluster->GetIDString() % label % content % "").str();
		}
	}
	else
	{
		dot = content;
	}
}

void WalkEdges(const IGraph * graph, std::string & content)
{
	for(IEdgeSet::const_iterator itr = graph->GetAllEdges().begin(); itr != graph->GetAllEdges().end(); ++itr)
	{
		IEdge * e = itr->get();
		if (e->GetPropertyCUnknown(DOT_PROP_CDOTITEM))
		{
			CDotItem * dotItem = (CDotItem *)e->GetPropertyCUnknown(DOT_PROP_CDOTITEM);
			content += dotItem->ToDot(e->GetIDString(), "");
		}
		else
		{
			IVertex * from = e->GetFromVertex();
			IVertex * to = e->GetToVertex();
			if (from->GetPropertyInt(XGMML_GLOBAL_USAGE_COUNT) > 0)
				continue;

			//if (from->GetPropertyBool(XGMML_IS_SPILL) && (from->GetParent() != to->GetParent()) && from->GetOutEdgeCount() > 1)
			//	continue;

			std::string props;
			if (e->HasPropertyString(DOT_EDGE_WEIGHT))
				props += (boost::format(PropTpl) % "weight" % e->GetPropertyString(DOT_EDGE_WEIGHT)).str();

			if (e->HasPropertyString(DOT_EDGE_PENWIDTH))
				props += (boost::format(PropTpl) % "penwidth" % e->GetPropertyString(DOT_EDGE_PENWIDTH)).str();

			if (e->HasPropertyString(DOT_EDGE_ARROWHEAD))
				props += (boost::format(PropTpl) % "arrowhead" % e->GetPropertyString(DOT_EDGE_ARROWHEAD)).str();

			if (e->HasPropertyString(DOT_EDGE_ARROWTAIL))
			{
				props += (boost::format(PropTpl) % "arrowtail" % e->GetPropertyString(DOT_EDGE_ARROWTAIL)).str();
				props += (boost::format(PropTpl) % "dir" % (e->HasPropertyString(DOT_EDGE_ARROWHEAD) ? "both" : "back")).str();
			}

			if (e->HasPropertyString(DOT_EDGE_COLOR))
				props += (boost::format(PropTpl) % "color" % e->GetPropertyString(DOT_EDGE_COLOR)).str();

			if (e->HasPropertyString(DOT_EDGE_STYLE))
				props += (boost::format(PropTpl) % "style" % e->GetPropertyString(DOT_EDGE_STYLE)).str();

			content += (boost::format(EdgeTpl) % from->GetIDString() % to->GetIDString() % e->GetIDString() % e->GetPropertyString(DOT_LABEL) % props.c_str()).str();
		}
	}
}

const char * WriteDOT(const IGraph * graph, std::string & dot)
{
	dot.clear();
	std::string content;
	WalkClusters(graph, content, 0);
	WalkEdges(graph, content);

	std::string layout = graph->GetPropertyString(PROP_LAYOUT);
	std::string props;
	if (boost::algorithm::equals(layout, "neato"))
		props += (boost::format(PropTpl) % "overlap" % "scale").str();
	else if (boost::algorithm::equals(layout, "twopi"))
		props += (boost::format(PropTpl) % "overlap" % "scale").str();
	else if (boost::algorithm::equals(layout, "circo"))
		props += (boost::format(PropTpl) % "overlap" % "compress").str();

	if (graph->GetPropertyCUnknown(DOT_PROP_CDOTITEM))  
	{
		CDotItem * dotItem = (CDotItem *)graph->GetPropertyCUnknown(DOT_PROP_CDOTITEM);
		dot = dotItem->ToDot(graph->GetIDString(), content);
	}
	else
	{
		dot = (boost::format(GraphTpl) % graph->GetIDString() % props.c_str() % content).str();
	}
	return dot.c_str();
}

//  ===========================================================================

std::string xmlEncode(const std::string & text) 
{ 
	std::string retVal; 
	retVal.reserve(text.size()); 
	for(size_t pos = 0; pos != text.size(); ++pos) 
	{ 
		switch(text[pos]) 
		{ 
			case '&':  retVal.append("&amp;");		break; 
			case '\"': retVal.append("&quot;");		break; 
			case '\'': retVal.append("&apos;");		break; 
			case '<':  retVal.append("&lt;");		break; 
			case '>':  retVal.append("&gt;");		break;
			case '\n':  retVal.append("&#10;");		break;
			case '\r':  retVal.append("&#13;");		break;
			default:   retVal.append(1, text[pos]);	break; 
		} 
	} 
	return retVal;
}

const char * BuildVertexString(const IVertex * vertex, std::string &vertexStr, bool isPoint)
{
	std::string attrStr, propsStr;
	StringStringMap props;
	vertex->GetProperties(props);
	for(StringStringMap::const_iterator itr = props.begin(); itr != props.end(); ++itr)
	{
		if (isPoint && boost::algorithm::iequals(itr->first, "_kind"))
			propsStr += "<att name=\"_kind\" value=\"point\"/>";
		else if (boost::algorithm::iequals(itr->first, "id") || boost::algorithm::iequals(itr->first, "label"))
			attrStr += (boost::format(" %1%=\"%2%\"") % itr->first % xmlEncode(itr->second)).str();
		else
			propsStr += (boost::format("<att name=\"%1%\" value=\"%2%\"/>") % itr->first % xmlEncode(itr->second)).str();
	}

	vertexStr = (boost::format("<node%1%>%2%</node>") % attrStr % propsStr).str();
	return vertexStr.c_str();
}

const char * BuildEdgeString(const IEdge * edge, std::string &edgeStr)
{
	std::string attrStr, propsStr;
	StringStringMap props;
	edge->GetProperties(props);
	for(StringStringMap::const_iterator itr = props.begin(); itr != props.end(); ++itr)
	{
		if (boost::algorithm::iequals(itr->first, "id") ||
			boost::algorithm::iequals(itr->first, "label") ||
			boost::algorithm::iequals(itr->first, "source") ||
			boost::algorithm::iequals(itr->first, "target"))
			attrStr += (boost::format(" %1%=\"%2%\"") % itr->first % xmlEncode(itr->second)).str();
		else
			propsStr += (boost::format("<att name=\"%1%\" value=\"%2%\"/>") % itr->first % xmlEncode(itr->second)).str();
	}

	edgeStr = (boost::format("<edge%1%>%2%</edge>") % attrStr % propsStr).str();
	return edgeStr.c_str();
}

typedef std::vector<IClusterPtr> IClusterVector;
void GetAncestors(IVertex * v, IClusterVector & ancestors)
{
	ICluster * parent = v->GetParent();
	while (parent)
	{
		ancestors.push_back(parent);
		parent = parent->GetParent();
	}
}

ICluster * GetCommonAncestor(IVertex * v1, IVertex * v2)
{
	IClusterVector v1_ancestors, v2_ancestors;
	GetAncestors(v1, v1_ancestors);
	GetAncestors(v2, v2_ancestors);
	IClusterVector::const_reverse_iterator finger1 = v1_ancestors.rbegin();
	IClusterVector::const_reverse_iterator finger2 = v2_ancestors.rbegin();
	ICluster * retVal = NULL;
	while(finger1 != v1_ancestors.rend() && finger2 != v2_ancestors.rend() && finger1->get() == finger2->get()) {
		retVal = finger1->get();
		++finger1;
		++finger2;
	}
	return retVal;
}

ICluster * GetCommonAncestor(IEdge * e)
{
	return GetCommonAncestor(e->GetFromVertex(), e->GetToVertex());
}

bool isAncestor(const ICluster * ancestor, const ICluster * descendent)
{
	const ICluster * parent = descendent;
	while (parent)
	{
		if (parent == ancestor)
			return true;
		parent = parent->GetParent();
	}
	return false;
}

class CLocalisedXGMMLWriter : public IClusterVisitor, public IVertexVisitor, public IEdgeVisitor
{
public: 
	const IGraph * m_graph;

	IVertexSet m_visibleVertices;
	IVertexSet m_semiVisibleVertices;
	IEdgeSet m_visibleEdges;
	IClusterSet m_visibleClusters;

public:
	std::string m_xgmml;


	CLocalisedXGMMLWriter(const IGraph * graph) : m_graph(graph)
	{
	}

	void CalcVisibility(const IGraphItemSet & items, int localisationDepth, int localisationDistance)
	{
		for (IGraphItemSet::const_iterator itr = items.begin(); itr != items.end(); ++itr)
		{
			if (const IVertex * vertex = dynamic_cast<const IVertex *>(itr->get()))
			{
				CalcInVertexVisibility(vertex, localisationDistance);
				CalcOutVertexVisibility(vertex, localisationDistance);
			}
			else if (const IEdge * edge = dynamic_cast<const IEdge *>(itr->get()))
			{
				CalcInVertexVisibility(edge->GetFromVertex(), localisationDistance - 1);
				CalcOutVertexVisibility(edge->GetToVertex(), localisationDistance - 1);
			}
			else if (const ICluster * cluster = dynamic_cast<const ICluster *>(itr->get()))
			{
				CalcClusterVisibility(cluster, localisationDepth);
			}
		}

		CalcVisibility();
	}

	void CalcInVertexVisibility(const IVertex * vertex, int localisationDistance)
	{
		m_visibleVertices.insert(const_cast<IVertex *>(vertex));

		if (localisationDistance > 0)
		{
			for (IEdgeSet::const_iterator itr = vertex->GetInEdges().begin(); itr != vertex->GetInEdges().end(); ++itr)
				CalcInVertexVisibility(itr->get()->GetFromVertex(), localisationDistance - 1);
		}
	}

	void CalcOutVertexVisibility(const IVertex * vertex, int localisationDistance)
	{
		m_visibleVertices.insert(const_cast<IVertex *>(vertex));

		if (localisationDistance > 0)
		{
			for (IEdgeSet::const_iterator itr = vertex->GetOutEdges().begin(); itr != vertex->GetOutEdges().end(); ++itr)
				CalcOutVertexVisibility(itr->get()->GetToVertex(), localisationDistance - 1);
		}
	}

	void CalcClusterVisibility(const ICluster * cluster, int localisationDepth)
	{
		if (localisationDepth <= 0)
			return;

		for (IClusterSet::const_iterator itr = cluster->GetClusters().begin(); itr != cluster->GetClusters().end(); ++itr)
		{
			CalcClusterVisibility(itr->get(), localisationDepth - 1);
		}

		m_visibleClusters.insert(cluster->GetClusters().begin(), cluster->GetClusters().end());
		m_visibleVertices.insert(cluster->GetVertices().begin(), cluster->GetVertices().end());

		//  Calculate edges that pass through the cluster  ---
		for(IEdgeSet::const_iterator itr = m_graph->GetAllEdges().begin(); itr != m_graph->GetAllEdges().end(); ++itr)
		{
			if (itr->get()->GetFromVertex()->GetParent() != itr->get()->GetToVertex()->GetParent() && isAncestor(cluster, GetCommonAncestor(itr->get())))
			{
				m_visibleEdges.insert(itr->get());
			}
		}
	}

	void CalcAncestorVisibility(IVertex * vertex)
	{
		IClusterVector ancestors;
		GetAncestors(vertex, ancestors);
		m_visibleClusters.insert(ancestors.begin(), ancestors.end());
	}

	void CalcVisibility()
	{
		for (IVertexSet::const_iterator itr = m_visibleVertices.begin(); itr != m_visibleVertices.end(); ++itr)
		{
			m_visibleEdges.insert(itr->get()->GetInEdges().begin(), itr->get()->GetInEdges().end());
			m_visibleEdges.insert(itr->get()->GetOutEdges().begin(), itr->get()->GetOutEdges().end());
			CalcAncestorVisibility(itr->get());

		}
		CalcSemiVisibleVertices();
	}
	
	void CalcSemiVisibleVertices()
	{
		assert(m_semiVisibleVertices.empty());
		for(IEdgeSet::const_iterator itr = m_visibleEdges.begin(); itr != m_visibleEdges.end(); ++itr)
		{
			if (m_visibleVertices.find(itr->get()->GetFromVertex()) == m_visibleVertices.end())
			{
				m_semiVisibleVertices.insert(itr->get()->GetFromVertex());
				CalcAncestorVisibility(itr->get()->GetFromVertex());
			} 
			if (m_visibleVertices.find(itr->get()->GetToVertex()) == m_visibleVertices.end())
			{
				m_semiVisibleVertices.insert(itr->get()->GetToVertex());
				CalcAncestorVisibility(itr->get()->GetToVertex());
			}
		}
	}

	void WriteXgmml() 
	{
		((ICluster *)m_graph)->Walk((IClusterVisitor *)this);
		m_graph->Walk((IEdgeVisitor *)this);
	}

	bool ItemVisited(ICluster * cluster)
	{
		if (m_visibleClusters.find(cluster) != m_visibleClusters.end())
		{
			m_xgmml += (boost::format("<node id=\"%1%\"><att><graph>") % cluster->GetProperty("id")).str();
			int xgmmlLen = m_xgmml.length();
			cluster->Walk((IClusterVisitor *) this);
			cluster->Walk((IVertexVisitor *) this);
			if (xgmmlLen == m_xgmml.length()) 
			{	//  Add at least one child otherwise clusters will render as a vertex  ---
				IVertexSet::const_iterator vertex = cluster->GetVertices().begin();
				if (vertex != cluster->GetVertices().end()) 
				{
					std::string vertexString;
					BuildVertexString(vertex->get(), vertexString, true);
					m_xgmml += vertexString;
				}
			}
			m_xgmml += "</graph></att></node>";
		}
		return false;
	}

	void ItemVisited(IVertex * vertex)
	{
		if (m_visibleVertices.find(vertex) != m_visibleVertices.end())
		{
			std::string vertexString;
			BuildVertexString(vertex, vertexString, false);
			m_xgmml += vertexString;
		}
		else if (m_semiVisibleVertices.find(vertex) != m_semiVisibleVertices.end())
		{
			std::string vertexString;
			BuildVertexString(vertex, vertexString, true);
			m_xgmml += vertexString;
		}
	}

	void ItemVisited(IEdge * edge)
	{
		if (m_visibleEdges.find(edge) != m_visibleEdges.end())
		{
			std::string edgeString;
			BuildEdgeString(edge, edgeString);
			m_xgmml += edgeString;
		}
	}
};

GRAPHDB_API const char * WriteLocalisedXGMML(const IGraph * graph, const IGraphItemSet & items, int localisationDepth, int localisationDistance, std::string & xgmml)
{
	CLocalisedXGMMLWriter xgmmlWriter(graph);
	xgmmlWriter.CalcVisibility(items, localisationDepth, localisationDistance);
	xgmmlWriter.WriteXgmml();
	xgmml = xgmmlWriter.m_xgmml;
	return xgmml.c_str();
}

}