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

#include "GraphvizLayout.h"
#include "SvgParser.h"

#include <libagraph.h>

#ifdef _DEBUG
#include <fstream>
#endif

namespace hpcc
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

const char * DoGraphvizLayoutFromDot(IGraph * g, const std::string & generatedDot, const LayoutFinishedSlot & slot)
{
	boost::thread run(boost::bind(&thread_DoGraphvizLayout, g->GetPropertyString(PROP_LAYOUT), generatedDot, slot));
	return generatedDot.c_str();
}

}