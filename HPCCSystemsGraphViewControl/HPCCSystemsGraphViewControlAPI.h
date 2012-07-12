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

#include "Unknown.h"

#include "HPCCSystemsGraphViewControl.h"

#ifndef H_HPCCSystemsGraphViewControlAPI
#define H_HPCCSystemsGraphViewControlAPI

class HPCCSystemsGraphViewControlAPI : public FB::JSAPIAuto
{
private:
	HPCCSystemsGraphViewControlAPI()
	{
		assert(false);
	}

	HPCCSystemsGraphViewControlAPI(const HPCCSystemsGraphViewControlAPI & other)
	{
		assert(false);
	}
public:
	CDotView * m_callback;

	HPCCSystemsGraphViewControlAPI(const HPCCSystemsGraphViewControlPtr& plugin, const FB::BrowserHostPtr& host, CDotView * callback);
    virtual ~HPCCSystemsGraphViewControlAPI();

    HPCCSystemsGraphViewControlPtr getPlugin();

    // Read/Write property ${PROPERTY.ident}
    std::string get_testString();
    void set_testString(const std::string& val);

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Methods 
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

	FB::VariantMap getProperties(int item);
	std::string getProperty(int item, const std::string & key);

	int getItem(const std::string & externalID);
	std::string getGlobalID(int item);
	FB::VariantList getVertices();

	bool onMouseWheel(unsigned int nFlags, short zDelta, int x, int y);

	bool setMessage(const std::string& msg);

    // Method test-event
    void testEvent(const FB::variant& s);

	//  Fire Events
	FB_JSAPI_EVENT(Scaled, 1, (int));
	FB_JSAPI_EVENT(LayoutFinished, 0, ());
	FB_JSAPI_EVENT(MouseDoubleClick, 1, (int));
	FB_JSAPI_EVENT(SelectionChanged, 1, (FB::VariantList));

private:
    HPCCSystemsGraphViewControlWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;
};

#endif // H_HPCCSystemsGraphViewControlAPI

