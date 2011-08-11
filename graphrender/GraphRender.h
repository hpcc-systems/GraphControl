#pragma once

#include "GraphDB.h"
#include "SvgShapes.h"
#include "GraphBuffer.h"
#include "GraphHotItem.h"

namespace ln
{
interface GRAPHRENDER_API IGraphRender : public IUnknown
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

