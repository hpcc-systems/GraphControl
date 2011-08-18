#include "Platform.h"

#include "GraphEdge.h"

namespace ln
{
CEdge::CEdge(IGraph * graph, IVertex * from, IVertex * to) : CGraphItem(graph), m_from(from), m_to(to)
{
	m_from->AppendOutEdge(this);
	m_to->AppendInEdge(this);
}

//  ===  IEdge  ===
IVertex * CEdge::GetFromVertex() const
{
	return m_from;
}

IVertex * CEdge::GetToVertex() const
{
	return m_to;
}
}