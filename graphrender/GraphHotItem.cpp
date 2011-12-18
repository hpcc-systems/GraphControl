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
#include "Platform.h"

#include "GraphHotItem.h"
#include "SvgParser.h"

#include <assert.h>

namespace ln
{
//  ===========================================================================
class CGraphHotItem : public IGraphHotItem, public CUnknown
{
protected:
	IGraphItemPtr m_hotItem;
	IEdge * m_hotEdge;
	IVertex * m_hotVertex;

	mutable RectD m_invalidateRect;
	RectD m_prevInvalidateRect;

public:
	BEGIN_CUNKNOWN
	END_CUNKNOWN

	CGraphHotItem()
	{
		m_hotEdge = NULL;
		m_hotVertex = NULL;
	}

	bool Set(IGraphItem * item)
	{
		if (m_hotItem != item)
		{
			GetInvalidateRect(m_prevInvalidateRect);
			m_hotItem = item;
			m_hotEdge = dynamic_cast<IEdge * >(m_hotItem.get());
			m_hotVertex = m_hotEdge == NULL ? dynamic_cast<IVertex * >(m_hotItem.get()) : NULL;
			m_invalidateRect = RectD();
			return true;
		}
		return false;
	}

	IGraphItem * GetXXX() const
	{
		return m_hotItem;
	}

	bool IsHot(IGraphItem * item) const
	{
		if (item == m_hotItem)
			return true;
		if (m_hotEdge && (item == m_hotEdge->GetFromVertex() || item == m_hotEdge->GetToVertex()))
			return true;
		if (m_hotVertex)
		{
			if (IEdge * edge = dynamic_cast<IEdge *>(item))
			{
				if (m_hotVertex == edge->GetFromVertex() || m_hotVertex == edge->GetToVertex())
					return true;
			}
		}
		return false;
	}

	bool GetInvalidateRect(RectD & retVal) const
	{
		if (!m_invalidateRect.IsEmptyArea())
			retVal = m_invalidateRect;

		if (m_hotItem)
		{
			if (ln::ElementG * hotElementG = GetElementG(m_hotItem))
			{
				retVal = hotElementG->GetBoundingBox();
				if (m_hotEdge)
				{
					if (ln::ElementG * hotElementG = GetElementG(m_hotEdge->GetFromVertex()))
						retVal.Union(hotElementG->GetBoundingBox());
					if (ln::ElementG * hotElementG = GetElementG(m_hotEdge->GetToVertex()))
						retVal.Union(hotElementG->GetBoundingBox());
				}
				else if(m_hotVertex)
				{
					for(IEdgeSet::const_iterator itr = m_hotVertex->GetInEdges().begin(); itr != m_hotVertex->GetInEdges().end(); ++itr)
					{
						if (ln::ElementG * hotElementG = GetElementG(itr->get()))
							retVal.Union(hotElementG->GetBoundingBox());
					}
					for(IEdgeSet::const_iterator itr = m_hotVertex->GetOutEdges().begin(); itr != m_hotVertex->GetOutEdges().end(); ++itr)
					{
						if (ln::ElementG * hotElementG = GetElementG(itr->get()))
							retVal.Union(hotElementG->GetBoundingBox());
					}
				}
			}
		}
		m_invalidateRect = retVal;
		return !m_invalidateRect.IsEmptyArea();
	}

	bool GetPrevInvalidateRect(RectD & retVal) const
	{
		retVal = m_prevInvalidateRect;
		return !m_prevInvalidateRect.IsEmptyArea();
	}
};
typedef std::map<int, CGraphHotItem> CGraphHotItemMap;
//  ===========================================================================
class CGraphSelectionBag : public IGraphSelectionBag, public CUnknown
{
protected:
	CGraphHotItemMap m_selected;
	CGraphHotItemMap m_prevSelected;

public:
	BEGIN_CUNKNOWN
	END_CUNKNOWN

	bool Clear()
	{
		if (!m_selected.empty())
		{
			m_prevSelected = m_selected;
			m_selected.clear();
			return true;
		}
		return false;
	}

	bool Select(IGraphItem * item, bool clearPrevious = true)
	{
		bool changed = false;
		if (m_selected.size() == 1 && IsSelected(item))
			return changed;

		CGraphHotItemMap prevSelected = m_selected;

		if (clearPrevious && !m_selected.empty())
		{
			changed = true;
			m_selected.clear();
		}
		CGraphHotItemMap::const_iterator found = m_selected.find(item->GetID());
		if (found == m_selected.end())
		{
			changed = true;
			m_selected[item->GetID()].Set(item);
		}

		if (changed)
			m_prevSelected = prevSelected;
		return changed;
	}

	bool Select(const IGraphItemSet & items, bool clearPrevious = true)
	{
		bool changed = false;
		CGraphHotItemMap prevSelected = m_selected;

		if (clearPrevious && !m_selected.empty())
		{
			changed = true;
			m_selected.clear();
		}

		for (IGraphItemSet::const_iterator itr = items.begin(); itr != items.end(); ++itr)
		{
			CGraphHotItemMap::const_iterator found = m_selected.find(itr->get()->GetID());
			if (found == m_selected.end())
			{
				changed = true;
				m_selected[itr->get()->GetID()].Set(itr->get());
			}
		}

		if (changed)
			m_prevSelected = prevSelected;
		return changed;
	}

	bool Deselect(IGraphItem * item)
	{
		CGraphHotItemMap::iterator found = m_selected.find(item->GetID());
		if (found != m_selected.end())
		{
			m_selected.erase(found);
			m_prevSelected = m_selected;
			return true;
		}
		return false;
	}

	bool IsSelected(IGraphItem * item) const
	{
		CGraphHotItemMap::const_iterator found = m_selected.find(item->GetID());
		if (found != m_selected.end())
			return true;
		return false;
	}

	int GetSelection(std::vector<int> & selection) const
	{
		for (CGraphHotItemMap::const_iterator itr = m_selected.begin(); itr != m_selected.end(); ++itr)
			selection.push_back(itr->first);
		return selection.size();
	}

	int GetSelection(const IGraph * g, std::vector<std::string> & selection) const
	{
		for (CGraphHotItemMap::const_iterator itr = m_selected.begin(); itr != m_selected.end(); ++itr)
			selection.push_back(g->GetExternalID(itr->first));
		return selection.size();
	}

	bool GetInvalidateRect(RectD & retVal) const
	{
		bool first = true;
		for (CGraphHotItemMap::const_iterator itr = m_selected.begin(); itr != m_selected.end(); ++itr)
		{
			if (first)
			{
				first = false;
				itr->second.GetInvalidateRect(retVal);
			}
			else
			{
				RectD rect;
				itr->second.GetInvalidateRect(rect);
				retVal.Union(rect);
			}
		}
		return true;
	}

	bool GetPrevInvalidateRect(RectD & retVal) const
	{
		bool first = true;
		for (CGraphHotItemMap::const_iterator itr = m_prevSelected.begin(); itr != m_prevSelected.end(); ++itr)
		{
			if (first)
			{
				first = false;
				itr->second.GetInvalidateRect(retVal);
			}
			else
			{
				RectD rect;
				itr->second.GetInvalidateRect(rect);
				retVal.Union(rect);
			}
		}
		return true;
	}
};
//  ===========================================================================
GRAPHRENDER_API IGraphHotItem * CreateGraphHotItem()
{
	return new CGraphHotItem();
}

GRAPHRENDER_API IGraphSelectionBag * CreateGraphSelectionBag()
{
	return new CGraphSelectionBag();
}
//  ===========================================================================
}
