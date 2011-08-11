#pragma once

#include "GraphGraph.h"

namespace ln
{
class CEdge : public IEdge, public CGraphItem
{
protected:
	IVertex * m_from;
	IVertex * m_to;

public:
	BEGIN_CUNKNOWN
	END_CUNKNOWN

	CEdge(IGraph * graph, IVertex * from, IVertex * to);

	//  ===  IGraphItem  ===
	IGRAPHITEM_IMPL

	//  ===  IEdge  ===
	IVertex * GetFromVertex() const;
	IVertex * GetToVertex() const;
};
typedef CUnknownPtr<CEdge> CEdgePtr;
}