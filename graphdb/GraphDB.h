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

#include "Unknown.h"

namespace hpcc
{
//  ===  Forward Declarations  ===
template<typename T>
struct CompareT
{
	bool operator() (const T & l, const T & r) const
	{
		return l->GetID() < r ->GetID();
	}
};

hpcc_interface IGraphItem;
typedef CUnknownPtr<IGraphItem> IGraphItemPtr;
typedef std::set<IGraphItemPtr, CompareT<IGraphItemPtr> > IGraphItemSet;

hpcc_interface IGraph;
typedef CUnknownPtr<IGraph> IGraphPtr;
typedef std::set<IGraphPtr, CompareT<IGraphPtr> > IGraphSet;

hpcc_interface ICluster;
typedef CUnknownPtr<ICluster> IClusterPtr;
typedef std::set<IClusterPtr, CompareT<IClusterPtr> > IClusterSet;

hpcc_interface IVertex;
typedef CUnknownPtr<IVertex> IVertexPtr;
typedef std::set<IVertexPtr, CompareT<IVertexPtr> > IVertexSet;

hpcc_interface IEdge;
typedef CUnknownPtr<IEdge> IEdgePtr;
typedef std::set<IEdgePtr, CompareT<IEdgePtr> > IEdgeSet;

typedef std::map<std::string, std::string> StringStringMap;

//  ===========================================================================
enum PROP
{
	PROP_UNKNOWN = 0,
	PROP_LAYOUT,
	PROP_LAST
};
//  External ID  ==============================================================
enum GRAPH_TYPE
{
	GRAPH_TYPE_UNKNOWN = 0,
	GRAPH_TYPE_GRAPH,
	GRAPH_TYPE_CLUSTER,
	GRAPH_TYPE_VERTEX,
	GRAPH_TYPE_EDGE,
	GRAPH_TYPE_LAST
};
//  ===========================================================================

hpcc_interface GRAPHDB_API IClusterVisitor
{
	virtual bool ItemVisited(ICluster * cluster) = 0;
};

hpcc_interface GRAPHDB_API IVertexVisitor
{
	virtual void ItemVisited(IVertex * vertex) = 0;
};

hpcc_interface GRAPHDB_API IEdgeVisitor
{
	virtual void ItemVisited(IEdge * edge) = 0;
};

hpcc_interface GRAPHDB_API IGraphItem : public IUnknown
{
	virtual IGraph * GetGraph() const = 0;
	virtual unsigned int GetID() const = 0;
	virtual const std::string & GetIDString() const = 0;

	virtual void SetProperty(unsigned int key, bool val) = 0;
	virtual bool GetPropertyBool(unsigned int key) const = 0;
	virtual void SetProperty(unsigned int key, int val) = 0;
	virtual int GetPropertyInt(unsigned int key) const = 0;
	virtual void SetProperty(unsigned int key, double val) = 0;
	virtual double GetPropertyDouble(unsigned int key) const = 0;
	virtual void SetProperty(unsigned int key, const char * val) = 0;
	virtual bool HasPropertyString(unsigned int key) const = 0;
	virtual const char * GetPropertyString(unsigned int key) const = 0;
	virtual void SetProperty(unsigned int key, IUnknown * val) = 0;
	virtual IUnknown * GetPropertyIUnknown(unsigned int key) const = 0;
	virtual void SetProperty(unsigned int key, CUnknown * val) = 0;
	virtual CUnknown * GetPropertyCUnknown(unsigned int key) const = 0;

	virtual void SetProperty(const std::string & key, const std::string & val) = 0;
	virtual const char * GetProperty(const std::string & key) const = 0;
	virtual int GetProperties(StringStringMap & results) const = 0;
};

hpcc_interface GRAPHDB_API ICluster : public IGraphItem
{
	virtual ICluster * GetParent() const = 0;
	virtual void MoveTo(ICluster * cluster) = 0;
	virtual const IClusterSet & GetClusters() const = 0;
	virtual const IVertexSet & GetVertices() const = 0;

	virtual void AppendCluster(ICluster * cluster) = 0;
	virtual void RemoveCluster(ICluster * cluster) = 0;
	virtual void AppendVertex(IVertex * vertex) = 0;
	virtual void RemoveVertex(IVertex * vertex) = 0;

	virtual void Walk(IClusterVisitor * visitor) const = 0;
	virtual void Walk(IVertexVisitor * visitor) const = 0;

	virtual bool OnlyConatinsOneCluster() const = 0;
};

hpcc_interface GRAPHDB_API IVertex : public IGraphItem
{
	virtual ICluster * GetParent() const = 0;
	virtual void MoveTo(ICluster * cluster) = 0;
	virtual unsigned int GetInEdgeCount() const = 0;
	virtual unsigned int GetOutEdgeCount() const = 0;
	virtual const IEdgeSet & GetInEdges() const = 0;
	virtual const IEdgeSet & GetOutEdges() const = 0;

	virtual unsigned int GetAdjacentVertices(IVertexSet & adjacentVertices) const = 0;
	virtual IEdge * GetEdge(IVertex * adjacentVertex) const = 0;

	virtual void AppendInEdge(IEdge * edge) = 0;
	virtual void AppendOutEdge(IEdge * edge) = 0;
};

hpcc_interface GRAPHDB_API IEdge : public IGraphItem
{
	virtual IVertex * GetFromVertex() const = 0;
	virtual IVertex * GetToVertex() const = 0;
};

hpcc_interface GRAPHDB_API IGraph : public ICluster
{
	virtual void Clear() = 0;

	virtual ICluster * CreateCluster() = 0;
	virtual ICluster * CreateCluster(ICluster * cluster) = 0;
	virtual void DeleteCluster(ICluster * cluster) = 0;

	virtual IVertex * CreateVertex() = 0;
	virtual IVertex * CreateVertex(ICluster * cluster) = 0;

	virtual IEdge * CreateEdge(IVertex * from, IVertex * to) = 0;

	virtual IGraph * GetGraph(const std::string & id, bool externalID = false) const = 0;

	virtual const IClusterSet & GetAllClusters() const = 0;
	virtual ICluster * GetCluster(unsigned int id) const = 0;
	virtual ICluster * GetCluster(const std::string & id, bool externalID = false) const = 0;
	 
	virtual const IVertexSet & GetAllVertices() const = 0;
	virtual IVertex * GetVertex(unsigned int id) const = 0;
	virtual IVertex * GetVertex(const std::string & id, bool externalID = false) const = 0;

	virtual const IEdgeSet & GetAllEdges() const = 0;
	virtual IEdge * GetEdge(unsigned int id) const = 0;
	virtual IEdge * GetEdge(const std::string & id, bool externalID = false) const = 0;
	virtual void Walk(IEdgeVisitor * visitor) const = 0;

	virtual IGraphItem * GetGraphItem(unsigned int id) const = 0;
	virtual IGraphItem * GetGraphItem(GRAPH_TYPE type, const std::string & id) const = 0;

	virtual void SetExternalID(GRAPH_TYPE type, const std::string & id, IGraphItem * item) = 0;
	virtual const char * GetExternalID(int item) const = 0;
};

//  ===  Factories  ===
GRAPHDB_API IGraph * CreateGraph();
GRAPHDB_API const char * WriteDOT(const IGraph * graph, std::string & dot);
GRAPHDB_API const char * WriteLocalisedXGMML(const IGraph * graph, const IGraphItemSet & items, int localisationDepth, int localisationDistance, std::string & xgmml);
}