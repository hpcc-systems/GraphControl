#include "Platform.h"

#include <string.h>

#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp> 

#include "SaxParser.h"
#include "XgmmlParser.h"

namespace ln
{
//  ===========================================================================
struct Shapes
{
	StringStringMap m_items;
	std::string m_blankStr;
	Shapes()
	{
		m_items["2"] = "rectangle";		//Disk Write
		m_items["3"] = "hexagon";		//sort
		m_items["5"] = "invhouse";		//Filter
		m_items["7"] = "invhouse";		//Filter project
		m_items["12"] = "invhouse";		//First N
		m_items["6"] = "trapezium";		//Split
		m_items["15"] = "invtrapezium";	//Lightweight Join
		m_items["19"] = "invtrapezium";	//Keyed Join
		m_items["21"] = "rectangle";		//Output
		m_items["22"] = "note";		//Pipe Output
		m_items["23"] = "invtrapezium"; //Funnel
		m_items["25"] = "rectangle"; //Inline Dataset
		m_items["26"] = "octagon";	//distribute
		m_items["29"] = "ellipse";		//Store Internal Result
		m_items["36"] = "diamond";		//If
		m_items["44"] = "rectangle";	//write csv
		m_items["47"] = "rectangle";	//write 
		m_items["54"] = "ellipse";		//Workunit Read
		m_items["56"] = "rectangle";		//Spill
		m_items["59"] = "invtrapezium";	//Merge
		m_items["61"] = "rectangle";	//write xml
		m_items["82"] = "rectangle";	//Projected Disk Read Spill 
		m_items["88"] = "rectangle";	//Projected Disk Read Spill 
		m_items["92"] = "rectangle";		//Limted Index Read
		m_items["93"] = "rectangle";		//Limted Index Read
		m_items["99"] = "rectangle";		//CSV Read
		m_items["105"] = "rectangle";		//CSV Read
		m_items["point"] = "point";		
	}
	const char * get(const char * key)
	{
		if (key == NULL)
			return m_blankStr.c_str();
		return m_items[key].c_str();
	}
} g_shapes;
//  ===========================================================================
ICluster * GetCluster(IGraph* graph, ICluster* cluster, const std::string & id, bool merge, bool appendMissing = true)
{
	ICluster * retVal = NULL;
	if (merge)
		retVal = graph->GetCluster(id, true);
	if (!retVal && appendMissing)
	{
		retVal = graph->CreateCluster(cluster);
		graph->SetExternalID(GRAPH_TYPE_CLUSTER, id, retVal);
		retVal->SetProperty(DOT_ID, id.c_str());
	}
	assert((appendMissing && retVal) || !appendMissing);
	return retVal;
}

IVertex * GetVertex(IGraph* graph, ICluster* cluster, const std::string & id, bool merge, bool appendMissing = true)
{
	IVertex * retVal = NULL;
	if (merge)
		retVal = graph->GetVertex(id, true);
	if (!retVal && appendMissing)
	{
		retVal = graph->CreateVertex(cluster == NULL ? graph : cluster);
		graph->SetExternalID(GRAPH_TYPE_VERTEX, id, retVal);
		retVal->SetProperty(DOT_ID, id.c_str());
	}
	assert((appendMissing && retVal) || !appendMissing);
	return retVal;
}

IEdge * GetEdge(IGraph* graph, const std::string & id, IVertex* from, IVertex* to, bool merge, bool appendMissing = true)
{
	IEdge * retVal = NULL;
	if (merge)
		retVal = graph->GetEdge(id, true);
	if (!retVal && appendMissing)
	{
		retVal = graph->CreateEdge(from, to);
		graph->SetExternalID(GRAPH_TYPE_EDGE, id, retVal);
		retVal->SetProperty(DOT_ID, id.c_str());
	}
	assert((appendMissing && retVal) || !appendMissing);
	return retVal;
}

typedef std::map<std::string, IGraphItemPtr> StringGraphItemMap;

struct XGMMLStackItem
{
	std::string id;
	IGraphItemPtr item;

	XGMMLStackItem(const std::string & _id)
	{
		id = _id;
	}
};

typedef std::pair<std::string, IGraphItemPtr> StringGraphItemPair;
typedef std::deque<XGMMLStackItem> GraphItemStack;
typedef std::set<CElementPtr> ElementSet;
class CXgmmlParser : public CStackParser
{
protected:
	IGraphPtr m_graph;
	GraphItemStack m_giStack;
	StringGraphItemMap m_itemLookup;
	ElementSet m_edgeElements;
	bool m_merge;

public:
	CXgmmlParser(IGraph * graph, bool merge) : m_graph(graph), m_merge(merge)
	{
	}

	const std::string & constGet(const StringStringMap & map, const std::string & key, const std::string & defVal  = "")
	{
		StringStringMap::const_iterator found = map.find(key);
		if (found == map.end())
			return defVal;
		return found->second;
	}

	void EnsureTopIsACluster()
	{
		//  Parent of a node must be a cluster
		GraphItemStack::iterator top = m_giStack.begin();
		if (top != m_giStack.end())
		{
			if (top->item.get() == NULL)
			{
				GraphItemStack::iterator parent = top + 1;
				top->item = GetCluster(m_graph, parent == m_giStack.end() ? NULL : dynamic_cast<ICluster *>(parent->item.get()), top->id, m_merge);
			}
		}
	}

	void EnsureTopIsAVertex(const std::string & id)
	{
		assert(!id.empty());
		//  Parent of a node must be a cluster
		GraphItemStack::iterator top = m_giStack.begin();
		if (top != m_giStack.end())
		{
			if (top->item.get() == NULL)
			{
				GraphItemStack::iterator parent = top + 1;
				top->item = GetVertex(m_graph, parent == m_giStack.end() ? NULL : dynamic_cast<ICluster *>(parent->item.get()), top->id, m_merge);
				m_itemLookup[id] = top->item;
			}
		}
	}

	IEdge * GetEdge(const std::string & id, const std::string & source, const std::string & target)
	{
		IEdge * retVal;
		assert(!id.empty());
		StringGraphItemMap::const_iterator from = m_itemLookup.find(source);
		StringGraphItemMap::const_iterator to = m_itemLookup.find(target);
		assert(from != m_itemLookup.end());
		assert(to != m_itemLookup.end());
				//top->item = m_graph->CreateEdge(dynamic_cast<IVertex *>(from->second.get()), dynamic_cast<IVertex *>(to->second.get()));
		retVal = ln::GetEdge(m_graph, id, dynamic_cast<IVertex *>(from->second.get()), dynamic_cast<IVertex *>(to->second.get()), m_merge);
		m_itemLookup[id] = retVal;
		return retVal;
	}

	virtual void OnStartElement(const XML_Char *pszName, const XML_Char **papszAttrs)
	{
		CStackParser::OnStartElement(pszName, papszAttrs);

		CElementPtr e = m_stack.top();

		if (e->m_tag.compare("node") == 0)
		{
			//  If top is NULL at this point it must be a subgraph.
			EnsureTopIsACluster();
			m_giStack.push_front(constGet(e->m_attr, "id"));
		}

		return;
	}

	bool equals(const char * str, const char * cmp)
	{
		if (str == NULL)
			return false;
		return boost::algorithm::equals(str, cmp);
	}

	void PropigateState(ICluster * cluster, XGMML_STATE_ENUM state)
	{
		if (cluster && cluster->GetParent())
		{
			cluster->SetProperty(XGMML_STATE, state);
			PropigateState(cluster->GetParent(), state);
		}
	}

	void PropigateState(IVertex * vertex, XGMML_STATE_ENUM state)
	{
		vertex->SetProperty(XGMML_STATE, state);
		PropigateState(vertex->GetParent(), state);
	}

	void PropigateState(IEdge * edge, XGMML_STATE_ENUM state)
	{
		edge->SetProperty(XGMML_STATE, state);
		PropigateState(edge->GetFromVertex(), state);
		PropigateState(edge->GetToVertex(), state);
	}

	void ProcessEdges()
	{
		for (ElementSet::const_iterator itr = m_edgeElements.begin(); itr != m_edgeElements.end(); ++itr)
		{
			CElementPtr e = itr->get();
			IEdge * edge = NULL;
			StringStringMap::const_iterator itrSource = e->m_attr.find("_sourceActivity");
			StringStringMap::const_iterator itrTarget = e->m_attr.find("_targetActivity");
			if (itrSource != e->m_attr.end() && !itrSource->second.empty() && itrTarget != e->m_attr.end() && !itrTarget->second.empty())
				edge = GetEdge(e->m_attr["id"], itrSource->second, itrTarget->second);
			else
				edge = GetEdge(e->m_attr["id"], e->m_attr["source"], e->m_attr["target"]);
			assert(edge);

			for(StringStringMap::const_iterator itr = e->m_attr.begin(); itr != e->m_attr.end(); ++itr)
				edge->SetProperty(itr->first, itr->second);

			std::string prettyCount = constGet(e->m_attr, "count");
			if (prettyCount.length() && 
					(!boost::algorithm::equals(prettyCount, "0") || 
					(boost::algorithm::equals(prettyCount, "0") && boost::algorithm::equals(constGet(e->m_attr, "_eofSeen"), "1")) || 
					(boost::algorithm::equals(prettyCount, "0") && boost::algorithm::equals(constGet(e->m_attr, "started"), "1"))))
			{
				std::string tmp;
				int len = prettyCount.length();
				for(int i = 0; i < len; ++i)
				{
					tmp += (char)prettyCount.at(i);;
					if ((len - 1 - i > 0) && (len - 1 - i) % 3 == 0)
						tmp += ',';
				}
				prettyCount = tmp;
			}
			else
				prettyCount = "";

			std::string edgeLabel;
			if (constGet(e->m_attr, "label").length() && prettyCount.length() && constGet(e->m_attr, "maxskew").length() && constGet(e->m_attr, "minskew").length())
				edgeLabel = (boost::format("%1%\n%2%\n+%3%%%, -%4%%%") % constGet(e->m_attr, "label") % prettyCount % constGet(e->m_attr, "maxskew") % constGet(e->m_attr, "minskew")).str();
			else if (prettyCount.length() && constGet(e->m_attr, "maxskew").length() && constGet(e->m_attr, "minskew").length())
				edgeLabel = (boost::format("%1%\n+%2%%%, -%3%%%") % prettyCount % constGet(e->m_attr, "maxskew") % constGet(e->m_attr, "minskew")).str();
			else if (constGet(e->m_attr, "label").length() && prettyCount.length())
				edgeLabel = (boost::format("%1%\n%2%") % constGet(e->m_attr, "label") % prettyCount).str();
			else if (prettyCount.length())
				edgeLabel = (boost::format("%1%") % prettyCount).str();
			else if (constGet(e->m_attr, "label").length())
				edgeLabel = (boost::format("%1%") % constGet(e->m_attr, "label")).str();

			boost::algorithm::replace_all(edgeLabel, "\n", "\\n");
			if (edgeLabel.empty())
				edgeLabel = ".";
			edge->SetProperty(DOT_LABEL, edgeLabel.c_str());
			if (m_merge)
				UpdateVisibleLabel(edge, edgeLabel);

			if (boost::algorithm::equals(constGet(e->m_attr, "_dependsOn"), "1") || boost::algorithm::equals(constGet(e->m_attr, "_childGraph"), "1"))
				edge->SetProperty(DOT_EDGE_STYLE, "dashed");

			std::string started = constGet(e->m_attr, "started");
			std::string stopped = constGet(e->m_attr, "stopped");
			if (started.empty() && stopped.empty())
			{
				edge->SetProperty(XGMML_STATE, XGMML_STATE_UNKNOWN);
			}
			else if (boost::algorithm::equals(started, stopped) && !boost::algorithm::equals(started, "0"))
			{
				PropigateState(edge, XGMML_STATE_COMPLETED);
			}
			else
			{
				PropigateState(edge, XGMML_STATE_RUNNING);
			}
		}
	}

	void UpdateVisibleLabel(IGraphItemPtr item, std::string label)
	{
		if (CUnknown * tmpProp = item->GetPropertyCUnknown(SVG_PROP_ELEMENTG))
		{

			boost::algorithm::replace_all(label, "\\n", "\n");

			typedef std::vector<std::string> split_vector_type;
			split_vector_type SplitVec; // #2: Search for tokens
			boost::algorithm::split(SplitVec, label, boost::algorithm::is_any_of("\n"), boost::algorithm::token_compress_on);
			ElementGPtr elemG = reinterpret_cast<ln::ElementG * >(tmpProp);
			int i = 0;
			for (split_vector_type::iterator itr = SplitVec.begin(); itr != SplitVec.end(); ++itr)
			{
				//assert(elemG->m_lines.size() > i);
				if (elemG->m_lines.size() > i)
					elemG->m_lines[i]->m_text = *itr;
				++i;
			}
			//assert(elemG->m_lines.size() == i);
		}
	}

	virtual void OnEndElement(const XML_Char *pszName)
	{
		CElementPtr e = m_stack.top();
		if (0 == e->m_tag.compare("node"))
		{
			GraphItemStack::iterator top = m_giStack.begin();
			assert(top != m_giStack.end());
			EnsureTopIsAVertex(e->m_attr["id"]); //  If top is NULL at this point it must be a vertex.

			for(StringStringMap::const_iterator itr = e->m_attr.begin(); itr != e->m_attr.end(); ++itr)
				top->item->SetProperty(itr->first, itr->second);

			boost::algorithm::replace_all(e->m_attr["label"], "\n", "\\n");
#ifdef _DEBUG
			if (top->item->GetProperty("_kind"))
			{			
				e->m_attr["label"] += "\\n";
				e->m_attr["label"] += top->item->GetProperty("_kind");
			}
#endif
			top->item->SetProperty(DOT_LABEL, e->m_attr["label"].c_str());
			if (m_merge)
				UpdateVisibleLabel(top->item, e->m_attr["label"]);
			top->item->SetProperty(DOT_VERTEX_SHAPE, g_shapes.get(e->m_attr["_kind"].c_str()));
			if (top->item->GetProperty("_globalUsageCount"))
				top->item->SetProperty(XGMML_GLOBAL_USAGE_COUNT, boost::lexical_cast<int>(top->item->GetProperty("_globalUsageCount")));
			if (top->item->GetProperty("_isSpill"))
				top->item->SetProperty(XGMML_IS_SPILL, boost::lexical_cast<bool>(top->item->GetProperty("_isSpill")));

			m_giStack.pop_front();
		}
		else if (0 == e->m_tag.compare("edge"))
		{
			m_edgeElements.insert(e);
		}
		else if (0 == e->m_tag.compare("att"))
		{
			m_stack.pop();
			CElementPtr e_p = m_stack.top();
			assert(e_p);
			m_stack.push(e);
			StringStringMap::const_iterator key = e->m_attr.find("name");
			StringStringMap::const_iterator val = e->m_attr.find("value");
			if (key != e->m_attr.end() && val != e->m_attr.end())
				e_p->m_attr[key->second] = val->second;
			else if (key != e->m_attr.end())
				e_p->m_attr[key->second] = "";
		}

		CStackParser::OnEndElement(pszName);
		return;
	}

};

GRAPHDB_API bool LoadXGMML(IGraph * graph, const std::string & xgmml)
{
	CXgmmlParser parser(graph, false);
	parser.Create();
	bool retVal = parser.Parse(xgmml.c_str(), xgmml.length());
	parser.ProcessEdges();
	IClusterSet clusters = graph->GetAllClusters();
	for(IClusterSet::const_iterator itr = clusters.begin(); itr != clusters.end(); ++itr)
	{
		if (itr->get()->OnlyConatinsOneCluster())
			itr->get()->Delete();
	}
	return retVal;
}

GRAPHDB_API bool MergeXGMML(IGraph * graph, const std::string & xgmml)
{
	CXgmmlParser parser(graph, true);
	parser.Create();
	bool retVal = parser.Parse(xgmml.c_str(), xgmml.length());
	parser.ProcessEdges();
	return retVal;
}
}