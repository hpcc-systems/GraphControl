#pragma once
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

namespace hpcc
{
class CDotItem : public CUnknown
{
protected:
	std::string m_dot;
public:
	std::string m_name;
	typedef std::map<std::string, std::string> AttrMap;
	AttrMap m_attrs;

	BEGIN_CUNKNOWN
	END_CUNKNOWN

	CDotItem(const std::string & name, const AttrMap & attrs);

	virtual const std::string ToDot(const std::string & id, const std::string & content) = 0;
};

class CDotGraph : public CDotItem
{
public:
	bool m_directed;

	CDotGraph(bool directed, const std::string & name, const AttrMap & attrs);

	const std::string ToDot(const std::string & id, const std::string & content);
};

class CDotCluster : public CDotItem
{
public:
	CDotCluster(const std::string & name, const AttrMap & attrs);

	const std::string ToDot(const std::string & id, const std::string & content);
};

class CDotVertex : public CDotItem
{
public:
	CDotVertex(const std::string & name, const AttrMap & attrs);

	const std::string ToDot(const std::string & id, const std::string & content);
};
typedef CUnknownPtr<CDotVertex> CDotVertexPtr;

class CDotEdge : public CDotItem
{
public:
	bool m_directed;
	std::string m_source;
	std::string m_target;

	CDotEdge(bool directed, const std::string & name, const std::string & source, const std::string & target, const AttrMap & attrs);

	const std::string ToDot(const std::string & id, const std::string & content);
};
typedef CUnknownPtr<CDotEdge> CDotEdgePtr;
}