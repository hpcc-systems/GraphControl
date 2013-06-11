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

#include <neato.h>
#include <gvc.h>

#if WITH_CGRAPH
#include <cgraph.h> // needed to cure VS7 linker error
extern Agraph_t *agmemread(const char *);
#else
#include <graph.h> // needed to cure VS7 linker error
//extern Agraph_t *agfstsubg(Agraph_t * g), *agnxtsubg(Agraph_t * subg);
#endif

//
//// required for exporting shortest_route
//
#include <vispath.h>
#include "libagraphsp.h"
#include <boost/algorithm/string.hpp>

void global_cleanup()
{
	free(Gvfilepath);
	free(Files);
	free(Lib);
}

extern "C" gvplugin_library_t gvplugin_dot_layout_LTX_library;
extern "C" gvplugin_library_t gvplugin_neato_layout_LTX_library;
extern "C" gvplugin_library_t gvplugin_core_LTX_library;

lt_symlist_t lt_preloaded_symbols[] = {
	{ "gvplugin_dot_layout_LTX_library", (void*)(&gvplugin_dot_layout_LTX_library) },
	{ "gvplugin_neato_layout_LTX_library", (void*)(&gvplugin_neato_layout_LTX_library) },
	{ "gvplugin_core_LTX_library", (void*)(&gvplugin_core_LTX_library) },
	{ 0, 0 }
};

std::map<GVC_t *, std::string> g_result;
size_t MyWriteFunction(GVJ_t *job, const char *s, size_t len)
{
	g_result[job->gvc].append(s, len);
	return len;
}

static GVC_t *gvc;
bool DoLayout(const char * layout, const char* mem, const char* format, const char* scale, std::string & result)
{
	bool retVal = true;
	int  argc = 0;
	char* argv [32];

    gvc = gvContextPlugins(lt_preloaded_symbols, FALSE);
	if (gvc) 
	{
		std::string arg_layout = layout;
		std::string arg_format = "-T";
		std::string arg_scale  = "-s";

		argv[argc++] = const_cast<char*>(arg_layout.c_str());

		if (format) {
			arg_format  += format;
			argv[argc++] = const_cast<char*>(arg_format.c_str());
		}

		if (scale) {
			arg_scale   += scale;
			argv[argc++] = const_cast<char*>(arg_scale.c_str());
		}

		argv[argc] = 0;

		gvParseArgs(gvc, argc, argv);
		graph_t *g = agmemread(const_cast<char *>(mem));

		if (g) 
		{
#ifdef _DEBUG
			std::cerr << std::string("Start - Layout Engine.") << std::endl;
			gvLayout(gvc, g, const_cast<char *>(layout)); 
			gvc->write_fn = &MyWriteFunction;
			gvRenderJobs(gvc, g);
			result = g_result[gvc];
			g_result[gvc].clear();
			gvFreeLayout(gvc, g);
			agclose(g);
			gvFinalize(gvc);
			gvFreeContext(gvc);
			std::cerr << std::string("Stop - Layout Engine.") << std::endl;
#else
			try {
				gvLayout(gvc, g, const_cast<char *>(layout)); 
			} catch (...) {
				std::cerr << std::string("Layout Engine:  Failed at Layout.") << std::endl;
				retVal = false;
			}
			try {
				gvc->write_fn = &MyWriteFunction;
				gvRenderJobs(gvc, g);
				result = g_result[gvc];
				g_result[gvc].clear();
			} catch (...) {
				std::cerr << std::string("Layout Engine:  Failed at RenderJobs.") << std::endl;
				retVal = false;
			}
			try {
				gvFreeLayout(gvc, g);
			} catch (...) {
				std::cerr << std::string("Layout Engine:  Failed at FreeLayout.") << std::endl;
			}
			try {
				agclose(g);
			} catch (...) {
				std::cerr << std::string("Layout Engine:  Failed at Close.") << std::endl;
			}
			try {
				gvFinalize(gvc);
			} catch (...) {
				std::cerr << std::string("Layout Engine:  Failed at Finalize.") << std::endl;
			}
			try {
				gvFreeContext(gvc);
			} catch (...) {
				std::cerr << std::string("Layout Engine:  Failed at FreeContext.") << std::endl;
			}
#endif
		}
		global_cleanup();
	}

	return retVal;
}

#ifdef DOT_PARSER
static int internalID = 0;
void gatherAttrs(Agraph_t * graph, void * item, int type, AttrMap & attrs)
{
	attrs.clear();
#if WITH_CGRAPH
	Agsym_t *attr = NULL;
	while ((attr = agnxtattr(graph, type, attr)))
	{
		if (agget(item, attr->name) != NULL)
		{
			std::string val = agget(item, attr->name);
			attrs[attr->name] = val;
		}
	}

	if (type == AGEDGE)
	{
		Agnode_t * head = aghead((Agedge_t*)item);
		Agnode_t * tail = agtail((Agedge_t*)item);
		attrs["source"] = agnameof(tail);
		attrs["target"] = agnameof(head);
	}

	if (attrs.find("id") == attrs.end())
	{
		char * name = agnameof(item);
		if (name && name[0] != '\0')
		{
			if (type == AGRAPH && boost::algorithm::istarts_with(name, "cluster"))
			{
				attrs["id"] = (name + sizeof("cluster") - 1);
			}
			else
			{
				attrs["id"] = name;
			}
		}
		else if (type == AGEDGE)  //  Anonymous edge
		{
			attrs["id"] = attrs["source"] + "_" + attrs["target"];
		}
		else
		{
			attrs["id"] = std::string("internal_") + boost::lexical_cast<std::string>(internalID++);
		}
	}
#else
	for (Agsym_t *attr = agfstattr(item); attr; attr = agnxtattr(item, attr))
	{
		if (strcmp(attr->name, "id") != 0 &&
			agxget(item, attr->index) != NULL && strcmp(agxget(item, attr->index), "\\N") != 0)
			attrs[attr->name] = agxget(item, attr->index);
	}
#endif
}

void walkGraph(graph_t * root_g, graph_t * g, IGraphvizVisitor * visitor, int depth)
{
	if (!g) 
		return;

	AttrMap g_attrs;
	gatherAttrs(root_g, g, AGRAPH, g_attrs);

#if WITH_CGRAPH
	depth == 0 ? visitor->OnStartGraph(root_g->desc.directed, g_attrs["id"], g_attrs) : visitor->OnStartCluster(g_attrs["id"], g_attrs);

	graph_t *subg;
	for (subg = agfstsubg(g); subg; subg = agnxtsubg(subg)) {
#else
	depth == 0 ? visitor->OnStartGraph(agisdirected(root_g), g_attrs["id"], g_attrs) : visitor->OnStartCluster(g_attrs["id"], g_attrs);
	graph_t *mg, *subg;
	node_t *mm, *mn;
	edge_t *me;

	mm = g->meta_node;
	mg = mm->graph;
	for (me = agfstout(mg, mm); me; me = agnxtout(mg, me)) {
		mn = me->head;
		subg = agusergraph(mn);
#endif
		walkGraph(root_g, subg, visitor, depth + 1);
	}

	for (Agnode_t *v = agfstnode(g); v; v = agnxtnode(g,v))
	{
		AttrMap v_attrs;
		gatherAttrs(root_g, v, AGNODE, v_attrs);

		visitor->OnStartVertex(v_attrs["id"], v_attrs);
		for (Agedge_t *e = agfstout(g, v); e; e = agnxtout(g, e)) 
		{
			AttrMap e_attrs;
			gatherAttrs(root_g, e, AGEDGE, e_attrs);
#if WITH_CGRAPH
			visitor->OnStartEdge(root_g->desc.directed, e_attrs["id"], e_attrs["source"], e_attrs["target"], e_attrs);
#else
			visitor->OnStartEdge(agisdirected(root_g), e_attrs["id"], e_attrs["source"], e_attrs["target"], e_attrs);
#endif
			visitor->OnEndEdge(e_attrs["id"]);
		}
		visitor->OnEndVertex(v_attrs["id"]);
	}
	depth == 0 ? visitor->OnEndGraph(g_attrs["id"]) : visitor->OnEndCluster(g_attrs["id"]);
}

bool DoParse(const char* mem, IGraphvizVisitor * visitor)
{
	bool retVal = true;
	int  argc = 0;

	gvc = gvContextPlugins(lt_preloaded_symbols, FALSE);
	if (gvc) 
	{
		graph_t *g = agmemread(const_cast<char *>(mem));
		if (g) 
		{
			std::cerr << std::string("Start - Parse.") << std::endl;

			int sg = 0;
			int v = 0;
			int e = 0;
			walkGraph(g, g, visitor, 0);

			agclose(g);
			gvFinalize(gvc);
			gvFreeContext(gvc);
			std::cerr << std::string("Stop - Parse.") << std::endl;
		}
		global_cleanup();
	}

	return retVal;
}
#endif

int shortest_route(Ppoly_t **polys, int num_polys, Ppoint_t * src, Ppoint_t * dst, Ppolyline_t* path)
{
	vconfig_t* vc=Pobsopen(polys, num_polys);
	if(vc!=0)
	{
		int result=Pobspath(vc, *src, POLYID_NONE, *dst, POLYID_NONE, path);
		Pobsclose(vc);
		//free(vc);
		return result;
	}
	return 0;
}

