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
#include "Platform.h"

#include <boost/assert.hpp>

#include "GraphVertex.h"

namespace ln
{
CVertex::CVertex(IGraph * graph, ICluster * parent) : CGraphItem(graph), m_parent(parent)
{
	assert(m_parent);
	m_parent->AppendVertex(this);
}

//  ===  IVertex  ===
ICluster * CVertex::GetParent() const
{
	return m_parent;
}

unsigned int CVertex::GetInEdgeCount() const
{
	return m_inEdges.size();
}

unsigned int CVertex::GetOutEdgeCount() const
{
	return m_outEdges.size();
}

const IEdgeSet & CVertex::GetInEdges() const
{
	return m_inEdges;
}

const IEdgeSet & CVertex::GetOutEdges() const
{
	return m_outEdges;
}

void CVertex::AppendInEdge(IEdge * edge)
{
	m_inEdges.insert(edge);
}

void CVertex::AppendOutEdge(IEdge * edge)
{
	m_outEdges.insert(edge);
}
}