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

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "HPCCSystemsGraphViewControl.h"

#ifndef H_HPCCSystemsGraphViewControlAPI
#define H_HPCCSystemsGraphViewControlAPI

class HPCCSystemsGraphViewControlAPI : public FB::JSAPIAuto
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// @fn HPCCSystemsGraphViewControlAPI::HPCCSystemsGraphViewControlAPI(const HPCCSystemsGraphViewControlPtr& plugin, const FB::BrowserHostPtr host)
    ///
    /// @brief  Constructor for your JSAPI object.
    ///         You should register your methods, properties, and events
    ///         that should be accessible to Javascript from here.
    ///
    /// @see FB::JSAPIAuto::registerMethod
    /// @see FB::JSAPIAuto::registerProperty
    /// @see FB::JSAPIAuto::registerEvent
    ////////////////////////////////////////////////////////////////////////////
    HPCCSystemsGraphViewControlAPI(const HPCCSystemsGraphViewControlPtr& plugin, const FB::BrowserHostPtr& host) :
        m_plugin(plugin), m_host(host)
    {
        
        registerProperty("version", make_property(this, &HPCCSystemsGraphViewControlAPI::get_version));
        registerProperty("version_major", make_property(this, &HPCCSystemsGraphViewControlAPI::get_versionMajor));
        registerProperty("version_minor", make_property(this, &HPCCSystemsGraphViewControlAPI::get_versionMinor));
        registerProperty("version_point", make_property(this, &HPCCSystemsGraphViewControlAPI::get_versionPoint));
        registerProperty("version_sequence", make_property(this, &HPCCSystemsGraphViewControlAPI::get_versionSequence));
	
		registerMethod("clear", make_method(this, &HPCCSystemsGraphViewControlAPI::clear));
		registerMethod("loadXGMML", make_method(this, &HPCCSystemsGraphViewControlAPI::loadXGMML));
		registerMethod("mergeXGMML", make_method(this, &HPCCSystemsGraphViewControlAPI::mergeXGMML));
		registerMethod("mergeSVG", make_method(this, &HPCCSystemsGraphViewControlAPI::mergeSVG));
		registerMethod("loadDOT", make_method(this, &HPCCSystemsGraphViewControlAPI::loadDOT));
		registerMethod("startLayout", make_method(this, &HPCCSystemsGraphViewControlAPI::startLayout));
		registerMethod("setScale", make_method(this, &HPCCSystemsGraphViewControlAPI::setScale));
		registerMethod("getScale", make_method(this, &HPCCSystemsGraphViewControlAPI::getScale));
		registerMethod("centerOnItem", make_method(this, &HPCCSystemsGraphViewControlAPI::centerOnItem));
		registerMethod("setMessage", make_method(this, &HPCCSystemsGraphViewControlAPI::setMessage));
		registerMethod("find", make_method(this, &HPCCSystemsGraphViewControlAPI::find));
		registerMethod("hasItems", make_method(this, &HPCCSystemsGraphViewControlAPI::hasItems));
		registerMethod("getSelection", make_method(this, &HPCCSystemsGraphViewControlAPI::getSelection));
		registerMethod("getSelectionAsGlobalID", make_method(this, &HPCCSystemsGraphViewControlAPI::getSelectionAsGlobalID));
		registerMethod("setSelected", make_method(this, &HPCCSystemsGraphViewControlAPI::setSelected));
		registerMethod("setSelectedAsGlobalID", make_method(this, &HPCCSystemsGraphViewControlAPI::setSelectedAsGlobalID));
		registerMethod("setControlProperty", make_method(this, &HPCCSystemsGraphViewControlAPI::setControlProperty));
		registerMethod("getControlProperty", make_method(this, &HPCCSystemsGraphViewControlAPI::getControlProperty));
		registerMethod("getProperties", make_method(this, &HPCCSystemsGraphViewControlAPI::getProperties));
		registerMethod("setProperty", make_method(this, &HPCCSystemsGraphViewControlAPI::setProperty));
		registerMethod("getProperty", make_method(this, &HPCCSystemsGraphViewControlAPI::getProperty));
		registerMethod("getItem", make_method(this, &HPCCSystemsGraphViewControlAPI::getItem));
		registerMethod("getGlobalID", make_method(this, &HPCCSystemsGraphViewControlAPI::getGlobalID));
		registerMethod("getVertices", make_method(this, &HPCCSystemsGraphViewControlAPI::getVertices));
		registerMethod("onMouseWheel", make_method(this, &HPCCSystemsGraphViewControlAPI::onMouseWheel));
		registerMethod("getRunningSubgraph", make_method(this, &HPCCSystemsGraphViewControlAPI::getRunningSubgraph));

		registerMethod("loadTestData", make_method(this, &HPCCSystemsGraphViewControlAPI::loadTestData));
		registerMethod("loadXML", make_method(this, &HPCCSystemsGraphViewControlAPI::loadXML));
		registerMethod("loadXML2", make_method(this, &HPCCSystemsGraphViewControlAPI::loadXML2));
		registerMethod("getSVG", make_method(this, &HPCCSystemsGraphViewControlAPI::getSVG));
		registerMethod("getDOT", make_method(this, &HPCCSystemsGraphViewControlAPI::getDOT));
		registerMethod("getLocalisedXGMML", make_method(this, &HPCCSystemsGraphViewControlAPI::getLocalisedXGMML));

		registerMethod("getSubgraphsWithProperties", make_method(this, &HPCCSystemsGraphViewControlAPI::getSubgraphsWithProperties));
		registerMethod("getVerticesWithProperties", make_method(this, &HPCCSystemsGraphViewControlAPI::getVerticesWithProperties));
		registerMethod("getEdgesWithProperties", make_method(this, &HPCCSystemsGraphViewControlAPI::getEdgesWithProperties));
	}

    ///////////////////////////////////////////////////////////////////////////////
    /// @fn HPCCSystemsGraphViewControlAPI::~HPCCSystemsGraphViewControlAPI()
    ///
    /// @brief  Destructor.  Remember that this object will not be released until
    ///         the browser is done with it; this will almost definitely be after
    ///         the plugin is released.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~HPCCSystemsGraphViewControlAPI() {};

    HPCCSystemsGraphViewControlPtr getPlugin();

    std::string get_version() const;
    int get_versionMajor() const;
    int get_versionMinor() const;
    int get_versionPoint() const;
    int get_versionSequence() const;

    // Method echo
	void loadTestData();
	bool loadXML(const std::string& verticesXML, const std::string& edgesXML);
	bool loadXML2(const std::string& xml);
	const std::string getSVG();
	const std::string getDOT();
	const std::string getLocalisedXGMML(const std::vector<int> & items, boost::optional<int> localisationDepth, boost::optional<int> localisationDistance);

	bool clear();
	bool loadXGMML(const std::string& xgmml);
	bool mergeXGMML(const std::string& xgmml);
	bool mergeSVG(const std::string& svg);
	bool loadDOT(const std::string& dot);
	bool startLayout(const std::string& layout);

	int setScale(int percent);
	int getScale();
	bool centerOnItem(int item, boost::optional<bool> scaleToFit, boost::optional<bool> widthOnly);
	FB::VariantList find(const std::string & text, boost::optional<bool> includeProperties);
	bool hasItems();

	FB::VariantList getSelection();
	FB::VariantList getSelectionAsGlobalID();
	bool setSelected(const std::vector<int> & items, boost::optional<bool> clearPrevious);
	bool setSelectedAsGlobalID(const std::vector<std::string> & items, boost::optional<bool> clearPrevious);
	int getRunningSubgraph();

	bool setControlProperty(const std::string & key, const std::string & value);
	std::string getControlProperty(const std::string & key);
	FB::VariantMap getProperties(int item);
	FB::VariantList getPropertiesForItems(const std::vector<int> & items);
	bool setProperty(int item, const std::string & key, const std::string & value);
	std::string getProperty(int item, const std::string & key);

	int getItem(const std::string & externalID);
	std::string getGlobalID(int item);

	FB::VariantList getSubgraphsWithProperties();

	FB::VariantList getVertices();
	FB::VariantList getVerticesWithProperties();

	FB::VariantList getEdgesWithProperties();
	
	bool onMouseWheel(unsigned int nFlags, short zDelta, int x, int y);

	bool setMessage(const std::string& msg);

    FB::variant echo(const FB::variant& msg);
    
    // Event helpers
    FB_JSAPI_EVENT(test, 0, ());
    FB_JSAPI_EVENT(echo, 2, (const FB::variant&, const int));

    // Method test-event
    void testEvent();

	//  Fire Events
	FB_JSAPI_EVENT(Scaled, 1, (const int));
	FB_JSAPI_EVENT(LayoutFinished, 0, ());
	FB_JSAPI_EVENT(MouseDoubleClick, 1, (const int));
	FB_JSAPI_EVENT(SelectionChanged, 1, (const FB::VariantList &));

private:
    HPCCSystemsGraphViewControlWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;
};

#endif // H_HPCCSystemsGraphViewControlAPI

