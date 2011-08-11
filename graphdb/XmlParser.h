#pragma once

#include "GraphDB.h"
#include "SvgParser.h"

namespace ln
{
enum DOT_PROP
{
	DOT_PROP_UNKNOWN = SVG_PROP_LAST,
	DOT_ID,
	DOT_LABEL,

	DOT_VERTEX_SHAPE,
	DOT_VERTEX_COLOR,
	DOT_VERTEX_STYLE,
	DOT_VERTEX_FILLCOLOR,

	DOT_EDGE_FROMID,
	DOT_EDGE_TOID,
	DOT_EDGE_WEIGHT, 
	DOT_EDGE_PENWIDTH, 
	DOT_EDGE_ARROWHEAD, 
	DOT_EDGE_ARROWTAIL, 
	DOT_EDGE_COLOR, 
	DOT_EDGE_STYLE, 

	DOT_PROP_LAST
};

GRAPHDB_API bool LoadXML(IGraph * graph, const std::string & verticesXML, const std::string & edgesXML);
GRAPHDB_API bool LoadXML2(IGraph * graph, const std::string & xml);
}