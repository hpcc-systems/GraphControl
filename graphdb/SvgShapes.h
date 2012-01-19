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

#include "Unknown.h"

namespace hpcc
{
#define REAL_MAX            FLT_MAX
#define REAL_MIN            FLT_MIN
#define REAL_TOLERANCE     (FLT_MIN * 100)
#define REAL_EPSILON        1.192092896e-07F        /* FLT_EPSILON */
#define DOT_DPI 72

class SizeD;
//class PointD;
class RectD;

class SizeD
{
public:
	SizeD()
	{
		Width = Height = 0.0f;
	}

	SizeD(const SizeD& size)
	{
		Width = size.Width;
		Height = size.Height;
	}

	SizeD(double width, double height)
	{
		Width = width;
		Height = height;
	}

	SizeD operator+(const SizeD& sz) const
	{
		return SizeD(Width + sz.Width,
					 Height + sz.Height);
	}

	SizeD operator-(const SizeD& sz) const
	{
		return SizeD(Width - sz.Width,
					 Height - sz.Height);
	}

	bool Equals(const SizeD& sz) const
	{
		return (Width == sz.Width) && (Height == sz.Height);
	}

	bool Empty() const
	{
		return (Width == 0.0f && Height == 0.0f);
	}

public:

	double Width;
	double Height;
};

template<typename T>
class PointT
{
public:
	PointT()
	{
		x = y = 0.0f;
	}

	PointT(const PointT<T> &point)
	{
		x = point.x;
		y = point.y;
	}

	PointT(const SizeD &size)
	{
		x = size.Width;
		y = size.Height;
	}

	PointT(T _x, T _y)
	{
		x = _x;
		y = _y;
	}

	~PointT()
	{
	}

	PointT<T> operator+(const PointT<T>& point) const
	{
		return PointT<T>(x + point.x, y + point.y);
	}

	PointT<T> operator-(const PointT<T>& point) const
	{
		return PointT<T>(x - point.x, y - point.y);
	}

	bool Equals(const PointT<T>& point)
	{
		return (x == point.x) && (y == point.y);
	}

	void Offset(const PointT<T>& point)
	{
		Offset(point.x, point.y);
	}

	void Offset(T dx, T dy)
	{
		x += dx;
		y += dy;
	}

	PointT<T> Translate(T _x, T _y) const
	{
		return PointT<T>(x + _x, y + _y);
	}

	bool Empty() const
	{
		return (x == 0.0f && y == 0.0f);
	}

	PointT<T> MulDiv(T multiplier, T divisor) const 
	{
		return PointT<T>(
			(x * multiplier) / divisor,
			(y * multiplier) / divisor);
	}

public:
	T x;
	T y;
};
typedef PointT<double> PointD;
typedef std::vector<PointD> PointDVector;
PointD CreatePointD(const std::string & x, const std::string & y, const PointD & offset, int dpi = 96);

template<typename T>
class RectT 
{
public:
	T left;
	T top;
	T right;
	T bottom;

public:
	RectT()
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
	RectT(T _left, T _top, T _right, T _bottom)
	{
		left = _left;
		top = _top;
		right = _right;
		bottom = _bottom;
	}

	T Width() const 
	{
		return right - left;
	}

	T Height() const 
	{
		return bottom - top;
	}

	void Offset(const PointT<T>& point)
	{
		Offset(point.x, point.y);
	}

	void Offset(T dx, T dy)
	{
		left += dx;
		top += dy;
		right += dx;
		bottom += dy;
	}

	bool operator == (const RectT<T> & other) const
	{
		return (other.left == left && other.top == top && other.right == right && other.bottom == bottom);
	}

	bool operator != (const RectT<T> & other) const
	{
		return !(operator == (other));
	}
};
typedef RectT<unsigned int> RectI;

class RectD 
{
public:
	RectD()
	{
		x = y = Width = Height = 0.0f;
	}

	RectD(const RectI & rc)
	{
		x = rc.left;
		y = rc.top;
		Width = rc.right - x;
		Height = rc.bottom - y;
	}

	RectD(double _x, double _y, double width, double height)
	{
		x = _x;
		y = _y;
		Width = width;
		Height = height;
	}

	RectD(const PointD& location,
		  const SizeD& size)
	{
		x = location.x;
		y = location.y;
		Width = size.Width;
		Height = size.Height;
	}

	RectD(const SizeD& size)
	{
		x = 0.0f;
		y = 0.0f;
		Width = size.Width;
		Height = size.Height;
	}

	RectD* Clone() const
	{
		return new RectD(x, y, Width, Height);
	}

	void GetLocation(PointD* point) const
	{
		point->x = x;
		point->y = y;
	}

	void SetLocation(const PointD* point)
	{
		x = point->x;
		y = point->y;
	}

	void GetSize(SizeD* size) const
	{
		size->Width = Width;
		size->Height = Height;
	}

	void GetBounds(RectD* rect) const
	{
		rect->x = x;
		rect->y = y;
		rect->Width = Width;
		rect->Height = Height;
	}

	void GetCenter(PointD* point) const
	{
		point->x = x + Width / 2;
		point->y = y + Height / 2;
	}

	void GetCenterTop(PointD* point) const
	{
		point->x = x + Width / 2;
		point->y = y;
	}

	double GetLeft() const
	{
		return x;
	}

	double GetTop() const
	{
		return y;
	}

	double GetRight() const
	{
		return x+Width;
	}

	double GetBottom() const
	{
		return y+Height;
	}

	int GetIntWidth() const
	{
		return (int)(Width + 0.5);
	}

	int GetIntHeight() const
	{
		return (int)(Height + 0.5);
	}

	bool IsEmptyArea() const
	{
		return (Width <= REAL_EPSILON) || (Height <= REAL_EPSILON);
	}

	bool Equals(const RectD & rect) const
	{
		return x == rect.x &&
			   y == rect.y &&
			   Width == rect.Width &&
			   Height == rect.Height;
	}

	bool Contains(double _x,
				  double _y) const
	{
		return _x >= x && _x < x+Width && _y >= y && _y < y+Height;
	}

	bool Contains(const PointD& pt) const
	{
		return Contains(pt.x, pt.y);
	}

	bool Contains(const RectD& rect) const
	{
		return (x <= rect.x) && (rect.GetRight() <= GetRight()) &&
			   (y <= rect.y) && (rect.GetBottom() <= GetBottom());
	}

	void Inflate(double dx,
				 double dy)
	{
		x -= dx;
		y -= dy;
		Width += 2*dx;
		Height += 2*dy;
	}

	void Inflate(const PointD& point)
	{
		Inflate(point.x, point.y);
	}

	bool Intersect(const RectD& rect)
	{
		return Intersect(*this, *this, rect);
	}

	static bool Intersect(RectD& c,
						  const RectD& a,
						  const RectD& b)
	{
		double right = std::min<double>(a.GetRight(), b.GetRight());
		double bottom = std::min<double>(a.GetBottom(), b.GetBottom());
		double left = std::max<double>(a.GetLeft(), b.GetLeft());
		double top = std::max<double>(a.GetTop(), b.GetTop());

		c.x = left;
		c.y = top;
		c.Width = right - left;
		c.Height = bottom - top;
		return !c.IsEmptyArea();
	}

	bool IntersectsWith(const RectD& rect) const
	{
		return (GetLeft() < rect.GetRight() &&
				GetTop() < rect.GetBottom() &&
				GetRight() > rect.GetLeft() &&
				GetBottom() > rect.GetTop());
	}

	bool Union(const RectD& rect)
	{
		return Union(*this, *this, rect);
	}

	static bool Union(RectD& c,
					  const RectD& a,
					  const RectD& b)
	{
		double right = std::max<double>(a.GetRight(), b.GetRight());
		double bottom = std::max<double>(a.GetBottom(), b.GetBottom());
		double left = std::min<double>(a.GetLeft(), b.GetLeft());
		double top = std::min<double>(a.GetTop(), b.GetTop());

		c.x = left;
		c.y = top;
		c.Width = right - left;
		c.Height = bottom - top;
		return !c.IsEmptyArea();
	}

	bool Union(const PointD& pt)
	{
		return Union(*this, *this, pt);
	}

	static bool Union(RectD& c,
					  const RectD& a,
					  const PointD& b)
	{
		double right = std::max<double>(a.GetRight(), b.x);
		double bottom = std::max<double>(a.GetBottom(), b.y);
		double left = std::min<double>(a.GetLeft(), b.x);
		double top = std::min<double>(a.GetTop(), b.y);

		c.x = left;
		c.y = top;
		c.Width = right - left;
		c.Height = bottom - top;
		return !c.IsEmptyArea();
	}

	void Offset(const PointD& point)
	{
		Offset(point.x, point.y);
	}

	void Offset(double dx, double dy)
	{
		x += dx;
		y += dy;
	}

	RectD MulDiv(double multiplier, double divisor) const 
	{
		return RectD(
			(x * multiplier) / divisor,
			(y * multiplier) / divisor,
			(Width * multiplier) / divisor,
			(Height * multiplier) / divisor);
	}

	RectD operator+(const PointD& point) const
	{
		return RectD(x + point.x, y + point.y, Width, Height);
	}

	RectD operator-(const PointD& point) const
	{
		return RectD(x - point.x, y - point.y, Width, Height);
	}

	bool operator == (const RectD & other) const
	{
		return (other.x == x && other.y == y && other.Width == Width && other.Height == Height);
	}

	bool operator != (const RectD & other) const
	{
		return !(operator == (other));
	}

public:

	double x;
	double y;
	double Width;
	double Height;
};
RectD CreateRectD(const std::string & rect, const PointD & offset, int dpi = 96);
RectD CreateRectD(const std::string & x, const std::string & y, const std::string & w, const std::string & h, const PointD & offset, int dpi = 96);

class Colour : public CUnknown
{
public:
	//----------------------------------------------------------------------------
	// Colour mode
	//----------------------------------------------------------------------------

	enum ColourMode
	{
		ColourModeARGB32 = 0,
		ColourModeARGB64 = 1
	};

	//----------------------------------------------------------------------------
	// Colour Channel flags
	//----------------------------------------------------------------------------

	enum ColourChannelFlags
	{
		ColourChannelFlagsC = 0,
		ColourChannelFlagsM,
		ColourChannelFlagsY,
		ColourChannelFlagsK,
		ColourChannelFlagsLast
	};

	//----------------------------------------------------------------------------
	// Colour
	//----------------------------------------------------------------------------
	typedef unsigned long ARGB;
	#ifdef WIN32
	typedef unsigned __int64 ARGB64;
	#else
	typedef uint64_t ARGB64;
	#endif
	typedef unsigned char BYTE;

	BEGIN_CUNKNOWN
	END_CUNKNOWN

	Colour()
	{
		Argb = 0x0;
	}

	// Construct an opaque Colour object with
	// the specified Red, Green, Blue values.
	//
	// Colour values are not premultiplied.

	Colour(BYTE r,
		  BYTE g,
		  BYTE b)
	{
		Argb = MakeARGB(255, r, g, b);
	}

	Colour(BYTE a,
		  BYTE r,
		  BYTE g,
		  BYTE b)
	{
		Argb = MakeARGB(a, r, g, b);
	}

	Colour(ARGB argb)
	{
		Argb = argb;
	}

	BYTE GetAlpha() const
	{
		return (BYTE) (Argb >> AlphaShift);
	}

	BYTE GetA() const
	{
		return GetAlpha();
	}

	BYTE GetRed() const
	{
		return (BYTE) (Argb >> RedShift);
	}

	BYTE GetR() const
	{
		return GetRed();
	}

	BYTE GetGreen() const
	{
		return (BYTE) (Argb >> GreenShift);
	}

	BYTE GetG() const
	{
		return GetGreen();
	}

	BYTE GetBlue() const
	{
		return (BYTE) (Argb >> BlueShift);
	}

	BYTE GetB() const
	{
		return GetBlue();
	}

	ARGB GetValue() const
	{
		return Argb;
	}

	bool IsEmpty() const
	{
		return Argb == 0;
	}

	void SetValue(ARGB argb)
	{
		Argb = argb;
	}

	void Darken()
	{
		double r = GetR() * 2.0f / 3.0f;
		double g = GetG() * 2.0f / 3.0f;
		double b = GetB() * 2.0f / 3.0f;
		SetValue(MakeARGB(GetA(), static_cast<BYTE>(r), static_cast<BYTE>(g), static_cast<BYTE>(b)));
	}

	void Lighten()
	{
		double r = std::min<double>(GetR() * 2.0f, 255.0f);
		double g = std::min<double>(GetG() * 2.0f, 255.0f);
		double b = std::min<double>(GetB() * 2.0f, 255.0f);
		SetValue(MakeARGB(GetA(), static_cast<BYTE>(r), static_cast<BYTE>(g), static_cast<BYTE>(b)));
	}

	//void MoreBright(unsigned short step=1);
	//void LessBright(unsigned short step=1);
	//void MoreSaturated(unsigned short step=1);
	//void LessSaturated(unsigned short step=1);
	//unsigned short GetHue() const;
	//unsigned short GetLuminance() const;
	//unsigned short GetSaturation() const;
	//void GetHLS(unsigned short hls[3]) const;

	//void Complementary(Colour& comp) const
	//{
	//	comp.SetValue(MakeARGB(GetA(), 255-GetR(), 255-GetG(), 255-GetB()));
	//}

	//bool IsDarker(const Colour& Colour) const
	//{
	//	WORD mylum=GetLuminance();
	//	WORD hislum=Colour.GetLuminance();
	//	// eventually use percentage rather than raw value comparison
	//	return mylum<hislum;
	//}
	//bool IsLighter(const Colour& Colour) const
	//{
	//	WORD mylum=GetLuminance();
	//	WORD hislum=Colour.GetLuminance();
	//	return mylum>hislum;
	//}


public:

	// Common Colour constants

	enum
	{
		AliceBlue            = 0xFFF0F8FF,
		AntiqueWhite         = 0xFFFAEBD7,
		Aqua                 = 0xFF00FFFF,
		Aquamarine           = 0xFF7FFFD4,
		Azure                = 0xFFF0FFFF,
		Beige                = 0xFFF5F5DC,
		Bisque               = 0xFFFFE4C4,
		Black                = 0xFF000000,
		BlanchedAlmond       = 0xFFFFEBCD,
		Blue                 = 0xFF0000FF,
		BlueViolet           = 0xFF8A2BE2,
		Brown                = 0xFFA52A2A,
		BurlyWood            = 0xFFDEB887,
		CadetBlue            = 0xFF5F9EA0,
		Chartreuse           = 0xFF7FFF00,
		Chocolate            = 0xFFD2691E,
		Coral                = 0xFFFF7F50,
		CornflowerBlue       = 0xFF6495ED,
		Cornsilk             = 0xFFFFF8DC,
		Crimson              = 0xFFDC143C,
		Cyan                 = 0xFF00FFFF,
		DarkBlue             = 0xFF00008B,
		DarkCyan             = 0xFF008B8B,
		DarkGoldenrod        = 0xFFB8860B,
		DarkGray             = 0xFFA9A9A9,
		DarkGreen            = 0xFF006400,
		DarkKhaki            = 0xFFBDB76B,
		DarkMagenta          = 0xFF8B008B,
		DarkOliveGreen       = 0xFF556B2F,
		DarkOrange           = 0xFFFF8C00,
		DarkOrchid           = 0xFF9932CC,
		DarkRed              = 0xFF8B0000,
		DarkSalmon           = 0xFFE9967A,
		DarkSeaGreen         = 0xFF8FBC8B,
		DarkSlateBlue        = 0xFF483D8B,
		DarkSlateGray        = 0xFF2F4F4F,
		DarkTurquoise        = 0xFF00CED1,
		DarkViolet           = 0xFF9400D3,
		DeepPink             = 0xFFFF1493,
		DeepSkyBlue          = 0xFF00BFFF,
		DimGray              = 0xFF696969,
		DodgerBlue           = 0xFF1E90FF,
		Firebrick            = 0xFFB22222,
		FloralWhite          = 0xFFFFFAF0,
		ForestGreen          = 0xFF228B22,
		Fuchsia              = 0xFFFF00FF,
		Gainsboro            = 0xFFDCDCDC,
		GhostWhite           = 0xFFF8F8FF,
		Gold                 = 0xFFFFD700,
		Goldenrod            = 0xFFDAA520,
		Gray                 = 0xFF808080,
		Green                = 0xFF008000,
		GreenYellow          = 0xFFADFF2F,
		Honeydew             = 0xFFF0FFF0,
		HotPink              = 0xFFFF69B4,
		IndianRed            = 0xFFCD5C5C,
		Indigo               = 0xFF4B0082,
		Ivory                = 0xFFFFFFF0,
		Khaki                = 0xFFF0E68C,
		Lavender             = 0xFFE6E6FA,
		LavenderBlush        = 0xFFFFF0F5,
		LawnGreen            = 0xFF7CFC00,
		LemonChiffon         = 0xFFFFFACD,
		LightBlue            = 0xFFADD8E6,
		LightCoral           = 0xFFF08080,
		LightCyan            = 0xFFE0FFFF,
		LightGoldenrodYellow = 0xFFFAFAD2,
		LightGray            = 0xFFD3D3D3,
		LightGreen           = 0xFF90EE90,
		LightPink            = 0xFFFFB6C1,
		LightSalmon          = 0xFFFFA07A,
		LightSeaGreen        = 0xFF20B2AA,
		LightSkyBlue         = 0xFF87CEFA,
		LightSlateGray       = 0xFF778899,
		LightSteelBlue       = 0xFFB0C4DE,
		LightYellow          = 0xFFFFFFE0,
		Lime                 = 0xFF00FF00,
		LimeGreen            = 0xFF32CD32,
		Linen                = 0xFFFAF0E6,
		Magenta              = 0xFFFF00FF,
		Maroon               = 0xFF800000,
		MediumAquamarine     = 0xFF66CDAA,
		MediumBlue           = 0xFF0000CD,
		MediumOrchid         = 0xFFBA55D3,
		MediumPurple         = 0xFF9370DB,
		MediumSeaGreen       = 0xFF3CB371,
		MediumSlateBlue      = 0xFF7B68EE,
		MediumSpringGreen    = 0xFF00FA9A,
		MediumTurquoise      = 0xFF48D1CC,
		MediumVioletRed      = 0xFFC71585,
		MidnightBlue         = 0xFF191970,
		MintCream            = 0xFFF5FFFA,
		MistyRose            = 0xFFFFE4E1,
		Moccasin             = 0xFFFFE4B5,
		NavajoWhite          = 0xFFFFDEAD,
		Navy                 = 0xFF000080,
		OldLace              = 0xFFFDF5E6,
		Olive                = 0xFF808000,
		OliveDrab            = 0xFF6B8E23,
		Orange               = 0xFFFFA500,
		OrangeRed            = 0xFFFF4500,
		Orchid               = 0xFFDA70D6,
		PaleGoldenrod        = 0xFFEEE8AA,
		PaleGreen            = 0xFF98FB98,
		PaleTurquoise        = 0xFFAFEEEE,
		PaleVioletRed        = 0xFFDB7093,
		PapayaWhip           = 0xFFFFEFD5,
		PeachPuff            = 0xFFFFDAB9,
		Peru                 = 0xFFCD853F,
		Pink                 = 0xFFFFC0CB,
		Plum                 = 0xFFDDA0DD,
		PowderBlue           = 0xFFB0E0E6,
		Purple               = 0xFF800080,
		Red                  = 0xFFFF0000,
		RosyBrown            = 0xFFBC8F8F,
		RoyalBlue            = 0xFF4169E1,
		SaddleBrown          = 0xFF8B4513,
		Salmon               = 0xFFFA8072,
		SandyBrown           = 0xFFF4A460,
		SeaGreen             = 0xFF2E8B57,
		SeaShell             = 0xFFFFF5EE,
		Sienna               = 0xFFA0522D,
		Silver               = 0xFFC0C0C0,
		SkyBlue              = 0xFF87CEEB,
		SlateBlue            = 0xFF6A5ACD,
		SlateGray            = 0xFF708090,
		Snow                 = 0xFFFFFAFA,
		SpringGreen          = 0xFF00FF7F,
		SteelBlue            = 0xFF4682B4,
		Tan                  = 0xFFD2B48C,
		Teal                 = 0xFF008080,
		Thistle              = 0xFFD8BFD8,
		Tomato               = 0xFFFF6347,
		Transparent          = 0x00FFFFFF,
		Turquoise            = 0xFF40E0D0,
		Violet               = 0xFFEE82EE,
		Wheat                = 0xFFF5DEB3,
		White                = 0xFFFFFFFF,
		WhiteSmoke           = 0xFFF5F5F5,
		Yellow               = 0xFFFFFF00,
		YellowGreen          = 0xFF9ACD32
	};

	// Shift count and bit mask for A, R, G, B components

	enum
	{
		AlphaShift  = 24,
		RedShift    = 16,
		GreenShift  = 8,
		BlueShift   = 0
	};

	enum
	{
		AlphaMask   = 0xff000000,
		RedMask     = 0x00ff0000,
		GreenMask   = 0x0000ff00,
		BlueMask    = 0x000000ff
	};

	// Assemble A, R, G, B values into a 32-bit integer

	static ARGB MakeARGB(BYTE a,
						 BYTE r,
						 BYTE g,
						 BYTE b)
	{
		return (((ARGB) (b) <<  BlueShift) |
				((ARGB) (g) << GreenShift) |
				((ARGB) (r) <<   RedShift) |
				((ARGB) (a) << AlphaShift));
	}

	unsigned long ToBGR()
	{
		return (((ARGB) (GetRed()) <<  BlueShift) |
				((ARGB) (GetGreen()) << GreenShift) |
				((ARGB) (GetBlue()) <<   RedShift));
	}


protected:

	ARGB Argb;
};
Colour CreateColour(const std::string & colour);

class GRAPHDB_API BoundingBox : public CUnknown
{
protected:
	RectD m_rect;

public:
	BEGIN_CUNKNOWN
	END_CUNKNOWN

	RectD GetBoundingBox()
	{
		if (m_rect.IsEmptyArea())
			CalcBoundingBox();
		return m_rect;
	}

	void SetBoundingBox(const RectD & boudningBox)
	{
		m_rect = boudningBox;
	}

	virtual void CalcBoundingBox() = 0;
};

class GRAPHDB_API Ellipse : public BoundingBox
{
public:
	Colour m_fill;
	Colour m_stroke;
	PointD m_c;
	PointD m_r;

	BEGIN_CUNKNOWN
	END_CUNKNOWN

	Ellipse();
	Ellipse(const std::string& fill, const std::string & stroke, const std::string & cx, const std::string & cy, const std::string & rx, const std::string & ry, const PointD & offset, int dpi = 96);

	virtual void CalcBoundingBox();
};
typedef CUnknownPtr<Ellipse> EllipsePtr;
typedef std::vector<EllipsePtr> EllipseVector;

class GRAPHDB_API Polygon : public BoundingBox
{
public:
	Colour m_fill;
	Colour m_stroke;
	PointDVector m_points;

	BEGIN_CUNKNOWN
	END_CUNKNOWN

	Polygon();
	Polygon(const std::string& fill, const std::string & stroke, const std::string & points, const PointD & offset, int dpi = 96);

	virtual void CalcBoundingBox();
};
typedef CUnknownPtr<Polygon> PolygonPtr;
typedef std::vector<PolygonPtr> PolygonVector;

typedef std::vector<double> DoubleVector;
struct AttrDPart
{
public:
	char m_command;
	DoubleVector m_points;

	AttrDPart(char command) : m_command(command)
	{
	}
};
typedef std::vector<AttrDPart> AttrDPartVector;

class GRAPHDB_API Path : public BoundingBox
{
public:
	Colour m_fill;
	Colour m_stroke;
	double m_stroke_width;
	int m_dash1;
	int m_dash2;
	AttrDPartVector m_d;

	BEGIN_CUNKNOWN
	END_CUNKNOWN

	Path();
	Path(const std::string& fill, const std::string & stroke, const std::string & stroke_dasharrau, const std::string & stroke_width, const std::string & d, const PointD & offset, int dpi = 96);

	virtual void CalcBoundingBox();
};
typedef CUnknownPtr<Path> PathPtr;
typedef std::vector<PathPtr> PathVector;

enum ANCHOR {
	ANCHOR_UNKNOWN = 0,
	ANCHOR_LEFT,
	ANCHOR_MIDDLE,
	ANCHOR_RIGHT,
	ANCHOR_LAST
};

class GRAPHDB_API Text : public BoundingBox
{
public:
	ANCHOR m_text_anchor;
	PointD m_pos;
	std::string m_font_family;
	double m_font_size;
	Colour m_fill;
	std::string m_text;

	BEGIN_CUNKNOWN
	END_CUNKNOWN

	Text();
	Text(const std::string & text_anchor, const std::string & x, const std::string & y, const std::string & font_family, const std::string & font_size, const std::string & fill, const std::string & text, const PointD & offset, int dpi = 96);

	virtual void CalcBoundingBox();
};
typedef CUnknownPtr<Text> TextPtr;
typedef std::vector<TextPtr> TextVector;

class GRAPHDB_API ElementG : public BoundingBox
{
protected:
	bool m_visible;

public:
	EllipseVector m_ellipses;
	TextVector m_lines;
	PathVector m_paths;
	PolygonVector m_polygons;
	PolygonVector m_polylines;

	BEGIN_CUNKNOWN
	END_CUNKNOWN

	ElementG();
	ElementG(const RectD & forcedSize);
	bool IsVisible() const;
	virtual void CalcBoundingBox();
};
typedef CUnknownPtr<ElementG> ElementGPtr;

}
