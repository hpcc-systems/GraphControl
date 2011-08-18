#include "Platform.h"

#include <boost/assert.hpp>

#include "Unknown.h"

#define DESTRUCTOR_REFCOUNT 1042

namespace ln
{
CUnknown::CUnknown() : m_refCount(0)
{
}

CUnknown::CUnknown(const CUnknown & other) : m_refCount(0)
{
}

CUnknown & CUnknown::operator=(const CUnknown & other)
{
    return *this;
}

CUnknown::~CUnknown()
{
}

unsigned long CUnknown::AddRef() throw()
{
	return ++m_refCount;
}

unsigned long CUnknown::Release() throw()
{
	if (!--m_refCount)
	{
		delete this;
		return 0;
	}
	assert(m_refCount > 0);
	return m_refCount;
}
}
