#pragma once

#include "GraphGraph.h"

namespace ln
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
	unsigned int GetInEdgeCount() const;
	unsigned int GetOutEdgeCount() const;
	const IEdgeSet & GetInEdges() const;
	const IEdgeSet & GetOutEdges() const;
	void AppendInEdge(IEdge * edge);
	void AppendOutEdge(IEdge * edge);
};
typedef CUnknownPtr<CVertex> CVertexPtr;
}