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
#include "DotShapes.h"

namespace hpcc
{

void attrsToString(const CDotItem::AttrMap & attrs, const std::string & delim, std::string & result)
{
	for (CDotItem::AttrMap::const_iterator itr = attrs.begin(); itr != attrs.end(); ++itr)
	{
		if (itr->first.compare("id") != 0)
			result += itr->first + "=\"" + itr->second + "\"" + delim;
	}
}

CDotItem::CDotItem(const std::string & name, const AttrMap & attrs) : m_name(name), m_attrs(attrs)
{
}

CDotGraph::CDotGraph(bool directed, const std::string & name, const AttrMap & attrs) : CDotItem(name, attrs), m_directed(directed)
{
}

const std::string CDotGraph::ToDot(const std::string & id, const std::string & content)
{
	std::string retVal = (m_directed == 0 ? "graph \"" : "digraph \"") + m_name + "\" {\nid=\"" + id + "\";\n";
	attrsToString(m_attrs, ";\n", retVal);
	retVal += content + "}\n";
	return retVal;
}

CDotCluster::CDotCluster(const std::string & name, const AttrMap & attrs) : CDotItem(name, attrs)
{
}

const std::string CDotCluster::ToDot(const std::string & id, const std::string & content)
{
	std::string retVal = "subgraph \"cluster_" + id + "\" {\nid=\"" + id + "\";\n";
	attrsToString(m_attrs, ";\n", retVal);
	retVal += content + "}\n";
	return retVal;
}

CDotVertex::CDotVertex(const std::string & name, const AttrMap & attrs) : CDotItem(name, attrs)
{
}

const std::string CDotVertex::ToDot(const std::string & id, const std::string & content)
{
	std::string retVal = "\"" + m_name + "\" [id=\"" + id + "\" ";
	attrsToString(m_attrs, " ", retVal);
	retVal += content + "];\n";
	return retVal;
}

CDotEdge::CDotEdge(bool directed, const std::string & name, const std::string & source, const std::string & target, const AttrMap & attrs) : CDotItem(name, attrs), m_directed(directed), m_source(source), m_target(target)
{
}

const std::string CDotEdge::ToDot(const std::string & id, const std::string & content)
{
	std::string retVal = "\"" + m_source + "\"" + (m_directed == 0 ? " -- " : " -> ") + "\"" + m_target + "\" [id=\"" + id + "\" ";
	attrsToString(m_attrs, " ", retVal);
	retVal += content + "];\n";
	return retVal;
}
}


