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

#include "GraphItem.h"

namespace hpcc
{
class CCluster : public ICluster, public CGraphItem
{
protected:
	ICluster * m_parent;
	IClusterSet m_clusters;
	IVertexSet m_vertices;

public:
	BEGIN_CUNKNOWN
	END_CUNKNOWN

	CCluster();	//  Special case for CGraph constructor
	CCluster(IGraph * graph, ICluster * parent);

	void Clear();

	//  ===  IGraphItem  ===
	IGRAPHITEM_IMPL

	//  ===  ICluster  ===
	ICluster * GetParent() const;
	void MoveTo(ICluster * cluster);
	const IClusterSet & GetClusters() const;
	const IVertexSet & GetVertices() const;
	void AppendCluster(ICluster * cluster);
	void RemoveCluster(ICluster * cluster);
	void AppendVertex(IVertex * vertex);
	void RemoveVertex(IVertex * vertex);

	void Walk(IClusterVisitor * visitor) const;
	void Walk(IVertexVisitor * visitor) const;

	bool OnlyConatinsOneCluster() const;
};

#define ICLUSTER_IMPL	ICluster * GetParent() const { return CCluster::GetParent(); } \
						void MoveTo(ICluster * cluster) { CCluster::MoveTo(cluster); } \
						const IClusterSet & GetClusters() const { return CCluster::GetClusters(); } \
						const IVertexSet & GetVertices() const { return CCluster::GetVertices(); } \
						void AppendCluster(ICluster * cluster) { CCluster::AppendCluster(cluster); } \
						void RemoveCluster(ICluster * cluster) { CCluster::RemoveCluster(cluster); } \
						void AppendVertex(IVertex * vertex) { CCluster::AppendVertex(vertex); } \
						void RemoveVertex(IVertex * vertex) { CCluster::RemoveVertex(vertex); } \
						void Walk(IClusterVisitor * visitor) const { CCluster::Walk(visitor); } \
						void Walk(IVertexVisitor * visitor) const { CCluster::Walk(visitor); } \
						bool OnlyConatinsOneCluster() const { return CCluster::OnlyConatinsOneCluster(); } 
}