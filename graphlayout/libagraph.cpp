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
extern Agraph_t *agmemread(char *);
#else
#include <graph.h> // needed to cure VS7 linker error
//extern Agraph_t *agfstsubg(Agraph_t * g), *agnxtsubg(Agraph_t * subg);
#endif

//
//// required for exporting shortest_route
//
#include <vispath.h>
#include "libagraphsp.h"

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

void gatherAttrs(void * item, AttrMap & attrs)
{
	attrs.clear();
	for (Agsym_t *attr = agfstattr(item); attr; attr = agnxtattr(item, attr))
	{
		if (strcmp(attr->name, "id") != 0 &&
			agxget(item, attr->index) != NULL && strlen(agxget(item, attr->index)) != 0 && strcmp(agxget(item, attr->index), "\\N") != 0)
			attrs[attr->name] = agxget(item, attr->index);
	}
}

void walkGraph(graph_t * g, IGraphvizVisitor * visitor, int depth)
{
	if (!g) 
		return;

	AttrMap attrs;
	gatherAttrs(g, attrs);

	depth == 0 ? visitor->OnStartGraph(g->kind, g->name, attrs) : visitor->OnStartCluster(g->name, attrs);

	graph_t *mg, *subg;
	node_t *mm, *mn;
	edge_t *me;

	mm = g->meta_node;
	mg = mm->graph;
	for (me = agfstout(mg, mm); me; me = agnxtout(mg, me)) {
		mn = me->head;
		subg = agusergraph(mn);
		walkGraph(subg, visitor, depth + 1);
	}

	for (Agnode_t *v = agfstnode(g); v; v = agnxtnode(g,v))
	{
		gatherAttrs(v, attrs);
		visitor->OnStartVertex(v->name, attrs);
		for (Agedge_t *e = agfstout(g, v); e; e = agnxtout(g, e)) 
		{
			gatherAttrs(e, attrs);

			char buff[16];
			visitor->OnStartEdge(g->kind, boost::lexical_cast<std::string>(e->id).c_str(), e->tail->name, e->head->name, attrs);
			visitor->OnEndEdge(g->kind, buff);
		}
		visitor->OnEndVertex(v->name);
	}
	depth == 0 ? visitor->OnEndGraph(g->kind, g->name) : visitor->OnEndCluster(g->name);
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
			walkGraph(g, visitor, 0);

			agclose(g);
			gvFinalize(gvc);
			gvFreeContext(gvc);
			std::cerr << std::string("Stop - Parse.") << std::endl;
		}
		global_cleanup();
	}

	return retVal;
}

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

