#pragma once

#include "GraphDB.h"

namespace ln
{
typedef std::map<unsigned int, bool> IntBoolMap;
typedef std::map<unsigned int, int> IntIntMap;
typedef std::map<unsigned int, double> IntDoubleMap;
typedef std::map<unsigned int, std::string> IntStringMap;
typedef std::map<unsigned int, IUnknownPtr> IntIUnknownMap;
typedef std::map<unsigned int, CUnknownPointer> IntCUnknownMap;

class CGraphItem : public IGraphItem, public CUnknown
{
protected:
	IGraph * m_graph;

	unsigned int m_id;
	std::string m_idString;

	IntBoolMap m_propBool;
	IntIntMap m_propInt;
	IntDoubleMap m_propDouble;
	IntStringMap m_propString;
	IntIUnknownMap m_propIUnknown;
	IntCUnknownMap m_propCUnknown;

	StringStringMap m_propStringString;

	std::string m_blankString;
	
public:
	BEGIN_CUNKNOWN
	END_CUNKNOWN

	CGraphItem(); 	//  Special case for CGraph constructor
	CGraphItem(IGraph * graph);

	void SetID(unsigned int id);

	void Clear();

	bool operator < (const CGraphItem & other) const;

	//  ===  IGraphItem  ===
	IGraph * GetGraph() const;
	unsigned int GetID() const;
	const std::string & GetIDString() const;

	void SetProperty(unsigned int key, bool val);
	bool GetPropertyBool(unsigned int key) const;
	void SetProperty(unsigned int key, int val);
	int GetPropertyInt(unsigned int key) const;
	void SetProperty(unsigned int key, double val);
	double GetPropertyDouble(unsigned int key) const;
	void SetProperty(unsigned int key, const char * val);
	bool HasPropertyString(unsigned int key) const;
	const char * GetPropertyString(unsigned int key) const;
	void SetProperty(unsigned int key, IUnknown * val);
	IUnknown * GetPropertyIUnknown(unsigned int key) const;
	void SetProperty(unsigned int key, CUnknown * val);
	CUnknown * GetPropertyCUnknown(unsigned int key) const;

	void SetProperty(const std::string & key, const std::string & val);
	const char * GetProperty(const std::string & key) const;
	int GetProperties(StringStringMap & results) const;
};
typedef CUnknownPtr<CGraphItem> CGraphItemPtr;
typedef std::map<unsigned int, CGraphItemPtr> IDGraphItemMap;

#define IGRAPHITEM_IMPL	IGraph * GetGraph() const {	return CGraphItem::GetGraph(); } \
						unsigned int GetID() const { return CGraphItem::GetID(); } \
						const std::string & GetIDString() const { return CGraphItem::GetIDString(); } \
						void SetProperty(unsigned int key, bool val) { CGraphItem::SetProperty(key, val); } \
						bool GetPropertyBool(unsigned int key) const { return CGraphItem::GetPropertyBool(key); } \
						void SetProperty(unsigned int key, int val) { CGraphItem::SetProperty(key, val); } \
						int GetPropertyInt(unsigned int key) const { return CGraphItem::GetPropertyInt(key); } \
						void SetProperty(unsigned int key, double val) { CGraphItem::SetProperty(key, val); } \
						double GetPropertyDouble(unsigned int key) const { return CGraphItem::GetPropertyDouble(key); } \
						void SetProperty(unsigned int key, const char * val) { CGraphItem::SetProperty(key, val); } \
						bool HasPropertyString(unsigned int key) const { return CGraphItem::HasPropertyString(key); } \
						const char * GetPropertyString(unsigned int key) const { return CGraphItem::GetPropertyString(key); } \
						void SetProperty(unsigned int key, IUnknown * val) { CGraphItem::SetProperty(key, val); } \
						IUnknown * GetPropertyIUnknown(unsigned int key) const { return CGraphItem::GetPropertyIUnknown(key); } \
						void SetProperty(unsigned int key, CUnknown * val) { CGraphItem::SetProperty(key, val); } \
						CUnknown * GetPropertyCUnknown(unsigned int key) const { return CGraphItem::GetPropertyCUnknown(key); } \
						void SetProperty(const std::string & key, const std::string & val) { CGraphItem::SetProperty(key, val); } \
						const char * GetProperty(const std::string & key) const { return CGraphItem::GetProperty(key); } \
						int GetProperties(StringStringMap & results) const { return CGraphItem::GetProperties(results); }
}