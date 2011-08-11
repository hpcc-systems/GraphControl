#pragma once

#include "GraphItem.h"

namespace ln
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
	const IClusterSet & GetClusters() const;
	const IVertexSet & GetVertices() const;
	void AppendCluster(ICluster * cluster);
	void RemoveCluster(ICluster * cluster);
	void AppendVertex(IVertex * vertex);

	void Walk(IClusterVisitor * visitor);
	void Walk(IVertexVisitor * visitor);

	bool OnlyConatinsOneCluster() const;
	void Delete();
};

#define ICLUSTER_IMPL	ICluster * GetParent() const { return CCluster::GetParent(); } \
						const IClusterSet & GetClusters() const { return CCluster::GetClusters(); } \
						const IVertexSet & GetVertices() const { return CCluster::GetVertices(); } \
						void AppendCluster(ICluster * cluster) { CCluster::AppendCluster(cluster); } \
						void RemoveCluster(ICluster * cluster) { CCluster::RemoveCluster(cluster); } \
						void AppendVertex(IVertex * vertex) { CCluster::AppendVertex(vertex); } \
						void Walk(IClusterVisitor * visitor) { CCluster::Walk(visitor); } \
						void Walk(IVertexVisitor * visitor) { CCluster::Walk(visitor); } \
						bool OnlyConatinsOneCluster() const { return CCluster::OnlyConatinsOneCluster(); } \
						void Delete() { CCluster::Delete(); };

}