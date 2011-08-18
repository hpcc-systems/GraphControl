#pragma once

#include "GraphBuffer.h"
#include "GraphDB.h"
#include "SvgShapes.h"

namespace ln
{
interface GRAPHRENDER_API IGraphHotItem : public IUnknown
{
	virtual bool Set(IGraphItem * item) = 0;
	virtual bool IsHot(IGraphItem * item) const = 0;
	virtual bool GetInvalidateRect(RectD & retVal) const = 0;
	virtual bool GetPrevInvalidateRect(RectD & retVal) const = 0;
};
typedef CUnknownPtr<IGraphHotItem> IGraphHotItemPtr;

interface GRAPHRENDER_API IGraphSelectionBag : public IUnknown
{
	virtual bool Clear() = 0;
	virtual bool Select(IGraphItem * item, bool clearPrevious = true) = 0;
	virtual bool Select(const IGraphItemSet & items, bool clearPrevious = true) = 0;
	virtual bool Deselect(IGraphItem * item) = 0;
	virtual bool IsSelected(IGraphItem * item) const = 0;
	virtual int GetSelection(std::vector<int> & selection) const = 0;
	virtual int GetSelection(const IGraph * g, std::vector<std::string> & selection) const = 0;
	virtual bool GetInvalidateRect(RectD & retVal) const = 0;
	virtual bool GetPrevInvalidateRect(RectD & retVal) const = 0;
};
typedef CUnknownPtr<IGraphSelectionBag> IGraphSelectionBagPtr;

GRAPHRENDER_API IGraphHotItem * CreateGraphHotItem();
GRAPHRENDER_API IGraphSelectionBag * CreateGraphSelectionBag();
}