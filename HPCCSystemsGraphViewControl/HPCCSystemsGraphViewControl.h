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
#ifndef H_HPCCSystemsGraphViewControlPLUGIN
#define H_HPCCSystemsGraphViewControlPLUGIN

#include "PluginWindow.h"
#include "PluginEvents/MouseEvents.h"
#include "PluginEvents/DrawingEvents.h"
#include "PluginEvents/AttachedEvent.h"

#include "PluginCore.h"

#include <boost/smart_ptr/detail/atomic_count.hpp>
#include <boost/signals2.hpp>

#include <GraphDB.h>
#include <GraphvizLayout.h>
#include <GraphRender.h>
#include <GraphHotItem.h>

FB_FORWARD_PTR(HPCCSystemsGraphViewControl)
class HPCCSystemsGraphViewControl : public FB::PluginCore
{
protected:
	hpcc::IGraphBufferPtr m_buffer;
	hpcc::IGraphPtr m_g;
	hpcc::IGraphRenderPtr m_gr;
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

	hpcc::PointD m_ptOffset;
	hpcc::PointD m_ptSize;

	mutable boost::recursive_mutex m_pendingMutex;
	std::string m_pendingDot;
	std::string m_pendingSvg;

public:
    static void StaticInitialize();
    static void StaticDeinitialize();

public:
    HPCCSystemsGraphViewControl();
    virtual ~HPCCSystemsGraphViewControl();

public:
	void Invalidate();
	void InvalidateWorldRect(const hpcc::RectD & worldRect);
	int GetScrollOffsetX();
	int GetScrollOffsetY();
	void SetScrollOffset(int x, int y);
	void SetScrollSize(int w, int h, bool redraw);
    bool GetClientRectangle(hpcc::RectD & rect);
	void InvalidateSelection();
	void operator()(const std::string & dot, const std::string & svg);

	void CalcScrollbars(bool redraw = false);
	void CenterOn(const hpcc::PointD & worldPoint);
	void MoveTo(const hpcc::PointD & worldPoint, int x, int y);
	hpcc::PointD GetCenterPoint(bool world);

	//  --- IAPICallback ---
	void Clear();
	void LoadTestData();
	void LoadXML(const std::string & verticesXML, const std::string & edgesXML);
	void LoadXML2(const std::string & xml);
	void LoadXGMML(const std::string & xgmml);
	void MergeXGMML(const std::string & xgmml);
	bool MergeSVG(const std::string & svg);
	void LoadDOT(const std::string & dot);
	const std::string GetSVG();
	const std::string GetDOT();
	const char * GetLocalisedXGMML(const std::vector<int> & items, int localisationDepth, int localisationDistance, std::string & xgmml);
	double SetScale(double scale);
	double GetScale();
	void CenterOnGraphItem(hpcc::IGraphItem * item = NULL);
	void CenterOnItem(int item, bool sizeToFit, bool widthOnly);
	void StartLayout(const std::string & layout);
	void SetMessage(const std::string & msg);
	int Find(const std::string & text, bool includeProperties, std::vector<int> & results);
	bool HasItems();
	int GetSelection(std::vector<int> & results);
	int GetSelection(std::vector<std::string> & results);
	bool SetSelected(const std::vector<int> & items, bool clearPrevious);
	bool SetSelected(const std::vector<std::string> & items, bool clearPrevious);
	const hpcc::IClusterSet & GetClusters();
	int GetProperties(int item, hpcc::ciStringStringMap & results);
	void SetProperty(int item, const std::string & key, const std::string & value);
	const char * GetProperty(int item, const std::string & key);
	unsigned int GetItem(const std::string &externalID);
	const char * GetGlobalID(int item);
	int GetClusters(std::vector<int> & results);
	int GetVertices(std::vector<int> & results);
	int GetEdges(std::vector<int> & results);
	//  --- IAPICallback ---

    void onPluginReady();
    void shutdown();
    virtual FB::JSAPIPtr createJSAPI();
    // If you want your plugin to always be windowless, set this to true
    // If you want your plugin to be optionally windowless based on the
    // value of the "windowless" param tag, remove this method or return
    // FB::PluginCore::isWindowless()
    virtual bool isWindowless() { return false; }

    BEGIN_PLUGIN_EVENT_MAP()
        EVENTTYPE_CASE(FB::MouseDownEvent, onMouseDown, FB::PluginWindow)
		EVENTTYPE_CASE(FB::MouseDoubleClickEvent, onMouseDoubleClick, FB::PluginWindow)
        EVENTTYPE_CASE(FB::MouseUpEvent, onMouseUp, FB::PluginWindow)
        EVENTTYPE_CASE(FB::MouseMoveEvent, onMouseMove, FB::PluginWindow)
        EVENTTYPE_CASE(FB::MouseMoveEvent, onMouseMove, FB::PluginWindow)
        EVENTTYPE_CASE(FB::MouseScrollEvent, onMouseScroll, FB::PluginWindow)
		EVENTTYPE_CASE(FB::ResizedEvent, onResized, FB::PluginWindow)
		EVENTTYPE_CASE(FB::RefreshEvent, onRefresh, FB::PluginWindow)
        EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindow)
        EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindow)
    END_PLUGIN_EVENT_MAP()

    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    virtual bool onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *);
	virtual bool onMouseDoubleClick(FB::MouseDoubleClickEvent *evt, FB::PluginWindow *);
    virtual bool onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *);
    virtual bool onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *);
    virtual bool onMouseScroll(FB::MouseScrollEvent *evt, FB::PluginWindow *);
	virtual bool onResized(FB::ResizedEvent *evt, FB::PluginWindow *);
	virtual bool onRefresh(FB::RefreshEvent *evt, FB::PluginWindow *);
    virtual bool onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow *);
    virtual bool onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *);
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/
	void FinishLayout();
};


#endif

