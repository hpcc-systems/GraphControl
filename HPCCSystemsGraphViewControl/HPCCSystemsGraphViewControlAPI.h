/**********************************************************\

  Auto-generated HPCCSystemsGraphViewControlAPI.h

\**********************************************************/

#include "Unknown.h"
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
    int get_version();

    // Methods 
	void loadTestData();
	bool loadXML(const std::string& verticesXML, const std::string& edgesXML);
	bool loadXML2(const std::string& xml);
	const std::string getSVG();
	const std::string getLocalisedXGMML(const std::vector<int> & items);

	//  For Jo
	bool clear();
	bool loadXGMML(const std::string& xgmml);
	bool mergeXGMML(const std::string& xgmml);
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
	void fireScaled(int newScale);
	void fireLayoutFinished();
	void fireMouseDoubleClicked(int item);
	void fireSelChanged(const std::vector<int> & seection);

private:
    HPCCSystemsGraphViewControlWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;
};

#endif // H_HPCCSystemsGraphViewControlAPI

