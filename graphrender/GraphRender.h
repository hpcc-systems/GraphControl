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

#include "GraphDB.h"
#include "SvgShapes.h"
#include "GraphBuffer.h"
#include "GraphHotItem.h"

namespace hpcc
{
hpcc_interface GRAPHRENDER_API IGraphRender : public IUnknown
{
	virtual void SetMessage(const std::string & msg) = 0;
	virtual void SetOffset(const PointD & pt) = 0;
	virtual PointD GetOffset() const = 0;

	virtual double SetScale(double scale = 1.0) = 0;
	virtual double GetScale() const = 0;
	virtual double ScaleToFit(double x, double y, const RectD & screenRect, bool widthOnly, bool world/* = false*/) = 0;
	virtual double ScaleToFit(IGraphItem * item, const RectD & screenRect, bool widthOnly) = 0;

	virtual RectD GetBoundingRect(bool world = false) const = 0;
	virtual RectD GetBoundingRect(double x, double y, bool world = false) const = 0;
	virtual RectD GetBoundingRect(IGraphItem * item, bool world = false) const = 0;
	virtual IGraphItem * GetItemAt(double x, double y, bool world = false) const = 0;

	// Transofmations  ---
	virtual PointD ScreenToWorld(const PointD & rect) const = 0;
	virtual PointD WorldToScreen(const PointD & rect) const = 0;
	virtual RectD ScreenToWorld(const RectD & pt) const = 0;
	virtual RectD WorldToScreen(const RectD & pt) const = 0;

	//  Rendering  ---
	virtual void DoRender(const RectI & rect, bool clear) = 0;
	virtual void DoRenderRect(const RectD & rect) = 0;
};
typedef CUnknownPtr<IGraphRender> IGraphRenderPtr;

GRAPHRENDER_API IGraphRender * CreateGraphRender(IGraph * g, IGraphBuffer * pixmap, IGraphHotItem * hotItem, IGraphSelectionBag * selectionBag, double scale = 1.0);
};

