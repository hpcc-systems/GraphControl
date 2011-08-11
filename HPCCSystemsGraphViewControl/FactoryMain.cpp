/**********************************************************\

  Auto-generated FactoryMain.cpp

  This file contains the auto-generated factory methods
  for the HPCCSystems Graph View Control project

\**********************************************************/

#include "FactoryDefinitions.h"
#include "HPCCSystemsGraphViewControl.h"

FB::PluginCore *_getMainPlugin()
{
    return new HPCCSystemsGraphViewControl();
}

void GlobalPluginInitialize()
{
    HPCCSystemsGraphViewControl::StaticInitialize();
}

void GlobalPluginDeinitialize()
{
    HPCCSystemsGraphViewControl::StaticDeinitialize();
}
