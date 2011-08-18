#pragma once

#include <SvgShapes.h>

namespace ln
{
class CAggHitTest
{
public:
	virtual void SetRect(const RectI& rc)=0;
	virtual void ClearCaches()=0;
	virtual void Transform(double scale)=0;
	virtual void Transform(const PointD& offset)=0; 
	virtual void TransformReset()=0;

	virtual bool LineHitTest(
		const PointD& p1,
		const PointD& p2, 
		const PointD& ptest,
		double tolerance=0)=0;

	virtual bool SolidPolygonHitTest(
		const PointD* points, 
		unsigned point_count,
		const PointD& ptest,
		double tolerance=0)=0;

	virtual bool Bezier4HitTest(
		const PointD& p1,
		const PointD& p2,
		const PointD& p3,
		const PointD& p4,
		const PointD& ptest,
		double tolerance=0.0,
		double width=1.0,
		bool bArrow=true,
		double scale=1.0)=0;

	virtual bool BezierHitTest(
		const PointDVector& points,
		const PointD& ptest,
		double tolerance=0.0,
		double width=2.0,
		bool bArrow=true,
		double scale=1.0)=0;

	virtual bool LollyPopHitTest(
		const RectD& rc, 
		bool bLeft,
		const PointD& ptest,
		double tolerance=0)=0;

	static CAggHitTest* CreateAggHitTest();
};
}