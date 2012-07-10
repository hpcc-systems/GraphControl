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
#include "precompiled_headers.h"

#include "GraphRender.h"
#include "SvgParser.h"
#include <XgmmlParser.h>

#include <agg_math_stroke.h>
#include <agg2d.h>
#include "FontResolver.h"

namespace hpcc
{
#define OVERVIEW_CUTOFF 0.25
#define NSHOW_BOUNDBOX

class CGraphRender : public IGraphRender, public CUnknown
{
protected:
	IGraphPtr m_g;
	IGraphBufferPtr m_pixmap;
	mutable Agg2D m_agg2d;
	IFontResolverPtr m_fonts;

	std::string m_message;
	PointD m_offset;
	double m_scale;

	RectD m_renderRect;

	double m_transparency;
	IGraphHotItemPtr m_hotItem;
	IGraphSelectionBagPtr m_selected;

	enum RENDER_TYPE
	{
		RENDER_TYPE_UNKNOWN = 0,
		RENDER_TYPE_CLUSTER,
		RENDER_TYPE_VERTEX,
		RENDER_TYPE_EDGE,
		RENDER_TYPE_LAST
	} m_inType;

	bool m_inHotItem;
	bool m_inSelectedItem;
	bool m_inDashed;
	XGMML_STATE_ENUM m_inState;

	struct StateT
	{
		RENDER_TYPE m_type;
		XGMML_STATE_ENUM m_state;

		StateT()
		{
			m_type = RENDER_TYPE_UNKNOWN;
			m_state = XGMML_STATE_UNKNOWN;
		}

		StateT(RENDER_TYPE type, XGMML_STATE_ENUM state)
		{
			m_type = type;
			m_state = state;
		}

		inline bool operator < (const StateT & other) const
		{
			if (other.m_state > m_state)
				return false;

			if (other.m_state < m_state)
				return true;

			if (other.m_type > m_type)
				return false;

			if (other.m_type < m_type)
				return true;

			return false;
		}
	};

	struct ColourT
	{
		Colour m_stroke;
		Colour m_fill;
		Colour m_text;

		ColourT()
		{
		}

		ColourT(const Colour & stroke, const Colour & fill, const Colour & text)
		{
			m_stroke = stroke;
			m_fill = fill;
			m_text = text;
		}
	};

	typedef std::map<StateT, ColourT> StateColourMap;

	StateColourMap m_colours;

	Colour m_selectedStroke;
	Colour m_selectedFill;
	Colour m_selectedFillText;

	Colour m_hotStroke;
	Colour m_hotFill;
	Colour m_hotFillText;

	Colour m_badColour;

public:
	BEGIN_CUNKNOWN
	END_CUNKNOWN

	CGraphRender(IGraph * g, IGraphBuffer * pixmap, IGraphHotItem * hotItem, IGraphSelectionBag * selectionBag, double scale = 1.0) : m_g(g), m_pixmap(pixmap), m_hotItem(hotItem), m_selected(selectionBag), 
			m_hotStroke(Colour::RoyalBlue),				m_hotFill(Colour::AliceBlue),				m_hotFillText(Colour::RoyalBlue),
			m_selectedStroke(Colour::DarkBlue),			m_selectedFill(Colour::LightBlue),		m_selectedFillText(Colour::DarkBlue)
	{
		m_fonts = CreateIFontResolver();
		m_scale = scale;
		m_inHotItem = false;
		m_inSelectedItem = false;
		m_inType = RENDER_TYPE_UNKNOWN;
		m_inDashed = false;

		m_colours[StateT(RENDER_TYPE_CLUSTER, XGMML_STATE_UNKNOWN)]	=	ColourT(Colour::Gray,			Colour::White,			Colour::Gray);
		m_colours[StateT(RENDER_TYPE_CLUSTER, XGMML_STATE_RUNNING)]	=	ColourT(Colour::ForestGreen,	Colour::Honeydew,		Colour::DarkGreen);
		m_colours[StateT(RENDER_TYPE_CLUSTER, XGMML_STATE_COMPLETED)] =	ColourT(Colour::Black,			Colour::White,			Colour::Black);

		m_colours[StateT(RENDER_TYPE_VERTEX, XGMML_STATE_UNKNOWN)]	=	ColourT(Colour::Gray,			Colour::White,			Colour::Gray);
		m_colours[StateT(RENDER_TYPE_VERTEX, XGMML_STATE_RUNNING)]	=	ColourT(Colour::ForestGreen,	Colour::White,			Colour::DarkGreen);
		m_colours[StateT(RENDER_TYPE_VERTEX, XGMML_STATE_COMPLETED)] =	ColourT(Colour::Black,			Colour::White,			Colour::Black);

		m_colours[StateT(RENDER_TYPE_EDGE, XGMML_STATE_UNKNOWN)]	=	ColourT(Colour::Gray,			Colour::Gray,			Colour::Gray);
		m_colours[StateT(RENDER_TYPE_EDGE, XGMML_STATE_RUNNING)]	=	ColourT(Colour::ForestGreen,	Colour::ForestGreen,	Colour::DarkGreen);
		m_colours[StateT(RENDER_TYPE_EDGE, XGMML_STATE_COMPLETED)] =	ColourT(Colour::Black,			Colour::Black,			Colour::Black);
		
		m_badColour = Colour::Red;
	}

	void SetMessage(const std::string & msg)
	{
		m_message = msg;
	}

	void SetOffset(const PointD & pt)
	{
		m_offset = pt.MulDiv(1.0, m_scale);
	}

	PointD GetOffset() const
	{
		return m_offset.MulDiv(m_scale, 1.0);
	}
	
	double SetScale(double scale)
	{
		double oldScale = m_scale;
		m_scale = scale;
		return oldScale;
	}

	double GetScale() const
	{
		return m_scale;
	}

	double ScaleToFit(double x, double y, const RectD & screenRect, bool widthOnly, bool world)
	{
		return ScaleToFit(GetItemAt(x, y, world), screenRect, widthOnly);
	}

	double ScaleToFit(IGraphItem * item, const RectD & screenRect, bool widthOnly)
	{
		RectD rect = screenRect;
		RectD rb = GetBoundingRect(item, true);
		if (IEdge * e = dynamic_cast<IEdge *>(item))
		{
			rb.Union(GetBoundingRect(e->GetFromVertex(), true));
			rb.Union(GetBoundingRect(e->GetToVertex(), true));
		}
		double widthRatio = rect.Width / rb.Width;
		double heightRatio = rect.Height / rb.Height;
		return SetScale(std::min<double>(1.0, widthOnly ? widthRatio : std::min<double>(widthRatio, heightRatio)));
	}

	RectD GetBoundingRect(bool world) const
	{
		return GetBoundingRect(m_g, world);
	}

	RectD GetBoundingRect(double x, double y, bool world = false) const
	{
		return GetBoundingRect(GetItemAt(x, y, world), world);
	}

	RectD GetBoundingRect(IGraphItem * item, bool world) const
	{
		if (item)
		{
			if (ElementG * eg = GetElementG(item))
			{
				RectD retVal = eg->GetBoundingBox();
				if (world)
					return retVal;
				return WorldToScreen(retVal);
			}
		}
		return GetBoundingRect(world);
	}

	bool HitTestItem(IGraphItem * item, int x, int y) const
	{
		ElementG * elementG = GetElementG(item);
		assert(elementG);

		for(EllipseVector::const_iterator itr = elementG->m_ellipses.begin(); itr != elementG->m_ellipses.end(); ++itr)
		{
			Render(m_agg2d, *itr);
			if (m_agg2d.hittestPath(x, y))
				return true;
		}
		for(PolygonVector::const_iterator itr = elementG->m_polygons.begin(); itr != elementG->m_polygons.end(); ++itr)
		{
			Render(m_agg2d, *itr);
			if (m_agg2d.hittestPath(x, y))
				return true;
		}
		for(PolygonVector::const_iterator itr = elementG->m_polylines.begin(); itr != elementG->m_polylines.end(); ++itr)
		{
			Render(m_agg2d, *itr);
			if (m_agg2d.hittestPath(x, y))
				return true;
		}
		for(PathVector::const_iterator itr = elementG->m_paths.begin(); itr != elementG->m_paths.end(); ++itr)
		{
			Render(m_agg2d, *itr);
			if (m_agg2d.hittestPath(x, y, true))
				return true;
		}
		for (TextVector::const_iterator itr = elementG->m_lines.begin(); itr != elementG->m_lines.end(); ++itr)
		{
			Render(m_agg2d, *itr);
			if (m_agg2d.hittestText(x, y, itr->get()->m_pos.x, itr->get()->m_pos.y, itr->get()->m_text.c_str()))
				return true;
		}

		return false;	
	}

	bool HitTestItemFast(IGraphItem * item, double x, double y) const
	{
		ElementG * elementG = GetElementG(item);
		assert(elementG);
		if (elementG->GetBoundingBox().Contains(x, y))
			return true;
		return false;	
	}

	bool HitTestItemFast(IGraphItem * item, const RectD & rc) const
	{
		ElementG * elementG = GetElementG(item);
		assert(elementG);
		if (elementG->GetBoundingBox().IntersectsWith(rc))
			return true;
		return false;	
	}

	IGraphItem * HitTestCluster(ICluster * cluster, double x, double y) const
	{
		IGraphItem * retVal = NULL;
		for(IClusterSet::const_reverse_iterator itr = cluster->GetClusters().rbegin(); itr != cluster->GetClusters().rend(); ++itr)  //  Reverse order to hit the "last" cluster first (the one on top)
		{
			if (HitTestItemFast(*itr, x, y))
				retVal = HitTestCluster(*itr, x, y);
			if (retVal)
				return retVal;
		}

		for(IVertexSet::const_iterator itr = cluster->GetVertices().begin(); itr != cluster->GetVertices().end(); ++itr)
		{
			if (HitTestItemFast(*itr, x, y))
				if (HitTestItem(*itr, (int)x, (int)y))
					return *itr;
		}
		if (!retVal && HitTestItem(cluster, (int)x, (int)y))
			retVal = cluster;
		return retVal;
	}

	IGraphItem * HitTestEdges(IGraph * g, int x, int y) const
	{
		for(IEdgeSet::const_iterator itr = g->GetAllEdges().begin(); itr != g->GetAllEdges().end(); ++itr)
		{
			if (HitTestItemFast(*itr, x, y))
				if (HitTestItem(*itr, x, y))
					return *itr;
		}
		return NULL;
	}

	virtual IGraphItem * GetItemAt(double x, double y, bool world) const
	{
		if (!m_message.empty())
			return NULL;

		PointD pt(x, y);
		if (!world)
			pt = ScreenToWorld(pt);

		m_agg2d.resetTransformations();
		m_agg2d.clipBox(pt.x - 1, pt.y - 1, pt.x + 1, pt.y + 1);
		m_agg2d.clearAll(0x7f, 0x7f, 0x7f);
		m_agg2d.lineColor(0x00, 0x00, 0x00, 255);
		m_agg2d.fillColor(0xff, 0xff, 0xff);
		m_agg2d.font(m_fonts->GetDefaultPath(), m_fonts->GetDefaultSize());

		if (HitTestItemFast(m_g, pt.x, pt.y))
		{
			IGraphItem * retVal = NULL;
			if (m_scale > OVERVIEW_CUTOFF)
			{
				retVal = HitTestEdges(m_g, (int)pt.x, (int)pt.y);
				if (retVal)
					return retVal;
			}

			std::vector<int> selection;
			m_selected->GetSelection(selection);
			for (std::vector<int>::const_iterator itr = selection.begin(); itr != selection.end(); ++itr)	
			{
				IClusterPtr cluster = m_g->GetCluster(*itr);
				if (cluster)
				{
					retVal = HitTestCluster(cluster, (int)pt.x, (int)pt.y);
					if (retVal)
						return retVal;
				}
			}
			retVal = HitTestCluster(m_g, (int)pt.x, (int)pt.y);
			if (retVal)
				return retVal;

			if (!retVal)
				return m_g;
		}

		return NULL;
	}

	// Transofmations  ---
	PointD ScreenToWorld(const PointD & pt) const
	{
		return pt.MulDiv(1.0, m_scale) - m_offset;
	}

	PointD WorldToScreen(const PointD & pt) const
	{
		return (pt + m_offset).MulDiv(m_scale, 1.0);
	}

	RectD ScreenToWorld(const RectD & rc) const
	{
		return rc.MulDiv(1.0, m_scale) - m_offset;
	}

	RectD WorldToScreen(const RectD & rc) const
	{
		return (rc + m_offset).MulDiv(m_scale, 1.0);
	}

	Agg2D::DrawPathFlag SetLineAndFill(Agg2D & agg2d, const Colour & stroke, const Colour & fill)
	{
		Agg2D::DrawPathFlag retVal = Agg2D::StrokeOnly;
		if (stroke.IsEmpty())
		{
			retVal = Agg2D::FillOnly;
			agg2d.noLine();
			if (m_inHotItem)
				agg2d.fillColor(m_hotFill.GetR(), m_hotFill.GetG(), m_hotFill.GetB(), static_cast<unsigned int>(m_hotFill.GetA() / m_transparency));
			else if (m_inSelectedItem)
				agg2d.fillColor(m_selectedFill.GetR(), m_selectedFill.GetG(), m_selectedFill.GetB(), static_cast<unsigned int>(m_selectedFill.GetA() / m_transparency));
			else
				agg2d.fillColor(fill.GetR(), fill.GetG(), fill.GetB(), static_cast<unsigned int>(fill.GetA() / m_transparency));
		}
		else if (fill.IsEmpty())
		{
			retVal = Agg2D::StrokeOnly;
			if (m_inHotItem)
				agg2d.lineColor(m_hotStroke.GetR(), m_hotStroke.GetG(), m_hotStroke.GetB(), m_hotStroke.GetA());
			else if (m_inSelectedItem)
				agg2d.lineColor(m_selectedStroke.GetR(), m_selectedStroke.GetG(), m_selectedStroke.GetB(), m_selectedStroke.GetA());
			else
				agg2d.lineColor(stroke.GetR(), stroke.GetG(), stroke.GetB(), stroke.GetA());
			agg2d.noFill();
		}
		else
		{
			assert(!stroke.IsEmpty() && !fill.IsEmpty());
			retVal = Agg2D::FillAndStroke;
			if (m_inHotItem)
			{
				agg2d.lineColor(m_hotStroke.GetR(), m_hotStroke.GetG(), m_hotStroke.GetB(), m_hotStroke.GetA());
				if (m_inType == RENDER_TYPE_EDGE)
					agg2d.fillColor(m_hotStroke.GetR(), m_hotStroke.GetG(), m_hotStroke.GetB(), static_cast<unsigned int>(m_hotStroke.GetA() / m_transparency));
				else
					agg2d.fillColor(m_hotFill.GetR(), m_hotFill.GetG(), m_hotFill.GetB(), static_cast<unsigned int>(m_hotFill.GetA() / m_transparency));
			}
			else if (m_inSelectedItem)
			{
				agg2d.lineColor(m_selectedStroke.GetR(), m_selectedStroke.GetG(), m_selectedStroke.GetB(), m_selectedStroke.GetA());
				if (m_inType == RENDER_TYPE_EDGE)
					agg2d.fillColor(m_selectedStroke.GetR(), m_selectedStroke.GetG(), m_selectedStroke.GetB(), static_cast<unsigned int>(m_selectedStroke.GetA() / m_transparency));
				else
					agg2d.fillColor(m_selectedFill.GetR(), m_selectedFill.GetG(), m_selectedFill.GetB(), static_cast<unsigned int>(m_selectedFill.GetA() / m_transparency));
			}
			else
			{
				agg2d.lineColor(stroke.GetR(), stroke.GetG(), stroke.GetB(), stroke.GetA());
				agg2d.fillColor(fill.GetR(), fill.GetG(), fill.GetB(), static_cast<unsigned int>(fill.GetA() / m_transparency));
			}
		}
		return retVal;
	}

	void Render(Agg2D & agg2d, const PointDVector & points) const
	{
		bool first = true;
		agg2d.resetPath();
		for (PointDVector::const_iterator itr = points.begin(); itr != points.end(); ++itr)
		{
			if (first)
				agg2d.moveTo(itr->x, itr->y);
			else
				agg2d.lineTo(itr->x, itr->y);
			first = false;
		}
		agg2d.closePolygon();
	}

	void Render(Agg2D & agg2d, Polygon * poly) const
	{
		if (!poly)
			return;

		Render(agg2d, poly->m_points);
	}

	void Render(Agg2D & agg2d, const AttrDPartVector & path) const
	{
		agg2d.resetPath();
		for (AttrDPartVector::const_iterator itr = path.begin(); itr != path.end(); ++itr)
		{
			switch(itr->m_command)
			{
			case 'M':
				assert(itr->m_points.size() == 2);
				agg2d.moveTo(itr->m_points[0], itr->m_points[1]);
				break;

			case 'm':
				assert(itr->m_points.size() == 2);
				agg2d.moveRel(itr->m_points[0], itr->m_points[1]);
				break;

			case 'L':
				assert(itr->m_points.size() == 2);
				agg2d.lineTo(itr->m_points[0], itr->m_points[1]);
				break;

			case 'l':
				assert(itr->m_points.size() == 2);
				agg2d.lineRel(itr->m_points[0], itr->m_points[1]);
				break;

			case 'V':
				assert(itr->m_points.size() == 1);
				agg2d.verLineTo(itr->m_points[0]);
				break;

			case 'v':
				assert(itr->m_points.size() == 1);
				agg2d.verLineRel(itr->m_points[0]);
				break;

			case 'H':
				assert(itr->m_points.size() == 1);
				agg2d.horLineTo(itr->m_points[0]);
				break;

			case 'h':
				assert(itr->m_points.size() == 1);
				agg2d.horLineTo(itr->m_points[0]);
				break;

			case 'Q':
				assert(itr->m_points.size() == 4);
				agg2d.quadricCurveTo(itr->m_points[0], itr->m_points[1], itr->m_points[2], itr->m_points[3]);
				break;

			case 'q':
				assert(itr->m_points.size() == 4);
				agg2d.quadricCurveRel(itr->m_points[0], itr->m_points[1], itr->m_points[2], itr->m_points[3]);
				break;

			case 'T':
				assert(itr->m_points.size() == 2);
				agg2d.quadricCurveTo(itr->m_points[0], itr->m_points[1]);
				break;

			case 't':
				assert(itr->m_points.size() == 2);
				agg2d.quadricCurveRel(itr->m_points[0], itr->m_points[1]);
				break;

			case 'C':
				assert(itr->m_points.size() == 6);
				agg2d.cubicCurveTo(itr->m_points[0], itr->m_points[1], itr->m_points[2], itr->m_points[3], itr->m_points[4], itr->m_points[5]);
				break;

			case 'c':
				assert(itr->m_points.size() == 6);
				agg2d.cubicCurveRel(itr->m_points[0], itr->m_points[1], itr->m_points[2], itr->m_points[3], itr->m_points[4], itr->m_points[5]);
				break;

			case 'S':
				assert(itr->m_points.size() == 4);
				agg2d.cubicCurveTo(itr->m_points[0], itr->m_points[1], itr->m_points[2], itr->m_points[3]);
				break;

			case 's':
				assert(itr->m_points.size() == 4);
				agg2d.cubicCurveRel(itr->m_points[0], itr->m_points[1], itr->m_points[2], itr->m_points[3]);
				break;

			case 'A': case 'a':
#ifdef WIN32
				throw std::exception("parse_path: Command A: NOT IMPLEMENTED YET");
#else
				throw std::exception();
#endif

			case 'Z': case 'z':
				//close_subpath();
				break;
			}
		}
	}

	void Render(Agg2D & agg2d, Path * path) const
	{
		if (!path)
			return;

		if (path->m_dash1 && path->m_dash2)
		{
			agg2d.dashClear();
			agg2d.dashAdd(path->m_dash1, path->m_dash2);
			//agg2d.dashAdd(5, 5);
			//agg2d.dashAdd(5, 5);
			agg2d.dashStart(10);
		}

		Render(agg2d, path->m_d);

		if (path->m_dash1 && path->m_dash2)
		{
		}
	}

	void Render(Agg2D & agg2d, Text * text) const
	{
		if (!text)
			return;

		m_agg2d.font(m_fonts->GetPath(text->m_font_family), text->m_font_size);
		Agg2D::TextAlignment xAlign = Agg2D::AlignCenter;
		Agg2D::TextAlignment yAlign = Agg2D::AlignBottom;
		switch(text->m_text_anchor)
		{
		case ANCHOR_LEFT:
			xAlign = Agg2D::AlignLeft;
			break;
		case ANCHOR_MIDDLE:
			xAlign = Agg2D::AlignCenter;
			break;
		case ANCHOR_RIGHT:
			xAlign = Agg2D::AlignRight;
			break;
		}

		agg2d.textAlignment(xAlign, yAlign);
		if (m_inHotItem)
			agg2d.fillColor(m_hotFillText.GetR(), m_hotFillText.GetG(), m_hotFillText.GetB(), m_hotFillText.GetA());
		else if (m_inSelectedItem)
			agg2d.fillColor(m_selectedFillText.GetR(), m_selectedFillText.GetG(), m_selectedFillText.GetB(), m_selectedFillText.GetA());
		else
		{
			StateColourMap::const_iterator found = m_colours.find(StateT(m_inType, m_inState));
			const Colour * text = (found != m_colours.end()) ? &found->second.m_text : &m_badColour;
			agg2d.fillColor(text->GetR(), text->GetG(), text->GetB(), text->GetA());
		}
		//else if (m_inState == XGMML_STATE_RUNNING)
		//	agg2d.fillColor(m_runningFillText.GetR(), m_runningFillText.GetG(), m_runningFillText.GetB(), m_runningFillText.GetA());
		//else if (m_inState == XGMML_STATE_COMPLETED)
		//	agg2d.fillColor(m_completedFillText.GetR(), m_completedFillText.GetG(), m_completedFillText.GetB(), m_completedFillText.GetA());
		//else
		//	agg2d.fillColor(m_normalFillText.GetR(), m_normalFillText.GetG(), m_normalFillText.GetB(), m_normalFillText.GetA());
		agg2d.noLine();
	}

	void Render(Agg2D & agg2d, Ellipse * ellipse) const
	{
		if (!ellipse)
			return;

		agg2d.resetPath();
		agg2d.addEllipse(ellipse->m_c.x, ellipse->m_c.y, ellipse->m_r.x, ellipse->m_r.y, Agg2D::CW);
	}

	void Render(Agg2D & agg2d, ElementG * elementG)
	{
		if (!elementG)
			return;

		for(EllipseVector::const_iterator itr = elementG->m_ellipses.begin(); itr != elementG->m_ellipses.end(); ++itr)
		{
			Render(agg2d, *itr);
			agg2d.drawPath(SetLineAndFill(agg2d, itr->get()->m_stroke, itr->get()->m_fill));
		}
		for(PolygonVector::const_iterator itr = elementG->m_polygons.begin(); itr != elementG->m_polygons.end(); ++itr)
		{
			Render(agg2d, *itr);
			agg2d.drawPath(SetLineAndFill(agg2d, itr->get()->m_stroke, itr->get()->m_fill));
		}
		for(PolygonVector::const_iterator itr = elementG->m_polylines.begin(); itr != elementG->m_polylines.end(); ++itr)
		{
			Render(agg2d, *itr);
			agg2d.drawPath(SetLineAndFill(agg2d, itr->get()->m_stroke, itr->get()->m_fill));
		}
		for(PathVector::const_iterator itr = elementG->m_paths.begin(); itr != elementG->m_paths.end(); ++itr)
		{
			Render(agg2d, *itr);
			if (m_scale > OVERVIEW_CUTOFF)
				agg2d.lineWidth(itr->get()->m_stroke_width);
			else
				m_agg2d.lineWidth(OVERVIEW_CUTOFF / m_scale);
			agg2d.drawPath(SetLineAndFill(agg2d, itr->get()->m_stroke, itr->get()->m_fill));
			agg2d.lineWidth(1.0);
			agg2d.dashClear();
		}
		if (m_scale > OVERVIEW_CUTOFF)
		{
			for (TextVector::const_iterator itr = elementG->m_lines.begin(); itr != elementG->m_lines.end(); ++itr)
			{
				Render(agg2d, *itr);
				agg2d.text(itr->get()->m_pos.x, itr->get()->m_pos.y, itr->get()->m_text.c_str());
			}
		}
	}

	void RenderCluster(ICluster * cluster, int depth = 0)
	{
		m_inType = RENDER_TYPE_CLUSTER;
		if (depth == 0)
			m_transparency = 1;
		else
			m_transparency = 3.0f / 2.0f;//m_scale > OVERVIEW_CUTOFF ? 1 : 2;

		Render(m_agg2d, GetElementG(cluster));
#ifdef SHOW_BOUNDBOX
		m_agg2d.fillColor(33 + depth * 10, 0x00, 0x00, 128);
		RectD rb = GetBoundingRect(cluster, true);
		m_agg2d.rectangle(rb.GetLeft(), rb.GetTop(), rb.GetRight(), rb.GetBottom());
#endif

		for(IClusterSet::const_iterator itr = cluster->GetClusters().begin(); itr != cluster->GetClusters().end(); ++itr)
		{
			if (HitTestItemFast(itr->get(), m_renderRect))
			{
				m_inHotItem = m_hotItem->IsHot(itr->get());
				m_inSelectedItem = m_selected->IsSelected(itr->get());
				m_inState = (XGMML_STATE_ENUM)itr->get()->GetPropertyInt(XGMML_STATE);
				if (m_inHotItem && m_inSelectedItem)
				{
					m_inHotItem = false;
					RenderCluster(itr->get(), depth + 1);
					m_inHotItem = true;
				}
				RenderCluster(itr->get(), depth + 1);
				m_inState = XGMML_STATE_UNKNOWN;
			}
		}

		m_inType = RENDER_TYPE_VERTEX;
		m_inHotItem = false;
		m_inSelectedItem = false;
		for(IVertexSet::const_iterator itr = cluster->GetVertices().begin(); itr != cluster->GetVertices().end(); ++itr)
		{
			if (HitTestItemFast(itr->get(), m_renderRect))
			{
				m_inHotItem = m_hotItem->IsHot(itr->get());
				m_inSelectedItem = m_selected->IsSelected(itr->get());
				m_inState = (XGMML_STATE_ENUM)itr->get()->GetPropertyInt(XGMML_STATE);
				if (m_inHotItem && m_inSelectedItem)
				{
					m_inHotItem = false;
					Render(m_agg2d, GetElementG(itr->get()));
					m_inHotItem = true;
				}
				Render(m_agg2d, GetElementG(itr->get()));
				m_inState = XGMML_STATE_UNKNOWN;

#ifdef SHOW_BOUNDBOX
				m_agg2d.fillColor(0x00, 33 + depth * 10, 0x00, 128);
				RectD rb = GetBoundingRect(itr->get(), true);
				m_agg2d.rectangle(rb.GetLeft(), rb.GetTop(), rb.GetRight(), rb.GetBottom());
#endif
			}
		}
		m_inType = RENDER_TYPE_UNKNOWN;
	}

	void RenderEdges(IGraph * g)
	{
		m_inType = RENDER_TYPE_EDGE;
		m_inHotItem = false;
		m_inSelectedItem = false;
		IEdgeSet hotEdges;  //  Draw hot items last
		for(IEdgeSet::const_iterator itr = g->GetAllEdges().begin(); itr != g->GetAllEdges().end(); ++itr)
		{
			if (HitTestItemFast(itr->get(), m_renderRect))	
			{
				if (m_hotItem->IsHot(itr->get()))
					hotEdges.insert(itr->get());
				else
				{
					m_inSelectedItem = m_selected->IsSelected(itr->get());
					m_inState = (XGMML_STATE_ENUM)itr->get()->GetPropertyInt(XGMML_STATE);
					Render(m_agg2d, GetElementG(itr->get()));
					m_inState = XGMML_STATE_UNKNOWN;
				}
			}
		}
		m_inHotItem = true;
		for (IEdgeSet::const_iterator itr = hotEdges.begin(); itr != hotEdges.end(); ++itr)	
		{
			Render(m_agg2d, GetElementG(itr->get()));
#ifdef SHOW_BOUNDBOX
			m_agg2d.fillColor(0x00, 0x00, 66, 128);
			RectD rb = GetBoundingRect(itr->get(), true);
			m_agg2d.rectangle(rb.GetLeft(), rb.GetTop(), rb.GetRight(), rb.GetBottom());
#endif
		}

		m_inType = RENDER_TYPE_UNKNOWN;
	}

	void DoRender(const RectI & _rect, bool clear)
	{
		RectD rect(_rect);
		rect = ScreenToWorld(rect);
		//if (m_renderRect != rect)
		{
			m_renderRect = rect;
			assert(_rect.Width() <= m_pixmap->Width() && _rect.Height() <= m_pixmap->Height());

			m_agg2d.attach(m_pixmap->GetBuffer(), m_pixmap->Width(), m_pixmap->Height(), m_pixmap->Stride());
			if (m_scale > OVERVIEW_CUTOFF)
				m_agg2d.antiAliasGamma(1.4);
			else
				m_agg2d.lineWidth(OVERVIEW_CUTOFF / m_scale);	//  Lines are never thiner than the cutoff
			m_agg2d.flipText(true);

			//  Set transform for AGG
			if (m_message.empty())
			{
				m_agg2d.translate(m_offset.x, m_offset.y);
				m_agg2d.scale(m_scale, m_scale);
			}
			m_agg2d.viewport(_rect.left, _rect.top, _rect.right, _rect.bottom, 0, 0, m_pixmap->Width(), m_pixmap->Height(), Agg2D::XMidYMid);

			if (clear)
				m_agg2d.clearAll(0x7f, 0x7f, 0x7f);
			m_agg2d.lineColor(0x00, 0x00, 0x00);

			m_agg2d.fillColor(0xff, 0xff, 0xff);
			m_agg2d.font(m_fonts->GetDefaultPath(), m_fonts->GetDefaultSize());

			if (!m_message.empty())
			{
				m_agg2d.text(12, 12, m_message.c_str());
			}
			else if (HitTestItemFast(m_g, m_renderRect))
			{
				m_inHotItem = m_hotItem->IsHot(m_g);
				m_inSelectedItem = m_selected->IsSelected(m_g);

				RenderCluster(m_g);

				m_inHotItem = m_hotItem->IsHot(m_g);
				m_inSelectedItem = m_selected->IsSelected(m_g);
				RenderEdges(m_g);
			}
		}
	}

	void DoRenderRect(const RectD & rect)
	{
		Colour black(Colour::DarkBlue), white(Colour::WhiteSmoke);
		m_agg2d.fillColor(black.GetR(), black.GetG(), black.GetB(), black.GetA() / 4);
		m_agg2d.lineColor(black.GetR(), black.GetG(), black.GetB(), 255);//m_hotStroke.GetA());
		m_agg2d.rectangle(rect.GetLeft(), rect.GetTop(), rect.GetRight(), rect.GetBottom());
	}
};

GRAPHRENDER_API IGraphRender * CreateGraphRender(IGraph * g, IGraphBuffer * pixmap, IGraphHotItem * hotItem, IGraphSelectionBag * selectionBag, double scale)
{
	return new CGraphRender(g, pixmap, hotItem, selectionBag, scale);
}
}
