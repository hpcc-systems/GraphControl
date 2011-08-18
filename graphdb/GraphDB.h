#pragma once

#include "Unknown.h"

namespace ln
{
//  ===  Forward Declarations  ===
interface IGraphItem;
typedef CUnknownPtr<IGraphItem> IGraphItemPtr;
typedef std::set<IGraphItemPtr> IGraphItemSet;

interface IGraph;
typedef CUnknownPtr<IGraph> IGraphPtr;
typedef std::set<IGraphPtr> IGraphSet;

interface ICluster;
typedef CUnknownPtr<ICluster> IClusterPtr;
typedef std::set<IClusterPtr> IClusterSet;

interface IVertex;
typedef CUnknownPtr<IVertex> IVertexPtr;
typedef std::set<IVertexPtr> IVertexSet;

interface IEdge;
typedef CUnknownPtr<IEdge> IEdgePtr;
typedef std::set<IEdgePtr> IEdgeSet;

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
	GRAPH_TYPE_CLUSTER,
	GRAPH_TYPE_VERTEX,
	GRAPH_TYPE_EDGE,
	GRAPH_TYPE_LAST
};

//  ===========================================================================

interface GRAPHDB_API IClusterVisitor
{
	virtual void ItemVisited(ICluster * cluster) = 0;
};

interface GRAPHDB_API IVertexVisitor
{
	virtual void ItemVisited(IVertex * vertex) = 0;
};

interface GRAPHDB_API IEdgeVisitor
{
	virtual void ItemVisited(IEdge * edge) = 0;
};

interface GRAPHDB_API IGraphItem : public IUnknown
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

interface GRAPHDB_API ICluster : public IGraphItem
{
	virtual ICluster * GetParent() const = 0;
	virtual const IClusterSet & GetClusters() const = 0;
	virtual const IVertexSet & GetVertices() const = 0;

	virtual void AppendCluster(ICluster * cluster) = 0;
	virtual void RemoveCluster(ICluster * cluster) = 0;
	virtual void AppendVertex(IVertex * vertex) = 0;

	virtual void Walk(IClusterVisitor * visitor) = 0;

	virtual bool OnlyConatinsOneCluster() const = 0;
	virtual void Delete() = 0;
};

interface GRAPHDB_API IVertex : public IGraphItem
{
	virtual ICluster * GetParent() const = 0;
	virtual unsigned int GetInEdgeCount() const = 0;
	virtual unsigned int GetOutEdgeCount() const = 0;
	virtual const IEdgeSet & GetInEdges() const = 0;
	virtual const IEdgeSet & GetOutEdges() const = 0;

	virtual void AppendInEdge(IEdge * edge) = 0;
	virtual void AppendOutEdge(IEdge * edge) = 0;
};

interface GRAPHDB_API IEdge : public IGraphItem
{
	virtual IVertex * GetFromVertex() const = 0;
	virtual IVertex * GetToVertex() const = 0;
};

interface GRAPHDB_API IGraph : public ICluster
{
	virtual void Clear() = 0;

	virtual ICluster * CreateCluster() = 0;
	virtual ICluster * CreateCluster(ICluster * cluster) = 0;
	virtual IVertex * CreateVertex() = 0;
	virtual IVertex * CreateVertex(ICluster * cluster) = 0;
	virtual IEdge * CreateEdge(IVertex * from, IVertex * to) = 0;

	virtual const IClusterSet & GetAllClusters() const = 0;
	virtual ICluster * GetCluster(unsigned int id) const = 0;
	virtual ICluster * GetCluster(const std::string & id, bool externalID = false) const = 0;
	 
	virtual const IVertexSet & GetAllVertices() const = 0;
	virtual IVertex * GetVertex(unsigned int id) const = 0;
	virtual IVertex * GetVertex(const std::string & id, bool externalID = false) const = 0;

	virtual const IEdgeSet & GetAllEdges() const = 0;
	virtual IEdge * GetEdge(unsigned int id) const = 0;
	virtual IEdge * GetEdge(const std::string & id, bool externalID = false) const = 0;

	virtual IGraphItem * GetGraphItem(unsigned int id) const = 0;
	virtual IGraphItem * GetGraphItem(GRAPH_TYPE type, const std::string & id) const = 0;

	virtual void SetExternalID(GRAPH_TYPE type, const std::string & id, IGraphItem * item) = 0;
	virtual const char * GetExternalID(int item) const = 0;
};

//  ===  Factories  ===
GRAPHDB_API IGraph * CreateGraph();
GRAPHDB_API const char * WriteDOT(const IGraph * graph, std::string & dot);
GRAPHDB_API const char * WriteLocalisedXGMML(const IGraph * graph, const IGraphItem * item, std::string & xgmml);
}