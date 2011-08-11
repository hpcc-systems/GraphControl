#include "Platform.h"

#include <boost/assert.hpp>

#include "GraphCluster.h"

namespace ln
{
CCluster::CCluster() : CGraphItem()
{
}

CCluster::CCluster(IGraph * graph, ICluster * parent) : CGraphItem(graph), m_parent(parent)
{
	assert(m_parent);
	m_parent->AppendCluster(this);
}

void CCluster::Clear()
{
	CGraphItem::Clear();
	m_clusters.clear();
	m_vertices.clear();
}

//  ===  ICluster  ===
ICluster * CCluster::GetParent() const
{
	return m_parent;
}

const IClusterSet & CCluster::GetClusters() const
{
	return m_clusters;
}

const IVertexSet & CCluster::GetVertices() const
{
	return m_vertices;
}

void CCluster::AppendCluster(ICluster * cluster)
{
	m_clusters.insert(cluster);
}

void CCluster::RemoveCluster(ICluster * cluster)
{
	IClusterSet::const_iterator found = m_clusters.find(cluster);
	if (found != m_clusters.end())
		m_clusters.erase(found);
}

void CCluster::AppendVertex(IVertex * vertex)
{
	m_vertices.insert(vertex);
}

void CCluster::Walk(IClusterVisitor * visitor)
{
	for(IClusterSet::const_iterator itr = m_clusters.begin(); itr != m_clusters.end(); ++itr)
	{
		visitor->ItemVisited(*itr);
		itr->get()->Walk(visitor);
	}
}

void CCluster::Walk(IVertexVisitor * visitor)
{
	for(IVertexSet::const_iterator itr = m_vertices.begin(); itr != m_vertices.end(); ++itr)
	{
		visitor->ItemVisited(*itr);
	}
}

bool CCluster::OnlyConatinsOneCluster() const
{
	if (m_clusters.size() == 1 && m_vertices.size() == 0)
		return true;
	return false;
}

void CCluster::Delete()
{
	if (ICluster * parent = GetParent())
	{
		for (IClusterSet::const_iterator itr = m_clusters.begin(); itr != m_clusters.end(); ++itr)
			parent->AppendCluster(itr->get());
		for (IVertexSet::const_iterator itr = m_vertices.begin(); itr != m_vertices.end(); ++itr)
			parent->AppendVertex(itr->get());
		parent->RemoveCluster(this);
	}
}

}