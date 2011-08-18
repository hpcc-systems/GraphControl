/**********************************************************\

  Auto-generated HPCCSystemsGraphViewControl.cpp

  This file contains the auto-generated main plugin object
  implementation for the HPCCSystemsGraphViewControl project

\**********************************************************/
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
typedef boost::shared_ptr<HPCCSystemsGraphViewControl> HPCCSystemsGraphViewControlPtr;
typedef boost::weak_ptr<HPCCSystemsGraphViewControl> HPCCSystemsGraphViewControlWeakPtr;


#endif

