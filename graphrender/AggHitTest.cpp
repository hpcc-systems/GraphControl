#ifdef AGGHITTEST
#include "platform.h"

#include "AggHitTest.h"

#include <agg2d.h>
#include <assert.h>

//*****************************************************************************

typedef agg::rasterizer_scanline_aa<> rasterizer_aa;
typedef agg::conv_transform<agg::path_storage, agg::trans_affine>	conv_path_trans_type;

inline int round_int(double x)
{
	assert(x > static_cast<double> (INT_MIN / 2) - 1.0);
	assert(x < static_cast<double> (INT_MAX / 2) + 1.0);

	const static float round_to_nearest = 0.5f;
#if _WIN64
	int i = x;
#elif _WIN32_WCE
	int i = x;
#else
	int i;
	__asm
	{
		fld x
		fadd st, st (0)
		fadd round_to_nearest
		fistp i
		sar i, 1
	}
#endif
	return i;
}
//*****************************************************************************

namespace ln
{
class CAggHitTestImpl : public CAggHitTest
{
	agg::path_storage m_path;
    agg::trans_affine m_mtx;
	conv_path_trans_type m_transpath;
	rasterizer_aa m_ras_aa;
	RectI m_rcUpdate;
public:
	CAggHitTestImpl();

	void SetRect(const RectI& rc);
	void ClearCaches();
	void Transform(double scale);
	void Transform(const PointD& offset); 
	void TransformReset() { m_mtx.reset(); }

	bool LineHitTest(
		const PointD& p1,
		const PointD& p2, 
		const PointD& ptest,
		double tolerance=0);

	bool SolidPolygonHitTest(
		const PointD* points, 
		unsigned point_count,
		const PointD& ptest,
		double tolerance=0);

	bool Bezier4HitTest(
		const PointD& p1,
		const PointD& p2,
		const PointD& p3,
		const PointD& p4,
		const PointD& ptest,
		double tolerance=0.0,
		double width=1.0,
		bool bArrow=true,
		double scale=1.0);

	bool CAggHitTestImpl::BezierHitTest(
		const PointDVector& points,
		const PointD& ptest,
		double tolerance=0.0,
		double width=2.0,
		bool bArrow=true,
		double scale=1.0);

	bool LollyPopHitTest(
		const RectD& rc, 
		bool bLeft,
		const PointD& ptest,
		double tolerance=0);
};

//*****************************************************************************

CAggHitTestImpl::CAggHitTestImpl()
	: m_transpath(m_path, m_mtx)
{
}

//*****************************************************************************

CAggHitTest* CAggHitTest::CreateAggHitTest()
{
	CAggHitTest* agght;

	agght=new CAggHitTestImpl();

	return agght;
}

//-----------------------------------------------------------------------------

void CAggHitTestImpl::SetRect(const RectI& rc)
{
	m_rcUpdate=rc;	
	m_ras_aa.clip_box(0, 0, m_rcUpdate.Width(), m_rcUpdate.Height()); 
}

//-----------------------------------------------------------------------------

void CAggHitTestImpl::ClearCaches()
{
	m_path.remove_all();
	m_ras_aa.reset();
}

//-----------------------------------------------------------------------------

void CAggHitTestImpl::Transform(double scale)
{
	m_mtx *= agg::trans_affine_scaling(scale);
}

//-----------------------------------------------------------------------------

void CAggHitTestImpl::Transform(const PointD& offset)
{
	m_mtx *= agg::trans_affine_translation(offset.x, offset.y);
}

//-----------------------------------------------------------------------------

bool CAggHitTestImpl::LineHitTest(
	const PointD& p1,
	const PointD& p2, 
	const PointD& ptest,
	double tolerance/*=0*/)
{
	m_path.move_to(p1.x, p1.y);
	m_path.line_to(p2.x, p2.y);

	typedef agg::conv_stroke<conv_path_trans_type> conv_trans_stroke_outline;
	conv_trans_stroke_outline stroke(m_transpath);
	stroke.width(tolerance);
	m_ras_aa.add_path(stroke);
	return m_ras_aa.hit_test(round_int(ptest.x), round_int(ptest.y));
}

//-----------------------------------------------------------------------------

bool CAggHitTestImpl::SolidPolygonHitTest(
	const PointD* points, 
	unsigned point_count,
	const PointD& ptest,
	double tolerance/*=0*/)
{
	assert(point_count>0);

	m_path.move_to(points->x, points->y);
	while(--point_count>0)
	{
		points++;
		m_path.line_to(points->x, points->y);
	}
	m_path.close_polygon();

	typedef agg::conv_stroke<conv_path_trans_type> conv_trans_stroke_outline;
	conv_trans_stroke_outline stroke(m_transpath);
	stroke.width(tolerance);
	m_ras_aa.add_path(stroke);
	return m_ras_aa.hit_test(round_int(ptest.x), round_int(ptest.y));
}

//-----------------------------------------------------------------------------

bool CAggHitTestImpl::Bezier4HitTest(
	const PointD& p1,
	const PointD& p2,
	const PointD& p3,
	const PointD& p4,
	const PointD& ptest,
	double tolerance/*=0.0*/,
	double width/*=1.0*/,
	bool bArrow/*=true*/,
	double scale/*=1.0*/)
{
	agg::curve4 curve(
		p1.x, p1.y,
		p2.x, p2.y,
		p3.x, p3.y,
		p4.x, p4.y);

 //   typedef agg::conv_stroke<agg::curve4, agg::vcgen_markers_term> conv_stroke_type;
 //   conv_stroke_type stroke(curve);
	//stroke.width(width+tolerance);

	//if(bArrow)
	//{
	//	AddPathWithArrowHead(m_ras_aa, stroke, m_mtx, 10, 3, 2, scale);
	//}
	//else
	//{
		typedef agg::conv_transform<conv_stroke_type, agg::trans_affine> conv_trans_type;
		conv_trans_type transstroke(stroke, m_mtx);
		m_ras_aa.add_path(transstroke);
	//}

	return m_ras_aa.hit_test(round_int(ptest.x), round_int(ptest.y));
}

//-----------------------------------------------------------------------------

bool CAggHitTestImpl::BezierHitTest(
	const PointDVector& points,
	const PointD& ptest,
	double tolerance/*=0.0*/,
	double width/*=2.0*/,
	bool bArrow/*=true*/,
	double scale/*=1.0*/)
{
    agg::curve_casteljau curve(points.size());
    curve.approximation_scale(scale);
	PointDVector::const_iterator itr=points.begin();
	for(; itr!=points.end();++itr)
	{
        curve.add_vertex((*itr).x, (*itr).y);
    }

    typedef agg::conv_stroke<agg::curve_casteljau, agg::vcgen_markers_term> conv_stroke_type;
    conv_stroke_type stroke(curve);
	stroke.width(width+tolerance);

	if(bArrow)
		AddPathWithArrowHead(m_ras_aa, stroke, m_mtx, 10, 3, 2, scale);
	else
	{
		typedef agg::conv_transform<conv_stroke_type, agg::trans_affine> conv_trans_type;
		conv_trans_type transstroke(stroke, m_mtx);
		m_ras_aa.add_path(transstroke);
	}

	return m_ras_aa.hit_test(round_int(ptest.x), round_int(ptest.y));
}

//-----------------------------------------------------------------------------

bool CAggHitTestImpl::LollyPopHitTest(
	const RectF& rc, 
	bool bLeft,
	const PointD& ptest,
	double tolerance/*=0*/)
{
	double radius=rc.Height/2;
	double split=rc.Width-rc.Height;
	double xcenter=bLeft? (rc.x+radius) : (rc.x+rc.Width-radius);
	double ycenter=rc.y+radius;

	agg::ellipse circle(xcenter, ycenter, radius, radius, 10);
	typedef agg::conv_transform<agg::ellipse, agg::trans_affine> conv_ellipse_trans_type;
	conv_ellipse_trans_type m_transcircle(circle, m_mtx);

	// connector line
	PointD p1, p2;
	p1.x=bLeft ? (rc.x+rc.Width-split) : rc.x; 
	p1.y=rc.y+radius; 

	p2.x=bLeft ? (rc.x+rc.Width) : (rc.x+split); 
	p2.y=p1.y; 

	m_path.move_to(p1.x, p1.y);
	m_path.line_to(p2.x, p2.y);

	m_ras_aa.add_path(m_transcircle);
	m_ras_aa.add_path(m_transpath);
	return m_ras_aa.hit_test(round_int(ptest.x), round_int(ptest.y));
}
}
#endif