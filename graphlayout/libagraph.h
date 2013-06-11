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

#ifdef WIN32
#  ifdef GRAPHLAYOUT_STATIC
#    define LIBAGRAPH_API __declspec(dllexport)
#  elif defined GRAPHLAYOUT_EXPORTS
#    define LIBAGRAPH_API __declspec(dllexport)
#  else
#    define LIBAGRAPH_API __declspec(dllimport)
#  endif
#else
#	if __GNUC__ >= 4
#		define LIBAGRAPH_API __attribute__ ((visibility("default")))
#	else
#		define LIBAGRAPH_API
#	endif
#endif

#ifdef _MSC_VER
#ifndef interface
#define interface    struct __declspec(novtable)
#endif
#else
#ifndef interface
#define interface    struct
#endif
#endif

LIBAGRAPH_API bool DoLayout(const char * layout, const char* mem, const char* format, const char* scale, std::string & result);

#define DOT_PARSER
#ifdef DOT_PARSER
typedef std::map<std::string, std::string> AttrMap;
interface IGraphvizVisitor
{
	virtual void OnStartGraph(bool directed, const std::string & id, const AttrMap & attrs) = 0;
	virtual void OnEndGraph(const std::string & id) = 0;

	virtual void OnStartCluster(const std::string & id, const AttrMap & attrs) = 0;
	virtual void OnEndCluster(const std::string & id) = 0;

	virtual void OnStartVertex(int id, const AttrMap & attrs) = 0;
	virtual void OnEndVertex(int id) = 0;
	virtual void OnStartVertex(const std::string & id, const AttrMap & attrs) = 0;
	virtual void OnEndVertex(const std::string & id) = 0;

	virtual void OnStartEdge(bool directed, const std::string & id, const std::string & sourceID, const std::string & targetID, const AttrMap & attrs) = 0;
	virtual void OnEndEdge(const std::string & id) = 0;
};

LIBAGRAPH_API bool DoParse(const char* mem, IGraphvizVisitor * visitor);
#endif