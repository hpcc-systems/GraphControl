#include "Platform.h"

#include <boost/signals2.hpp>
#include <boost/thread.hpp>

#include "GraphvizLayout.h"
#include "SvgParser.h"

#include <libagraph.h>

#ifdef _DEBUG
#include <fstream>
#endif

namespace ln
{
boost::recursive_mutex g_mutex;

void DoGraphvizLayout(std::string layout, const std::string & dotStr, std::string & svgStr)
{
	boost::recursive_mutex::scoped_lock lock(g_mutex);
#ifdef _DEBUG
	{
		std::ofstream fileDot("c:\\temp\\GraphvizLayout.dot", std::ios::binary);
		fileDot << dotStr;
	}
#endif
	if (layout.empty())
		layout = "dot";
	DoLayout(layout.c_str(), dotStr.c_str(), "svg", NULL, svgStr);
#ifdef _DEBUG
	{
		std::ofstream fileSvg("c:\\temp\\GraphvizLayout.svg", std::ios::binary);
		fileSvg << svgStr;
	}
#endif
}

const char * DoGraphvizLayout(IGraph * g, std::string & svgStr)
{
	std::string dotStr;
	WriteDOT(g, dotStr);
	std::string layout = g->GetPropertyString(PROP_LAYOUT);
	DoGraphvizLayout(layout, dotStr, svgStr);
	return svgStr.c_str();
}

void thread_DoGraphvizLayout(std::string layout, std::string dotStr, const LayoutFinishedSlot & slot)
{
	boost::recursive_mutex::scoped_lock lock(g_mutex);
	LayoutFinishedSignal sig;
	boost::signals2::connection c = sig.connect(slot);

	std::string svgStr;
	DoGraphvizLayout(layout, dotStr, svgStr);
	sig(dotStr, svgStr);
}

const char * DoGraphvizLayout(IGraph * g, std::string & generatedDot, const LayoutFinishedSlot & slot)
{
	WriteDOT(g, generatedDot);
	boost::thread run(boost::bind(&thread_DoGraphvizLayout, g->GetPropertyString(PROP_LAYOUT), generatedDot, slot));
	return generatedDot.c_str();
}
}