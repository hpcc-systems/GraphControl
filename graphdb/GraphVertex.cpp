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