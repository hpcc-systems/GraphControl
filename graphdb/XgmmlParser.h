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