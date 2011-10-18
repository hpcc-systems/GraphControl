#include "Platform.h"

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"

#include "HPCCSystemsGraphViewControlAPI.h"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <XgmmlParser.h>

#define CURRENT_VERSION 20110705

const char * const Scaled = "onScaled";
const char * const LayoutFinished = "onLayoutFinished";
const char * const MouseDoubleClick = "onMouseDoubleClick";
const char * const SelectionChanged = "onSelectionChanged";

///////////////////////////////////////////////////////////////////////////////
/// @fn HPCCSystemsGraphViewControlAPI::HPCCSystemsGraphViewControlAPI(HPCCSystemsGraphViewControlPtr plugin, FB::BrowserHostPtr host)
///
/// @brief  Constructor for your JSAPI object.  You should register your methods, properties, and events
///         that should be accessible to Javascript from here.
///
/// @see FB::JSAPIAuto::registerMethod
/// @see FB::JSAPIAuto::registerProperty
/// @see FB::JSAPIAuto::registerEvent
///////////////////////////////////////////////////////////////////////////////
HPCCSystemsGraphViewControlAPI::HPCCSystemsGraphViewControlAPI(const HPCCSystemsGraphViewControlPtr& plugin, const FB::BrowserHostPtr& host, CDotView * callback) : m_plugin(plugin), m_host(host)
{
	m_callback = callback;
    std::cout << "registerMethod\n";
	registerMethod("clear", make_method(this, &HPCCSystemsGraphViewControlAPI::clear));
	registerMethod("loadXGMML", make_method(this, &HPCCSystemsGraphViewControlAPI::loadXGMML));
	registerMethod("mergeXGMML", make_method(this, &HPCCSystemsGraphViewControlAPI::mergeXGMML));
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
	registerMethod("getProperties", make_method(this, &HPCCSystemsGraphViewControlAPI::getProperties));
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
	registerMethod("getLocalisedXGMML", make_method(this, &HPCCSystemsGraphViewControlAPI::getLocalisedXGMML));

    registerMethod("testEvent", make_method(this, &HPCCSystemsGraphViewControlAPI::testEvent));

    // Read-write property
    registerProperty("testString", make_property(this, &HPCCSystemsGraphViewControlAPI::get_testString, &HPCCSystemsGraphViewControlAPI::set_testString));

    // Read-only property
    registerProperty("version", make_property(this, &HPCCSystemsGraphViewControlAPI::get_version));

	//  Events
	registerEvent(Scaled);
	registerEvent(LayoutFinished);
	registerEvent(MouseDoubleClick);
	registerEvent(SelectionChanged);
}

///////////////////////////////////////////////////////////////////////////////
/// @fn HPCCSystemsGraphViewControlAPI::~HPCCSystemsGraphViewControlAPI()
///
/// @brief  Destructor.  Remember that this object will not be released until
///         the browser is done with it; this will almost definitely be after
///         the plugin is released.
///////////////////////////////////////////////////////////////////////////////
HPCCSystemsGraphViewControlAPI::~HPCCSystemsGraphViewControlAPI()
{
}

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

// Read/Write property testString
std::string HPCCSystemsGraphViewControlAPI::get_testString()
{
    return m_testString;
}
void HPCCSystemsGraphViewControlAPI::set_testString(const std::string& val)
{
    m_testString = val;
}

// Read-only property version
int HPCCSystemsGraphViewControlAPI::get_version()
{
    return CURRENT_VERSION;
}

bool HPCCSystemsGraphViewControlAPI::clear()
{
	m_callback->Clear();
	return true;
}

bool HPCCSystemsGraphViewControlAPI::loadXGMML(const std::string& xgmml)
{
    std::cout << "loadXGMML\n";
    assert(m_callback != NULL);
	if (xgmml.empty())
	{
        std::cout << "loadXGMML 1\n";
		m_callback->Clear();
		return true;
	}
    std::cout << "loadXGMML 2\n";
	m_callback->LoadXGMML(xgmml);
    std::cout << "loadXGMML 3\n";
	return true;
}

bool HPCCSystemsGraphViewControlAPI::mergeXGMML(const std::string& xgmml)
{
	m_callback->MergeXGMML(xgmml);
	return true;
}

bool HPCCSystemsGraphViewControlAPI::startLayout(const std::string& layout)
{
	m_callback->StartLayout(layout);
	return true;
}

int HPCCSystemsGraphViewControlAPI::setScale(int percent)
{
	double newScale = percent;
	double oldScale = m_callback->SetScale(newScale / 100) * 100;
	return (int)oldScale;
}

int HPCCSystemsGraphViewControlAPI::getScale()
{
	return (int)m_callback->GetScale() * 100;
}

bool HPCCSystemsGraphViewControlAPI::centerOnItem(int item, boost::optional<bool> scaleToFit, boost::optional<bool> widthOnly)
{
	assert(m_callback);
	m_callback->CenterOnItem(item, scaleToFit ? *scaleToFit : false, widthOnly ? *widthOnly : false);
	return true;
}

bool HPCCSystemsGraphViewControlAPI::setMessage(const std::string& msg)
{
	assert(m_callback);
	m_callback->SetMessage(msg);
	return true;
}

FB::VariantList HPCCSystemsGraphViewControlAPI::find(const std::string & text, boost::optional<bool> includeProperties)
{
	assert(m_callback);
	FB::VariantList retVal;

	std::vector<int> foundItems;
	m_callback->Find(text, includeProperties ? *includeProperties : true, foundItems);
	for(std::vector<int>::const_iterator itr = foundItems.begin(); itr != foundItems.end(); ++itr)
		retVal.push_back(*itr);

	return retVal;
}

bool HPCCSystemsGraphViewControlAPI::hasItems()
{
	return m_callback->HasItems();
}

FB::VariantList HPCCSystemsGraphViewControlAPI::getSelection()
{
	FB::VariantList retVal;

	std::vector<int> selectedItems;
	m_callback->GetSelection(selectedItems);
	for(std::vector<int>::const_iterator itr = selectedItems.begin(); itr != selectedItems.end(); ++itr)
		retVal.push_back(*itr);

	return retVal;
}

int HPCCSystemsGraphViewControlAPI::getRunningSubgraph()
{
	ln::IClusterSet clusters = m_callback->GetClusters();
	for(ln::IClusterSet::const_iterator itr = clusters.begin(); itr != clusters.end(); ++itr)
	{
		if ((ln::XGMML_STATE_ENUM)itr->get()->GetPropertyInt(ln::XGMML_STATE) == ln::XGMML_STATE_RUNNING)
			return itr->get()->GetID();
	}
	return 0;
}

FB::VariantList HPCCSystemsGraphViewControlAPI::getSelectionAsGlobalID()
{
	FB::VariantList retVal;

	std::vector<std::string> selectedItems;
	m_callback->GetSelection(selectedItems);
	for(std::vector<std::string>::const_iterator itr = selectedItems.begin(); itr != selectedItems.end(); ++itr)
		retVal.push_back(*itr);

	return retVal;
}

bool HPCCSystemsGraphViewControlAPI::setSelected(const std::vector<int> & items, boost::optional<bool> clearPrevious)
{
	return m_callback->SetSelected(items, clearPrevious ? *clearPrevious : true);
}

bool HPCCSystemsGraphViewControlAPI::setSelectedAsGlobalID(const std::vector<std::string> & items, boost::optional<bool> clearPrevious)
{
	return m_callback->SetSelected(items, clearPrevious ? *clearPrevious : true);
}

FB::VariantMap HPCCSystemsGraphViewControlAPI::getProperties(int item)
{
	assert(m_callback);
	FB::VariantMap retVal;

	ln::StringStringMap properties;
	m_callback->GetProperties(item, properties);
	for(ln::StringStringMap::const_iterator itr = properties.begin(); itr != properties.end(); ++itr)
		retVal[itr->first] = itr->second;

	return retVal;
}

std::string HPCCSystemsGraphViewControlAPI::getProperty(int item, const std::string & key)
{
	ln::StringStringMap properties;
	m_callback->GetProperties(item, properties);
	return properties[key];
}

int HPCCSystemsGraphViewControlAPI::getItem(const std::string & externalID)
{
	return m_callback->GetItem(externalID);
}

std::string HPCCSystemsGraphViewControlAPI::getGlobalID(int item)
{
	if (const char * globalIDChar = m_callback->GetGlobalID(item))
		return globalIDChar;
	return "";
}

FB::VariantList HPCCSystemsGraphViewControlAPI::getVertices()
{
 	FB::VariantList items;
	std::vector<int> vertices;
	m_callback->GetVertices(vertices);
	for(std::vector<int>::const_iterator itr = vertices.begin(); itr != vertices.end(); ++itr)
		items.push_back(*itr);

	return items;
}

bool HPCCSystemsGraphViewControlAPI::onMouseWheel(unsigned int nFlags, short zDelta, int x, int y)
{
#ifdef _WIN
	//  Hack for windows mouse wheel notifications  ---
	return m_callback->DoMouseWheel(nFlags, zDelta, CPoint(x, y));
#endif
	return false;
}

void HPCCSystemsGraphViewControlAPI::loadTestData()
{
	m_callback->LoadTestData();
}

bool HPCCSystemsGraphViewControlAPI::loadXML(const std::string& verticesXML, const std::string& edgesXML)
{
	m_callback->LoadXML(verticesXML, edgesXML);
	return true;
}

bool HPCCSystemsGraphViewControlAPI::loadXML2(const std::string& xml)
{
	m_callback->LoadXML2(xml);
	return true;
}

const std::string HPCCSystemsGraphViewControlAPI::getSVG()
{
	std::string svg = m_callback->GetSVG();
	boost::iterator_range<std::string::iterator> result = boost::algorithm::find_first(svg, "<svg");
	std::string retVal(result.begin(), svg.end());
	return retVal;
}

const std::string HPCCSystemsGraphViewControlAPI::getLocalisedXGMML(const std::vector<int> & items)
{
	std::string retVal;
	for(std::vector<int>::const_iterator itr = items.begin(); itr != items.end(); ++itr)
		m_callback->GetLocalisedXGMML(*itr, retVal);
	if (retVal.empty())
		return retVal;

	retVal = "<graph>" + retVal + "</graph>";
	return retVal;
}

void HPCCSystemsGraphViewControlAPI::testEvent(const FB::variant& var)
{
    FireEvent("onfired", FB::variant_list_of(var)(true)(1));
}

void HPCCSystemsGraphViewControlAPI::fireLayoutFinished()
{
	FireEvent(LayoutFinished, FB::variant_list_of());
}

void HPCCSystemsGraphViewControlAPI::fireScaled(int newScale)
{
	FireEvent(Scaled, FB::variant_list_of(newScale));
}

void HPCCSystemsGraphViewControlAPI::fireMouseDoubleClicked(int item)
{
	FireEvent(MouseDoubleClick, FB::variant_list_of(item));
}

void HPCCSystemsGraphViewControlAPI::fireSelChanged(const std::vector<int> & selection)
{
 	FB::VariantList items;
	for(std::vector<int>::const_iterator itr = selection.begin(); itr != selection.end(); ++itr)
		items.push_back(*itr);
	FireEvent(SelectionChanged, FB::variant_list_of(items));
}
