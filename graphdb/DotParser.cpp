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

#include "XgmmlParser.h"
#include "GraphDB.h"
#include "DotShapes.h"
#include "DotParser.h"
#include "util.h"

#include <libagraph.h>

/*
digraph G {

subgraph cluster0 {  //subgraph<Graph>
node [style=filled color=white];
style = filled;
bgcolor = lightgrey;

subgraph inner { //subgraph<Graph> or subgraph of subgraph
node [color = green];
a1 -> a2 -> a3 

};

a0 -> subgraph inner;

label = "process #1";
}

subgraph cluster1 {
node [style=filled color=white];
b0 -> b1 -> b2 -> b3;
label = "process #2";
bgcolor = lightgrey
}

subgraph cluster1 -> subgraph cluster0 [style=dashed color=red]

start -> subgraph inner[style=dotted];

start -> a0;
start -> b0;
a1 -> b3;
b2 -> a3;
a3 -> end;
b3 -> end;

start [shape=Mdiamond];
end [shape=Msquare];
}

digraph foo {
edge [weight="10"];

0 -> 1 [weight="3.14159"];
1 -> foo [weight="2.71828"];
foo -> bar;
bar -> 1;

subgraph cluster1 {
node [style=filled color=white];
b0 -> b1 -> b2 -> b3;
label = "process #2";
bgcolor = lightgrey
}
}

*/
namespace hpcc
{
#ifdef DOT_PARSER
typedef std::map<std::string, CDotEdgePtr> EdgeStructSet;
typedef std::map<std::string, CDotVertexPtr> VertexStructSet;

class CGraphvizVisitor : public IGraphvizVisitor 
{
	VertexStructSet m_vertexStructs; 
	EdgeStructSet m_edgeStructs;

	IGraphPtr m_graph;
	std::stack<IClusterPtr> m_clusterStack;

	bool m_merge;

public:
	CGraphvizVisitor(IGraph * graph, bool merge) 
	{
		m_graph = graph;
		m_merge = merge;
		m_clusterStack.push(graph);
	}

	~CGraphvizVisitor() 
	{
		m_clusterStack.pop();
		assert(m_clusterStack.empty());
	}

	void OnStartGraph(bool directed, const std::string & id, const AttrMap & attrs)
	{
		assert(!id.empty());
		m_graph->SetExternalID(GRAPH_TYPE_GRAPH, id, m_graph);
		m_graph->SetProperty(DOT_ID, id.c_str());
		m_graph->SetProperty(DOT_PROP_CDOTITEM, new CDotGraph(directed, id, attrs));
		m_clusterStack.push(NULL);
	}

	void OnEndGraph(const std::string & id)
	{
		m_clusterStack.pop();
	}

	void OnStartCluster(const std::string & id, const AttrMap & attrs)
	{
		assert(!id.empty());
		m_clusterStack.push(GetCluster(m_graph, m_clusterStack.top(), id, m_merge));
		m_clusterStack.top()->SetProperty(DOT_PROP_CDOTITEM, new CDotCluster(id, attrs));
	}

	void OnEndCluster(const std::string & id)
	{
		m_clusterStack.pop();
	}

	void OnStartVertex(int _id, const AttrMap & attrs)
	{
		OnStartVertex(UIntToString(_id), attrs);
	}
	void OnEndVertex(int id)
	{
	}
	void OnStartVertex(const std::string & id, const AttrMap & attrs)
	{
		if (m_vertexStructs.find(id) == m_vertexStructs.end())
		{
			IVertexPtr v = GetVertex(m_graph, m_clusterStack.top(), id, m_merge);
			m_vertexStructs[id] = new CDotVertex(id, attrs); 
			v->SetProperty(DOT_PROP_CDOTITEM, m_vertexStructs[id]);
		}
	}
	void OnEndVertex(const std::string & id)
	{
	}
	void OnStartEdge(bool directed, const std::string & id, const std::string & sourceID, const std::string & targetID, const AttrMap & attrs)
	{
		if (m_edgeStructs.find(id) == m_edgeStructs.end())
		{
			m_edgeStructs[id] = new CDotEdge(directed, id, sourceID, targetID, attrs);
		}
	}
	void OnEndEdge(const std::string & id)
	{
	}

	void ProcessEdges()
	{
		for (EdgeStructSet::const_iterator itr = m_edgeStructs.begin(); itr != m_edgeStructs.end(); ++itr)
		{
			CDotEdge * dotEdge = itr->second.get();
			assert(dotEdge);
			IVertex * vSource = m_graph->GetVertex(dotEdge->m_source, true);
			assert(vSource);
			IVertex * vTarget = m_graph->GetVertex(dotEdge->m_target, true);
			assert(vTarget);
			assert(!dotEdge->m_name.empty());
			IEdge * edge = GetEdge(m_graph, dotEdge->m_name, vSource, vTarget, m_merge);
			assert(edge);
			edge->SetProperty(DOT_PROP_CDOTITEM, dotEdge);
		}
	}
};
#endif

GRAPHDB_API bool LoadDOT(IGraph * graph, const std::string & dot)
{
#ifdef DOT_PARSER
	AttrMap attrs;
	CGraphvizVisitor visitor(graph, false);
	DoParse(dot.c_str(), &visitor);
	visitor.ProcessEdges();
	return true;
#else
	return false;
#endif
}

GRAPHDB_API bool MergeDOT(IGraph * graph, const std::string & dot)
{
	bool retVal = false;
	return retVal;
}
}
