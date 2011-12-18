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

#include "XmlParser.h"

namespace ln
{
enum XGMML_PROP
{
	XGMML_PROP_UNKNOWN = SVG_PROP_LAST,
	XGMML_GLOBAL_USAGE_COUNT,
	XGMML_IS_SPILL,
	XGMML_DOTTED,
	XGMML_STATE,
	XGMML_PROP_LAST
};

enum XGMML_STATE_ENUM
{
	XGMML_STATE_UNKNOWN = 0,
	XGMML_STATE_COMPLETED,
	XGMML_STATE_RUNNING,
	XGMML_STATE_LAST
};

ICluster * GetCluster(IGraph* graph, ICluster* cluster, unsigned int id, const std::string & label, bool merge, bool appendMissing);
GRAPHDB_API bool LoadXGMML(IGraph * graph, const std::string & xgmml);
GRAPHDB_API bool MergeXGMML(IGraph * graph, const std::string & xgmml);
}