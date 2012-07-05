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

#include "GraphItem.h"
#include "util.h"

namespace hpcc
{
static unsigned int g_id = 0;

CGraphItem::CGraphItem()
{
	m_graph = NULL;
	SetID(++g_id);
}

CGraphItem::CGraphItem(IGraph * graph) : m_graph(graph)
{
	SetID(++g_id);
}

void CGraphItem::SetID(unsigned int id)
{
	m_id = id;
	m_idString = UIntToString(id);
}

void CGraphItem::Clear()
{
	m_propBool.clear();
	m_propInt.clear();
	m_propDouble.clear();
	m_propString.clear();
	m_propIUnknown.clear();
	m_propCUnknown.clear();
	m_propStringString.clear();
}

bool CGraphItem::operator < (const CGraphItem & other) const
{
	return m_id < other.m_id;
}

//  ===  IGraphItem  ===
IGraph * CGraphItem::GetGraph() const
{
	return m_graph;
}

unsigned int CGraphItem::GetID() const
{
	return m_id;
}

const std::string & CGraphItem::GetIDString() const
{
	return m_idString;
}

void CGraphItem::SetProperty(unsigned int key, bool val)
{
	m_propBool[key] = val;
}

bool CGraphItem::GetPropertyBool(unsigned int key) const
{
	IntBoolMap::const_iterator found = m_propBool.find(key);
	if (found != m_propBool.end())
		return found->second;
	return false;
}

void CGraphItem::SetProperty(unsigned int key, int val)
{
	m_propInt[key] = val;
}

int CGraphItem::GetPropertyInt(unsigned int key) const
{
	IntIntMap::const_iterator found = m_propInt.find(key);
	if (found != m_propInt.end())
		return found->second;
	return 0;
}

void CGraphItem::SetProperty(unsigned int key, double val)
{
	m_propDouble[key] = val;
}

double CGraphItem::GetPropertyDouble(unsigned int key) const
{
	IntDoubleMap::const_iterator found = m_propDouble.find(key);
	if (found != m_propDouble.end())
		return found->second;
	return 0.0f;
}

void CGraphItem::SetProperty(unsigned int key, const char * val)
{
	m_propString[key] = val;
	boost::algorithm::trim(m_propString[key]);
}

bool CGraphItem::HasPropertyString(unsigned int key) const 
{
	IntStringMap::const_iterator found = m_propString.find(key);
	return (found != m_propString.end());
}

const char * CGraphItem::GetPropertyString(unsigned int key) const
{
	IntStringMap::const_iterator found = m_propString.find(key);
	if (found != m_propString.end())
		return found->second.c_str();
	return m_blankString.c_str();
}

void CGraphItem::SetProperty(unsigned int key, IUnknown * val)
{
	m_propIUnknown[key] = val;
}

IUnknown * CGraphItem::GetPropertyIUnknown(unsigned int key) const
{
	IntIUnknownMap::const_iterator found = m_propIUnknown.find(key);
	if (found != m_propIUnknown.end())
		return found->second;
	return NULL;
}

void CGraphItem::SetProperty(unsigned int key, CUnknown * val)
{
	m_propCUnknown[key] = val;
}

CUnknown * CGraphItem::GetPropertyCUnknown(unsigned int key) const
{
	IntCUnknownMap::const_iterator found = m_propCUnknown.find(key);
	if (found != m_propCUnknown.end())
		return found->second;
	return NULL;
}

void CGraphItem::SetProperty(const std::string & key, const std::string & val)
{
	m_propStringString[key] = val;
}

const char * CGraphItem::GetProperty(const std::string & key) const
{
	StringStringMap::const_iterator found = m_propStringString.find(key);
	if (found != m_propStringString.end())
		return found->second.c_str();
	return NULL;
}

int CGraphItem::GetProperties(StringStringMap & results) const 
{ 
	results = m_propStringString;
	return results.size();
}
}
