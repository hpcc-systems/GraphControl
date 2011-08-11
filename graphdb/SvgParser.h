#pragma once

#include "GraphDB.h"
#include "SvgShapes.h"

namespace ln
{
enum SVG_PROP
{
	SVG_PROP_UNKNOWN = PROP_LAST,
	SVG_PROP_ELEMENTG,
	SVG_PROP_VIEWBOX_X,
	SVG_PROP_VIEWBOX_Y,
	SVG_PROP_VIEWBOX_W,
	SVG_PROP_VIEWBOX_H,
	SVG_PROP_LAST
};

GRAPHDB_API void MergeSVG(IGraph * graph, const std::string & svg);

GRAPHDB_API ElementG * GetElementG(IGraphItem * item);
}