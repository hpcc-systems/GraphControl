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

#include <boost/algorithm/string.hpp>

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "HPCCSystemsGraphViewControlAPI.h"
#include <XgmmlParser.h>

#include "Version.h"

///////////////////////////////////////////////////////////////////////////////
/// @fn HPCCSystemsGraphViewControlPtr HPCCSystemsGraphViewControlAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
HPCCSystemsGraphViewControlPtr HPCCSystemsGraphViewControlAPI::getPlugin()
{
    HPCCSystemsGraphViewControlPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

std::string HPCCSystemsGraphViewControlAPI::get_version() const
{
    return hpcc_version;
}

int HPCCSystemsGraphViewControlAPI::get_versionMajor() const
{
	return hpcc_major;
}

int HPCCSystemsGraphViewControlAPI::get_versionMinor() const
{
	return hpcc_minor;
}

int HPCCSystemsGraphViewControlAPI::get_versionPoint() const
{
	return hpcc_point;
}

int HPCCSystemsGraphViewControlAPI::get_versionSequence() const
{
	return hpcc_sequence;
}

bool HPCCSystemsGraphViewControlAPI::clear()
{
	getPlugin()->Clear();
	return true;
}

bool HPCCSystemsGraphViewControlAPI::loadXGMML(const std::string& xgmml)
{
	if (xgmml.empty())
	{
		getPlugin()->Clear();
		return true;
	}
	getPlugin()->LoadXGMML(xgmml);
	return true;
}

bool HPCCSystemsGraphViewControlAPI::mergeXGMML(const std::string& xgmml)
{
	getPlugin()->MergeXGMML(xgmml);
	return true;
}

bool HPCCSystemsGraphViewControlAPI::mergeSVG(const std::string& svg)
{
	return getPlugin()->MergeSVG(svg);
}

bool HPCCSystemsGraphViewControlAPI::loadDOT(const std::string& dot)
{
    assert(getPlugin() != NULL);
	if (dot.empty())
	{
		getPlugin()->Clear();
		return true;
	}
	getPlugin()->LoadDOT(dot);
	return true;
}

bool HPCCSystemsGraphViewControlAPI::startLayout(const std::string& layout, boost::optional<std::string> attributes)
{
	getPlugin()->StartLayout(layout, attributes ? *attributes : "");
	return true;
}

int HPCCSystemsGraphViewControlAPI::setScale(int percent)
{
	double newScale = percent;
	double oldScale = getPlugin()->SetScale(newScale / 100) * 100;
	return (int)oldScale;
}

int HPCCSystemsGraphViewControlAPI::getScale()
{
	return (int)getPlugin()->GetScale() * 100;
}

bool HPCCSystemsGraphViewControlAPI::centerOnItem(int item, boost::optional<bool> scaleToFit, boost::optional<bool> widthOnly)
{
	assert(getPlugin());
	getPlugin()->CenterOnItem(item, scaleToFit ? *scaleToFit : false, widthOnly ? *widthOnly : false);
	return true;
}

bool HPCCSystemsGraphViewControlAPI::setMessage(const std::string& msg)
{
	assert(getPlugin());
	getPlugin()->SetMessage(msg);
	return true;
}

FB::VariantList HPCCSystemsGraphViewControlAPI::find(const std::string & text, boost::optional<bool> includeProperties)
{
	assert(getPlugin());
	FB::VariantList retVal;

	std::vector<int> foundItems;
	getPlugin()->Find(text, includeProperties ? *includeProperties : true, foundItems);
	for(std::vector<int>::const_iterator itr = foundItems.begin(); itr != foundItems.end(); ++itr)
		retVal.push_back(*itr);

	return retVal;
}

bool HPCCSystemsGraphViewControlAPI::hasItems()
{
	return getPlugin()->HasItems();
}

FB::VariantList HPCCSystemsGraphViewControlAPI::getSelection()
{
	FB::VariantList retVal;

	std::vector<int> selectedItems;
	getPlugin()->GetSelection(selectedItems);
	for(std::vector<int>::const_iterator itr = selectedItems.begin(); itr != selectedItems.end(); ++itr)
		retVal.push_back(*itr);

	return retVal;
}

int HPCCSystemsGraphViewControlAPI::getRunningSubgraph()
{
	hpcc::IClusterSet clusters = getPlugin()->GetClusters();
	for(hpcc::IClusterSet::const_iterator itr = clusters.begin(); itr != clusters.end(); ++itr)
	{
		if ((hpcc::XGMML_STATE_ENUM)itr->get()->GetPropertyInt(hpcc::XGMML_STATE) == hpcc::XGMML_STATE_RUNNING)
			return itr->get()->GetID();
	}
	return 0;
}

FB::VariantList HPCCSystemsGraphViewControlAPI::getSelectionAsGlobalID()
{
	FB::VariantList retVal;

	std::vector<std::string> selectedItems;
	getPlugin()->GetSelection(selectedItems);
	for(std::vector<std::string>::const_iterator itr = selectedItems.begin(); itr != selectedItems.end(); ++itr)
		retVal.push_back(*itr);

	return retVal;
}

bool HPCCSystemsGraphViewControlAPI::setSelected(const std::vector<int> & items, boost::optional<bool> clearPrevious)
{
	return getPlugin()->SetSelected(items, clearPrevious ? *clearPrevious : true);
}

bool HPCCSystemsGraphViewControlAPI::setSelectedAsGlobalID(const std::vector<std::string> & items, boost::optional<bool> clearPrevious)
{
	return getPlugin()->SetSelected(items, clearPrevious ? *clearPrevious : true);
}

FB::VariantMap HPCCSystemsGraphViewControlAPI::getProperties(int item)
{
	assert(getPlugin());
	FB::VariantMap retVal;
	retVal["_internalID"] = item;
	retVal["_globalID"] = getGlobalID(item);

	hpcc::ciStringStringMap properties;
	getPlugin()->GetProperties(item, properties);
	for(hpcc::ciStringStringMap::const_iterator itr = properties.begin(); itr != properties.end(); ++itr)
		retVal[itr->first] = itr->second;

	return retVal;
}

FB::VariantList HPCCSystemsGraphViewControlAPI::getPropertiesForItems(const std::vector<int> & items)
{
	FB::VariantList retVal;
	for(std::vector<int>::const_iterator itr = items.begin(); itr != items.end(); ++itr)
		retVal.push_back(getProperties(*itr));

	return retVal;
}

std::string HPCCSystemsGraphViewControlAPI::getProperty(int item, const std::string & key)
{
	hpcc::ciStringStringMap properties;
	getPlugin()->GetProperties(item, properties);
	return properties[key];
}

int HPCCSystemsGraphViewControlAPI::getItem(const std::string & externalID)
{
	return getPlugin()->GetItem(externalID);
}

std::string HPCCSystemsGraphViewControlAPI::getGlobalID(int item)
{
	if (const char * globalIDChar = getPlugin()->GetGlobalID(item))
		return globalIDChar;
	return "";
}

FB::VariantList HPCCSystemsGraphViewControlAPI::getVertices()
{
 	FB::VariantList items;
	std::vector<int> vertices;
	getPlugin()->GetVertices(vertices);
	for(std::vector<int>::const_iterator itr = vertices.begin(); itr != vertices.end(); ++itr)
		items.push_back(*itr);

	return items;
}

FB::VariantList HPCCSystemsGraphViewControlAPI::getSubgraphsWithProperties()
{
	std::vector<int> subgraphs;
	getPlugin()->GetClusters(subgraphs);
	return getPropertiesForItems(subgraphs);
}

FB::VariantList HPCCSystemsGraphViewControlAPI::getVerticesWithProperties()
{
	std::vector<int> vertices;
	getPlugin()->GetVertices(vertices);
	return getPropertiesForItems(vertices);
}

FB::VariantList HPCCSystemsGraphViewControlAPI::getEdgesWithProperties()
{
	std::vector<int> edges;
	getPlugin()->GetEdges(edges);
	return getPropertiesForItems(edges);
}

bool HPCCSystemsGraphViewControlAPI::onMouseWheel(unsigned int nFlags, short zDelta, int x, int y)
{
#ifdef _WIN
	//  Hack for windows mouse wheel notifications  ---
	return getPlugin()->DoMouseWheel(nFlags, zDelta, CPoint(x, y));
#endif
	return false;
}

void HPCCSystemsGraphViewControlAPI::loadTestData()
{
	getPlugin()->LoadTestData();
}

bool HPCCSystemsGraphViewControlAPI::loadXML(const std::string& verticesXML, const std::string& edgesXML)
{
	getPlugin()->LoadXML(verticesXML, edgesXML);
	return true;
}

bool HPCCSystemsGraphViewControlAPI::loadXML2(const std::string& xml)
{
	getPlugin()->LoadXML2(xml);
	return true;
}

const std::string HPCCSystemsGraphViewControlAPI::getSVG()
{
	std::string svg = getPlugin()->GetSVG();
	boost::iterator_range<std::string::iterator> result = boost::algorithm::find_first(svg, "<svg");
	std::string retVal(result.begin(), svg.end());
	return retVal;
}

const std::string HPCCSystemsGraphViewControlAPI::getDOT()
{
	std::string dot = getPlugin()->GetDOT();
	return dot;
}

const std::string HPCCSystemsGraphViewControlAPI::getLocalisedXGMML(const std::vector<int> & items, boost::optional<int> localisationDepth, boost::optional<int> localisationDistance)
{
	std::string retVal;
	getPlugin()->GetLocalisedXGMML(items, localisationDepth ? *localisationDepth : 1, localisationDistance ? *localisationDistance : 3, retVal);
	if (retVal.empty())
		return retVal;

	retVal = "<graph>" + retVal + "</graph>";
	return retVal;
}

