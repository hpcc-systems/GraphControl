#pragma once

#include "GraphDB.h"

#include <boost/signals2.hpp>

namespace ln
{
typedef boost::signals2::signal<void(const std::string & dot, const std::string & svg)> LayoutFinishedSignal;
typedef LayoutFinishedSignal::slot_type LayoutFinishedSlot;

GRAPHDB_API const char * DoGraphvizLayout(IGraph * g, std::string & svg);
GRAPHDB_API const char * DoGraphvizLayout(IGraph * g, std::string & generatedDot, const LayoutFinishedSlot & slot);
}
