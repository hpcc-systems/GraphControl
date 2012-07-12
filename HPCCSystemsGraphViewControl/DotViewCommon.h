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

#include "GraphDB.h"
#include "GraphvizLayout.h"
#include "GraphRender.h"
#include "GraphHotItem.h"

class HPCCSystemsGraphViewControlAPI;
class CDotViewCommon
{
public:
	HPCCSystemsGraphViewControlAPI * m_api;
	hpcc::IGraphBufferPtr m_buffer;
	hpcc::IGraphPtr m_g;
	hpcc::IGraphRenderPtr m_gr;
	//hpcc::IGraphRenderPtr m_gro;
	hpcc::IGraphHotItemPtr m_hotItem;
	hpcc::IGraphSelectionBagPtr m_selection;

	enum MOUSEDOWN
	{
		MOUSEDOWN_UNKNOWN = 0,
		MOUSEDOWN_NORMAL,
		MOUSEDOWN_DBLCLK,
		MOUSEDOWN_OVERVIEW,
		MOUSEDOWN_OVERVIEW_WIN,
		MOUSEDOWN_MOVED,
		MOUSEDOWN_LAST

	} m_mouseDown;
	int m_mouseDownPosX;
	int m_mouseDownPosY;
	int m_scrollDownPosX;
	int m_scrollDownPosY;

	std::string m_dot;
	std::string m_svg;

	CDotViewCommon();

	virtual void Invalidate() = 0;
	virtual int GetScrollOffsetX() = 0;
	virtual int GetScrollOffsetY() = 0;
	virtual void SetScrollOffset(int x, int y) = 0;
	virtual void SetScrollSize(int w, int h, bool redraw) = 0;
	virtual bool GetClientRectangle(hpcc::RectD & rect) = 0;
	virtual void UpdateWindow() = 0;
	virtual void InvalidateSelection() = 0;
	virtual void operator()(const std::string & dot, const std::string & svg) = 0;

	//  --- IAPICallback ---
	void Clear();
	void LoadTestData();
	void LoadXML(const std::string & verticesXML, const std::string & edgesXML);
	void LoadXML2(const std::string & xml);
	void LoadXGMML(const std::string & xgmml);
	void MergeXGMML(const std::string & xgmml);
	void MergeSVG(const std::string & svg);
	void LoadDOT(const std::string & dot);
	const std::string GetSVG();
	const std::string GetDOT();
	const char * GetLocalisedXGMML(const std::vector<int> & items, int localisationDepth, int localisationDistance, std::string & xgmml);
	double SetScale(double scale);
	double GetScale();
	virtual void CenterOnGraphItem(hpcc::IGraphItem * item = NULL);
	virtual void CenterOnItem(int item, bool sizeToFit, bool widthOnly);
	void StartLayout(const std::string & layout);
	void SetMessage(const std::string & msg);
	int Find(const std::string & text, bool includeProperties, std::vector<int> & results);
	bool HasItems();
	int GetSelection(std::vector<int> & results);
	int GetSelection(std::vector<std::string> & results);
	bool SetSelected(const std::vector<int> & items, bool clearPrevious);
	bool SetSelected(const std::vector<std::string> & items, bool clearPrevious);
	const hpcc::IClusterSet & GetClusters();
	int GetProperties(int item, hpcc::StringStringMap & results);
	unsigned int GetItem(const std::string &externalID);
	const char * GetGlobalID(int item);
	int GetVertices(std::vector<int> & results);
	//  --- IAPICallback ---

	void CenterOn(const hpcc::PointD & worldPoint);
	void MoveTo(const hpcc::PointD & worldPoint, int x, int y);
	hpcc::PointD GetCenterAsWorldPoint();
	void CalcScrollbars(bool redraw = false);
};

