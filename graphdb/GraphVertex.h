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

#include "GraphGraph.h"

namespace hpcc
{
class CVertex : public IVertex, public CGraphItem
{
protected:
	ICluster * m_parent;

	IEdgeSet m_inEdges;
	IEdgeSet m_outEdges;

public:
	BEGIN_CUNKNOWN
	END_CUNKNOWN

	CVertex(IGraph * graph, ICluster * parent);

	//  ===  IGraphItem  ===
	IGRAPHITEM_IMPL

	//  ===  IVertex  ===
	ICluster * GetParent() const;
	void SetParent(ICluster * cluster);
	unsigned int GetInEdgeCount() const;
	unsigned int GetOutEdgeCount() const;
	const IEdgeSet & GetInEdges() const;
	const IEdgeSet & GetOutEdges() const;
	unsigned int GetAdjacentVertices(IVertexSet & adjacentVertices) const;
	IEdge * GetEdge(IVertex * adjacentVertex) const;
	void AppendInEdge(IEdge * edge);
	void AppendOutEdge(IEdge * edge);
};
typedef CUnknownPtr<CVertex> CVertexPtr;
}