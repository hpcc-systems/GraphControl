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
#pragma once

#include "GraphDB.h"
#include "SvgParser.h"

namespace hpcc
{
enum DOT_PROP
{
	DOT_PROP_UNKNOWN = SVG_PROP_LAST,
	DOT_ID,
	DOT_LABEL,

	DOT_GRAPH_ATTRIBUTES,

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

	DOT_PROP_CDOTITEM,

	DOT_PROP_LAST
};

GRAPHDB_API bool LoadXML(IGraph * graph, const std::string & verticesXML, const std::string & edgesXML);
GRAPHDB_API bool LoadXML2(IGraph * graph, const std::string & xml);
}