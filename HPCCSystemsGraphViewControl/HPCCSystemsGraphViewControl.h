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
#ifdef XP_WIN
#include "PluginEvents/WindowsEvent.h"
#elif defined(XP_UNIX)
#include "PluginEvents/X11Event.h"
#endif
#include "PluginEvents/MouseEvents.h"
#include "PluginEvents/DrawingEvents.h"
#include "PluginEvents/AttachedEvent.h"

#include "PluginCore.h"
#ifdef XP_WIN
#include "DotViewWin.h"
#elif defined(XP_UNIX)
#include "DotViewX11.h"
#endif

FB_FORWARD_PTR(HPCCSystemsGraphViewControl)
class HPCCSystemsGraphViewControl : public FB::PluginCore
{
protected:
	CDotView *m_wnd;

public:
    static void StaticInitialize();
    static void StaticDeinitialize();

public:
    HPCCSystemsGraphViewControl();
    virtual ~HPCCSystemsGraphViewControl();

public:
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

		EVENTTYPE_CASE(FB::RefreshEvent, onRefresh, FB::PluginWindow)
#ifdef XP_WIN
		EVENTTYPE_CASE(FB::WindowsEvent, onWindows, FB::PluginWindow)
#elif defined(XP_UNIX)
		EVENTTYPE_CASE(FB::X11Event, onX11, FB::PluginWindow)
#endif

        EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindow)
        EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindow)
    END_PLUGIN_EVENT_MAP()

    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    virtual bool onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *);
	virtual bool onMouseDoubleClick(FB::MouseDoubleClickEvent *evt, FB::PluginWindow *);
    virtual bool onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *);
    virtual bool onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *);

	virtual bool onRefresh(FB::RefreshEvent *evt, FB::PluginWindow *);

	void DoRender(int x, int y, int width, int height, bool resized);
#ifdef XP_WIN
	virtual bool onWindows(FB::WindowsEvent *evt, FB::PluginWindow *);
#elif defined(XP_UNIX)
	virtual bool onX11(FB::X11Event *evt, FB::PluginWindow *);
#endif

	virtual bool onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow *);
	virtual bool onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *);
	/** END EVENTDEF -- DON'T CHANGE THIS LINE **/
};


#endif

