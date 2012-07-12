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

#include "GraphCluster.h"
#include "util.h"

namespace hpcc
{
class CVertex;
class CEdge;

typedef std::pair<GRAPH_TYPE, std::string> GraphTypeStringPair;
typedef std::map<GraphTypeStringPair, unsigned int> ExternalIDGraphItemMap;
typedef std::map<unsigned int, GraphTypeStringPair> GraphItemExternalIDMap;

class CGraph : public IGraph, public CCluster
{
protected:
	IClusterSet m_allClusters;
	IVertexSet m_allVertices;
	IEdgeSet m_allEdges;
	IDGraphItemMap m_allItems;
	ExternalIDGraphItemMap m_externalIDs;
	GraphItemExternalIDMap m_rexternalIDs;

public:

	BEGIN_CUNKNOWN
	END_CUNKNOWN

	CGraph();

	template<typename T>
	T * GetItem(unsigned int id) const
	{
		IDGraphItemMap::const_iterator found = m_allItems.find(id);
		if(found != m_allItems.end())
			return found->second->QueryInterface<T>();
		return NULL;
	}

	template<typename T>
	T * GetItem(const std::string & id) const
	{
		return GetItem<T>(StringToUInt(id));
	}

	template<typename T>
	T * GetItem(GRAPH_TYPE type, const std::string & id) const
	{
	    #ifdef WIN32
		assert(!id.empty());
		#endif
		ExternalIDGraphItemMap::const_iterator found = m_externalIDs.find(GraphTypeStringPair(type, id));
		if(found != m_externalIDs.end())
			return GetItem<T>(found->second);
		//assert(false);
		return NULL;
	}

	//  ===  IGraphItem  ===
	IGRAPHITEM_IMPL

	//  ===  ICluster  ===
	ICLUSTER_IMPL

	//  ===  IGraph  ===
	void Clear();

	ICluster * CreateCluster();
	ICluster * CreateCluster(ICluster * cluster);
	void DeleteCluster(ICluster * cluster);

	IVertex * CreateVertex();
	IVertex * CreateVertex(ICluster * cluster);

	IEdge * CreateEdge(IVertex * from, IVertex * to);

	IGraph * GetGraph(const std::string & id, bool externalID = false) const;

	const IClusterSet & GetAllClusters() const;
	ICluster * GetCluster(unsigned int id) const;
	ICluster * GetCluster(const std::string & id, bool externalID = false) const;

	const IVertexSet & GetAllVertices() const;
	IVertex * GetVertex(unsigned int id) const;
	IVertex * GetVertex(const std::string & id, bool externalID = false) const;

	const IEdgeSet & GetAllEdges() const;
	IEdge * GetEdge(unsigned int id) const;
	IEdge * GetEdge(const std::string & id, bool externalID = false) const;
	void Walk(IEdgeVisitor * visitor) const;

	IGraphItem * GetGraphItem(unsigned int id) const;
	IGraphItem * GetGraphItem(const std::string & id) const;
	IGraphItem * GetGraphItem(GRAPH_TYPE type, const std::string & id) const;

	//  ExternalID Helper  ---
	void SetExternalID(GRAPH_TYPE type, const std::string & id, IGraphItem * item);
	const char * GetExternalID(int item) const;
};
typedef CUnknownPtr<CGraph> CGraphPtr;

}
