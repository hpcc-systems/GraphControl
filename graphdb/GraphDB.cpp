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

class CDotClusterBuilder : public IClusterVisitor
{
public:
	std::_tstring m_str;

	void ItemVisited(ICluster * cluster)
	{
	}
};

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

const char * WriteDOT(const IGraph * graph, std::string & dot)
{
	dot.clear();
	std::string content;
	WalkClusters(graph, content, 0);

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

std::string xmlEncode(const std::string & text)
{
	std::string retVal = text;
	boost::algorithm::replace_all(retVal, "&", "&amp;");
	boost::algorithm::replace_all(retVal, "<", "&lt;");
	boost::algorithm::replace_all(retVal, ">", "&gt;");
	boost::algorithm::replace_all(retVal, "\n", "&#10;");
	return retVal;
}

enum DIRECTION
{
	DIRECTION_UNKNOWN = 0,
	DIRECTION_IN,
	DIRECTION_OUT,
	DIRECTION_LAST
};
const char * WriteLocalisedXGMML(const IGraph * graph, const IEdge * edge, IGraphItemSet & addedItems, std::string & xgmml, DIRECTION dir, int depth);

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

const char * WriteLocalisedXGMML(const IGraph * graph, const IVertex * vertex, IGraphItemSet & addedItems, std::string & xgmml, DIRECTION dir, int depth)
{
	std::string vertexStr;
	BuildVertexString(vertex, vertexStr, depth == 0);

	if (addedItems.find((IGraphItem *)vertex) == addedItems.end())
	{
		addedItems.insert((IGraphItem *)vertex);
		xgmml += vertexStr;
	}
	else
		return xgmml.c_str();

	if (depth == 0)
		return xgmml.c_str();

	if(dir == DIRECTION_UNKNOWN || dir == DIRECTION_IN)
	{
		IEdgeSet inEdges = vertex->GetInEdges();
		for(IEdgeSet::const_iterator itr = inEdges.begin(); itr != inEdges.end(); ++itr)
			WriteLocalisedXGMML(graph, itr->get(), addedItems, xgmml, dir == DIRECTION_UNKNOWN ? DIRECTION_IN : dir, depth);
	}
	if(dir == DIRECTION_UNKNOWN || dir == DIRECTION_OUT)
	{
		IEdgeSet outEdges = vertex->GetOutEdges();
		for(IEdgeSet::const_iterator itr = outEdges.begin(); itr != outEdges.end(); ++itr)
			WriteLocalisedXGMML(graph, itr->get(), addedItems, xgmml, dir == DIRECTION_UNKNOWN ? DIRECTION_OUT : dir, depth);
	}

	return xgmml.c_str();
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

const char * WriteLocalisedXGMML(const IGraph * graph, const IEdge * edge, IGraphItemSet & addedItems, std::string & xgmml, DIRECTION dir, int depth)
{
	if(dir == DIRECTION_UNKNOWN || dir == DIRECTION_IN)
		WriteLocalisedXGMML(graph, edge->GetFromVertex(), addedItems, xgmml, dir == DIRECTION_UNKNOWN ? DIRECTION_IN : dir, depth - 1);
	if(dir == DIRECTION_UNKNOWN || dir == DIRECTION_OUT)
		WriteLocalisedXGMML(graph, edge->GetToVertex(), addedItems, xgmml, dir == DIRECTION_UNKNOWN ? DIRECTION_OUT : dir, depth - 1);

	std::string edgeStr;
	BuildEdgeString(edge, edgeStr);
	if (addedItems.find((IGraphItem *)edge) == addedItems.end())
	{
		addedItems.insert((IGraphItem *)edge);
		xgmml += edgeStr;
	}
	return xgmml.c_str();
}

bool decendent(const ICluster * cluster, const ICluster * item)
{
	if (item == NULL)
		return false;
	if (cluster == item)
		return true;
	return decendent(cluster, item->GetParent());
}

const char * WriteLocalisedXGMML(const IGraph * graph, const ICluster * cluster, IGraphItemSet & addedItems, std::string & xgmml)
{
	std::string clusterXgmml, externalVertices;
	clusterXgmml += (boost::format("<node id=\"%1%\"><att><graph>") % cluster->GetProperty("id")).str();
	for(IVertexSet::const_iterator itr = cluster->GetVertices().begin(); itr != cluster->GetVertices().end(); ++itr)
	{
		std::string vertexStr, attrStr;
		BuildVertexString(itr->get(), vertexStr, false);
		if (addedItems.find(itr->get()) == addedItems.end())
		{
			addedItems.insert(itr->get());
			clusterXgmml += vertexStr;
		}
	}
	for(IClusterSet::const_iterator itr = cluster->GetClusters().begin(); itr != cluster->GetClusters().end(); ++itr)
		WriteLocalisedXGMML(graph, itr->get(), addedItems, clusterXgmml);
	for(IVertexSet::const_iterator v_itr = cluster->GetVertices().begin(); v_itr != cluster->GetVertices().end(); ++v_itr)
	{
		IEdgeSet inEdges = v_itr->get()->GetInEdges();
		for(IEdgeSet::const_iterator itr = inEdges.begin(); itr != inEdges.end(); ++itr)
		{
			IVertex * from = itr->get()->GetFromVertex();
			if (!decendent(cluster, from->GetParent()))
				WriteLocalisedXGMML(graph, from, addedItems, externalVertices, DIRECTION_IN, 0);

			std::string edgeStr;
			BuildEdgeString(itr->get(), edgeStr);
			if (addedItems.find((IGraphItem *)itr->get()) == addedItems.end())
			{
				addedItems.insert((IGraphItem *)itr->get());
				clusterXgmml += edgeStr;
			}
		}

		IEdgeSet outEdges = v_itr->get()->GetOutEdges();
		for(IEdgeSet::const_iterator itr = outEdges.begin(); itr != outEdges.end(); ++itr)
		{
			IVertex * to = itr->get()->GetToVertex();
			if (!decendent(cluster, to->GetParent()))
				WriteLocalisedXGMML(graph, to, addedItems, externalVertices, DIRECTION_OUT, 0);

			std::string edgeStr;
			BuildEdgeString(itr->get(), edgeStr);
			if (addedItems.find((IGraphItem *)itr->get()) == addedItems.end())
			{
				addedItems.insert((IGraphItem *)itr->get());
				clusterXgmml += edgeStr;
			}
		}
	}
	clusterXgmml += "</graph></att></node>";
	xgmml += externalVertices + clusterXgmml;
	return xgmml.c_str();
}

const char * WriteLocalisedXGMML(const IGraph * graph, std::string & xgmml)
{
	return xgmml.c_str();
}

GRAPHDB_API const char * WriteLocalisedXGMML(const IGraph * graph, const IGraphItem * item, std::string & xgmml)
{
	IGraphItemSet addedItems;
	if (const IVertex * vertex = dynamic_cast<const IVertex *>(item))
		WriteLocalisedXGMML(graph, vertex, addedItems, xgmml, DIRECTION_UNKNOWN, 3);
	else if (const IEdge * edge = dynamic_cast<const IEdge *>(item))
		WriteLocalisedXGMML(graph, edge, addedItems, xgmml, DIRECTION_UNKNOWN, 3);
	else if (const IGraph * graph = dynamic_cast<const IGraph *>(item))
		WriteLocalisedXGMML(graph, xgmml);
	else if (const ICluster * cluster = dynamic_cast<const ICluster *>(item))
		WriteLocalisedXGMML(graph, cluster, addedItems, xgmml);
	return xgmml.c_str();
}

}