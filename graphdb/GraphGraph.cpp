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
#include "precompiled_headers.h"

#include "GraphGraph.h"
#include "GraphVertex.h"
#include "GraphEdge.h"

#include "SvgParser.h"

namespace hpcc
{
CGraph::CGraph() : CCluster()  //- 'this' should not be used in base member initializer list.
{
	m_graph = this;
	m_parent = NULL;
	SetProperty("id", "0");
	SetExternalID(hpcc::GRAPH_TYPE_GRAPH, "0", (IGraph *)this);
}

void CGraph::Clear()
{
	CCluster::Clear();
	m_allClusters.clear();
	m_allVertices.clear();
	m_allEdges.clear();
	m_allItems.clear();
	m_externalIDs.clear();
	m_rexternalIDs.clear();
	SetProperty("id", "0");
	SetExternalID(hpcc::GRAPH_TYPE_GRAPH, "0", (IGraph *)this);
}

ICluster * CGraph::CreateCluster()
{
	CCluster * c = new CCluster(this, (IGraph *)this);
	m_clusters.insert(c);
	m_allClusters.insert(c);
	m_allItems[c->GetID()] = c;
	return c;
}

ICluster * CGraph::CreateCluster(ICluster * cluster)
{
	//assert(cluster != NULL);
	if(cluster == NULL)
		return CreateCluster();
	CCluster * c = new CCluster(this, cluster);
	m_allClusters.insert(c);
	m_allItems[c->GetID()] = c;
	return c;
}

void CGraph::DeleteCluster(ICluster * cluster)
{
	if (cluster != (IGraph *)this)
	{
		//  Elevate children  ---
		ICluster * parent = cluster->GetParent();
		IClusterSet clusters = cluster->GetClusters();
		for (IClusterSet::const_iterator itr = clusters.begin(); itr != clusters.end(); ++itr)
			itr->get()->MoveTo(parent);
		IVertexSet vertices = cluster->GetVertices();
		for (IVertexSet::const_iterator itr = vertices.begin(); itr != vertices.end(); ++itr)
			itr->get()->MoveTo(parent);

		//  Delete Cluster  ---
		parent->RemoveCluster(cluster);
		{
			IClusterSet::iterator found = m_allClusters.find(cluster);
			if (found != m_allClusters.end())
				m_allClusters.erase(found);
		}
		{
			IDGraphItemMap::iterator found = m_allItems.find(cluster->GetID());
			if (found != m_allItems.end())
				m_allItems.erase(found);
		}
	}
}

IVertex * CGraph::CreateVertex()
{
	CVertex * v = new CVertex(this, (IGraph *)this);
	m_allVertices.insert(v);
	m_allItems[v->GetID()] = v;
	return v;
}

IVertex * CGraph::CreateVertex(ICluster * cluster)
{
	assert(cluster != NULL);
	if(cluster == NULL)
		return CreateVertex();
	CVertex * v = new CVertex(this, cluster);
	m_allVertices.insert(v);
	m_allItems[v->GetID()] = v;
	return v;
}

IEdge * CGraph::CreateEdge(IVertex * from, IVertex * to)
{
	CEdge * e = new CEdge(this, from, to);
	m_allEdges.insert(e);
	m_allItems[e->GetID()] = e;
	return e;
}

IGraph * CGraph::GetGraph(const std::string & id, bool externalID) const
{
	if (externalID)
		return GetItem<IGraph>(GRAPH_TYPE_GRAPH, id);
	return GetItem<IGraph>(id);
}

const IClusterSet & CGraph::GetAllClusters() const
{
	return m_allClusters;
}

ICluster * CGraph::GetCluster(unsigned int id) const
{
	return GetItem<ICluster>(id);
}

ICluster * CGraph::GetCluster(const std::string & id, bool externalID) const
{
	if (externalID)
		return GetItem<ICluster>(GRAPH_TYPE_CLUSTER, id);
	return GetItem<ICluster>(id);
}

const IVertexSet & CGraph::GetAllVertices() const
{
	return m_allVertices;
}

IVertex * CGraph::GetVertex(unsigned int id) const
{
	return GetItem<IVertex>(id);
}

IVertex * CGraph::GetVertex(const std::string & id, bool externalID) const
{
	if (externalID)
		return GetItem<IVertex>(GRAPH_TYPE_VERTEX, id);
	return GetItem<IVertex>(id);
}

const IEdgeSet & CGraph::GetAllEdges() const
{
	return m_allEdges;
}

IEdge * CGraph::GetEdge(unsigned int id) const
{
	return GetItem<IEdge>(id);
}

IEdge * CGraph::GetEdge(const std::string & id, bool externalID) const
{
	if (externalID)
		return GetItem<IEdge>(GRAPH_TYPE_EDGE, id);
	return GetItem<IEdge>(id);
}

void CGraph::Walk(IEdgeVisitor * visitor) const
{
	for (IEdgeSet::const_iterator itr = m_allEdges.begin(); itr != m_allEdges.end(); ++itr) 
	{
		visitor->ItemVisited(itr->get());
	}
}

IGraphItem * CGraph::GetGraphItem(unsigned int id) const
{
	if (m_id == id || id == 0)
		return (IGraph *)const_cast<CGraph *>(this);

	IDGraphItemMap::const_iterator found = m_allItems.find(id);
	if(found != m_allItems.end())
		return found->second.get();
	return NULL;
}

IGraphItem * CGraph::GetGraphItem(const std::string & id) const
{
	return GetGraphItem(StringToUInt(id));
}

IGraphItem * CGraph::GetGraphItem(GRAPH_TYPE type, const std::string & id) const
{
	assert(!id.empty());
	ExternalIDGraphItemMap::const_iterator found = m_externalIDs.find(GraphTypeStringPair(type, id));
	if(found != m_externalIDs.end())
		return GetGraphItem(found->second);
	return NULL;
}

void CGraph::SetExternalID(GRAPH_TYPE type, const std::string & id, IGraphItem * item)
{
	assert(!id.empty());
	assert(item);
	//GJS TODO:  Should be true, but there is a bug in the GetLocalisedXGMML:  assert(GetGraphItem(type, id) == NULL || GetGraphItem(type, id) == item);
	m_externalIDs[GraphTypeStringPair(type, id)] = item->GetID();
	m_rexternalIDs[item->GetID()] = GraphTypeStringPair(type, id);
}

const char * CGraph::GetExternalID(int item) const
{
	assert(item != 0);
	GraphItemExternalIDMap::const_iterator found = m_rexternalIDs.find(item);
	if(found != m_rexternalIDs.end())
		return found->second.second.c_str();
	return NULL;
}

}
