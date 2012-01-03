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
#pragma once

#include "GraphBuffer.h"
#include "GraphDB.h"
#include "SvgShapes.h"

namespace hpcc
{
hpcc_interface GRAPHRENDER_API IGraphHotItem : public IUnknown
{
	virtual bool Set(IGraphItem * item) = 0;
	virtual bool IsHot(IGraphItem * item) const = 0;
	virtual bool GetInvalidateRect(RectD & retVal) const = 0;
	virtual bool GetPrevInvalidateRect(RectD & retVal) const = 0;
};
typedef CUnknownPtr<IGraphHotItem> IGraphHotItemPtr;

hpcc_interface GRAPHRENDER_API IGraphSelectionBag : public IUnknown
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