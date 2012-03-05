#pragma once

#include "GraphBuffer.h"

namespace hpcc
{
hpcc_interface GRAPHRENDER_API IFontResolver : public IUnknown
{
public:
	virtual const char * GetPath(const std::string & fontName) = 0;
	virtual const char * GetDefaultPath() = 0;
	virtual double GetDefaultSize() = 0;
};
typedef CUnknownPtr<IFontResolver> IFontResolverPtr;

IFontResolver * CreateIFontResolver();
}
