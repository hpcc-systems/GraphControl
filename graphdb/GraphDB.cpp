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

void BuildVertexEdgeString(IEdge * e, IVertex * v, const IVertexSet & visibleVertices, IGraphItemSet & addedItems, const ICluster * cluster, std::string & clusterXgmml, std::string & externalVertices)
{
	if (visibleVertices.find(v) == visibleVertices.end())
	{
		if (addedItems.find(v) == addedItems.end())
		{
			addedItems.insert(v);
			std::string vertexStr;
			BuildVertexString(v, vertexStr, true);
			if (decendent(cluster, v->GetParent()))
				clusterXgmml += vertexStr;
			else
				externalVertices += vertexStr;
		}
	}

	if (addedItems.find((IGraphItem *)e) == addedItems.end())
	{
		addedItems.insert((IGraphItem *)e);
		std::string edgeStr;
		BuildEdgeString(e, edgeStr);
		clusterXgmml += edgeStr;
	}
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

void CalcVisibility(const ICluster * rootCluster, const ICluster * cluster, IVertexSet & externalVertices, IEdgeSet & edges, std::string & content)
{
	std::string childContent;
	IVertexSet visibleVertices, pointVertices;
	for(IVertexSet::const_iterator itr = cluster->GetVertices().begin(); itr != cluster->GetVertices().end(); ++itr)
	{
		IVertex * v = itr->get();
		bool v_display = false;
		
		IVertexSet adjacentVertices;
		v->GetAdjacentVertices(adjacentVertices);
		for(IVertexSet::const_iterator adj_itr = adjacentVertices.begin(); adj_itr != adjacentVertices.end(); ++adj_itr)
		{
			IVertex * v_adjacent = adj_itr->get();
			IEdge * e = v->GetEdge(v_adjacent);

			//  Both vertices are inside rootCluster and their edge crosses rootClusters white space.
			if (rootCluster == GetCommonAncestor(v, v_adjacent))
			{
				v_display = true;
				edges.insert(e);
			} //  Main vertex is visible and adjacent vertex is external
			else if (rootCluster == v->GetParent() && !decendent(rootCluster, v_adjacent->GetParent())) 
			{
				v_display = true;
				edges.insert(e);
				externalVertices.insert(v_adjacent);
			} //  both vertices are within a single child cluster of root cluster
			else
			{
			}
		}

		if (v_display)
		{
			std::string vertexStr;
			BuildVertexString(v, vertexStr, v->GetParent() == rootCluster ? false : true);
			childContent += vertexStr;
		}
	}

	for(IClusterSet::const_iterator itr = cluster->GetClusters().begin(); itr != cluster->GetClusters().end(); ++itr)
	{
		CalcVisibility(rootCluster, itr->get(), externalVertices, edges, childContent);
	}

	if (!childContent.empty())
	{
		content += (boost::format("<node id=\"%1%\"><att><graph>") % cluster->GetProperty("id")).str();
		content += childContent;
		content += "</graph></att></node>";
	}
}

const char * WriteLocalisedXGMML(const IGraph * graph, const ICluster * cluster, IGraphItemSet & addedItems, std::string & xgmml)
{
	IVertexSet externalVertices;
	IEdgeSet edges;
	CalcVisibility(cluster, cluster, externalVertices, edges, xgmml);
	for (IVertexSet::const_iterator itr = externalVertices.begin(); itr != externalVertices.end(); ++itr)
	{
		std::string vertexStr;
		BuildVertexString(itr->get(), vertexStr, true);
		xgmml += vertexStr;
	}
	for(IEdgeSet::const_iterator itr = edges.begin(); itr != edges.end(); ++itr)
	{
		std::string edgeStr;
		BuildEdgeString(itr->get(), edgeStr);
		xgmml += edgeStr;
	}
	return xgmml.c_str();
}

GRAPHDB_API const char * WriteLocalisedXGMML(const IGraph * graph, const IGraphItem * item, std::string & xgmml)
{
	IGraphItemSet addedItems;
	if (const IVertex * vertex = dynamic_cast<const IVertex *>(item))
		WriteLocalisedXGMML(graph, vertex, addedItems, xgmml, DIRECTION_UNKNOWN, 3);
	else if (const IEdge * edge = dynamic_cast<const IEdge *>(item))
		WriteLocalisedXGMML(graph, edge, addedItems, xgmml, DIRECTION_UNKNOWN, 3);
	else if (const ICluster * cluster = dynamic_cast<const ICluster *>(item))
		WriteLocalisedXGMML(graph, cluster, addedItems, xgmml);
	return xgmml.c_str();
}

}