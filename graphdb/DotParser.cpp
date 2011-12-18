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
#include "Platform.h"

#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>
//#include <boost/test/minimal.hpp>
#include <string>
#include <fstream>
#include <boost/graph/iteration_macros.hpp>

using namespace boost;

typedef boost::adjacency_list<vecS, vecS, directedS,
                              property<vertex_name_t, std::string>,
                              property<edge_weight_t, double> > Digraph;

typedef boost::adjacency_list<vecS, vecS, undirectedS,
                              property<vertex_name_t, std::string>,
                              property<edge_weight_t, double> > Graph;

/*
void test_graph_read_write(const std::string& filename)
{
  std::ifstream in(filename.c_str());
  BOOST_REQUIRE(in);

  Graph g;
  dynamic_properties dp;
  dp.property("id", get(vertex_name, g));
  dp.property("weight", get(edge_weight, g));
  BOOST_CHECK(read_graphviz(in, g, dp, "id"));

  BOOST_CHECK(num_vertices(g) == 4);
  BOOST_CHECK(num_edges(g) == 4);
  
  typedef graph_traits<Graph>::vertex_descriptor Vertex;

  std::map<std::string, Vertex> name_to_vertex;
  BGL_FORALL_VERTICES(v, g, Graph) 
    name_to_vertex[get(vertex_name, g, v)] = v;

  // Check vertices
  BOOST_CHECK(name_to_vertex.find("0") != name_to_vertex.end());
  BOOST_CHECK(name_to_vertex.find("1") != name_to_vertex.end());
  BOOST_CHECK(name_to_vertex.find("foo") != name_to_vertex.end());
  BOOST_CHECK(name_to_vertex.find("bar") != name_to_vertex.end());

  // Check edges
  BOOST_CHECK(edge(name_to_vertex["0"], name_to_vertex["1"], g).second);
  BOOST_CHECK(edge(name_to_vertex["1"], name_to_vertex["foo"], g).second);
  BOOST_CHECK(edge(name_to_vertex["foo"], name_to_vertex["bar"], g).second);
  BOOST_CHECK(edge(name_to_vertex["1"], name_to_vertex["bar"], g).second);

  BOOST_CHECK(get(edge_weight, g, 
                  edge(name_to_vertex["0"], name_to_vertex["1"], g).first)
                == 3.14159);
  BOOST_CHECK(get(edge_weight, g, 
                  edge(name_to_vertex["1"], name_to_vertex["foo"], g).first)
                == 2.71828);
  BOOST_CHECK(get(edge_weight, g, 
                  edge(name_to_vertex["foo"], name_to_vertex["bar"], g).first)
                == 10.0);
  BOOST_CHECK(get(edge_weight, g, 
                  edge(name_to_vertex["1"], name_to_vertex["bar"], g).first)
                == 10.0);

  // Write out the graph
  write_graphviz_dp(std::cout, g, dp, std::string("id"));
}


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
*/
#include "DotParser.h"

namespace ln
{
GRAPHDB_API bool LoadDOT(IGraph * graph, const std::string & dot)
{
	Graph g;
	dynamic_properties dp;
	dp.property("id", get(vertex_name, g));
	dp.property("weight", get(edge_weight, g));
	read_graphviz(dot, g, dp, "id");

	bool retVal = false;
	return retVal;
}

GRAPHDB_API bool MergeDOT(IGraph * graph, const std::string & dot)
{
	bool retVal = false;
	return retVal;
}
}
