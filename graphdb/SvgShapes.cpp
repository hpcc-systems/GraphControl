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

#include "SaxParser.h"
#include "SvgShapes.h"

namespace agg
{
namespace svg
{
	class path_tokenizer
	{
	 public:
		path_tokenizer() : m_path(0), m_last_command(0), m_last_number(0.0)
		{
			init_char_mask(m_commands_mask,   s_commands);
			init_char_mask(m_numeric_mask,    s_numeric);
			init_char_mask(m_separators_mask, s_separators);
		}

		void set_path_str(const char* str)
		{
			m_path = str;
			m_last_command = 0;
			m_last_number = 0.0;
		}

		bool next()
		{
			if(m_path == 0) return false;

			// Skip all white spaces and other garbage
			while(*m_path && !is_command(*m_path) && !is_numeric(*m_path))
			{
				if(!is_separator(*m_path))
				{
					char buf[100];
					sprintf(buf, "path_tokenizer::next : Invalid Character %c", *m_path);
#ifdef WIN32
					throw std::exception(buf);
#else
					throw std::exception();
#endif
				}
				m_path++;
			}

			if(*m_path == 0) return false;

			if(is_command(*m_path))
			{
				// Check if the command is a numeric sign character
				if(*m_path == '-' || *m_path == '+')
				{
					return parse_number();
				}
				m_last_command = *m_path++;
				while(*m_path && is_separator(*m_path)) m_path++;
				if(*m_path == 0) return true;
			}
			return parse_number();
		}

		double next(char cmd)
		{
			if(!next())
#ifdef WIN32
				throw std::exception("parse_path: Unexpected end of path");
#else
				throw std::exception();
#endif

			if(last_command() != cmd)
			{
				char buf[100];
				sprintf(buf, "parse_path: Command %c: bad or missing parameters", cmd);
#ifdef WIN32
				throw std::exception(buf);
#else
				throw std::exception();
#endif
			}
			return last_number();
		}

		char   last_command() const { return m_last_command; }
		double last_number() const { return m_last_number; }


	private:
		static void init_char_mask(char* mask, const char* char_set)
		{
			memset(mask, 0, 256/8);
			while(*char_set)
			{
				unsigned c = unsigned(*char_set++) & 0xFF;
				mask[c >> 3] |= 1 << (c & 7);
			}
		}

		bool contains(const char* mask, unsigned c) const
		{
			return (mask[(c >> 3) & (256/8-1)] & (1 << (c & 7))) != 0;
		}

		bool is_command(unsigned c) const
		{
			return contains(m_commands_mask, c);
		}

		bool is_numeric(unsigned c) const
		{
			return contains(m_numeric_mask, c);
		}

		bool is_separator(unsigned c) const
		{
			return contains(m_separators_mask, c);
		}

		bool parse_number()
		{
			char buf[256]; // Should be enough for any number
			char* buf_ptr = buf;

			// Copy all sign characters
			while(buf_ptr < buf+255 && (*m_path == '-' || *m_path == '+'))
			{
				*buf_ptr++ = *m_path++;
			}

			// Copy all numeric characters
			while(buf_ptr < buf+255 && is_numeric(*m_path))
			{
				*buf_ptr++ = *m_path++;
			}
			*buf_ptr = 0;
			m_last_number = atof(buf);
			return true;
		}

		char m_separators_mask[256/8];
		char m_commands_mask[256/8];
		char m_numeric_mask[256/8];

		const char* m_path;
		double m_last_number;
		char   m_last_command;

		static const char s_commands[];
		static const char s_numeric[];
		static const char s_separators[];
	};

	const char path_tokenizer::s_commands[] = "+-MmZzLlHhVvCcSsQqTtAaFfPp";
	const char path_tokenizer::s_numeric[] = ".Ee0123456789";
	const char path_tokenizer::s_separators[] = " ,\t\n\r";

	struct named_color
	{
		char name[22];
		unsigned char r, g, b, a;
	};

	named_color colors[] =
	{
		{ "aliceblue",240,248,255, 255 },
		{ "antiquewhite",250,235,215, 255 },
		{ "aqua",0,255,255, 255 },
		{ "aquamarine",127,255,212, 255 },
		{ "azure",240,255,255, 255 },
		{ "beige",245,245,220, 255 },
		{ "bisque",255,228,196, 255 },
		{ "black",0,0,0, 255 },
		{ "blanchedalmond",255,235,205, 255 },
		{ "blue",0,0,255, 255 },
		{ "blueviolet",138,43,226, 255 },
		{ "brown",165,42,42, 255 },
		{ "burlywood",222,184,135, 255 },
		{ "cadetblue",95,158,160, 255 },
		{ "chartreuse",127,255,0, 255 },
		{ "chocolate",210,105,30, 255 },
		{ "coral",255,127,80, 255 },
		{ "cornflowerblue",100,149,237, 255 },
		{ "cornsilk",255,248,220, 255 },
		{ "crimson",220,20,60, 255 },
		{ "cyan",0,255,255, 255 },
		{ "darkblue",0,0,139, 255 },
		{ "darkcyan",0,139,139, 255 },
		{ "darkgoldenrod",184,134,11, 255 },
		{ "darkgray",169,169,169, 255 },
		{ "darkgreen",0,100,0, 255 },
		{ "darkgrey",169,169,169, 255 },
		{ "darkkhaki",189,183,107, 255 },
		{ "darkmagenta",139,0,139, 255 },
		{ "darkolivegreen",85,107,47, 255 },
		{ "darkorange",255,140,0, 255 },
		{ "darkorchid",153,50,204, 255 },
		{ "darkred",139,0,0, 255 },
		{ "darksalmon",233,150,122, 255 },
		{ "darkseagreen",143,188,143, 255 },
		{ "darkslateblue",72,61,139, 255 },
		{ "darkslategray",47,79,79, 255 },
		{ "darkslategrey",47,79,79, 255 },
		{ "darkturquoise",0,206,209, 255 },
		{ "darkviolet",148,0,211, 255 },
		{ "deeppink",255,20,147, 255 },
		{ "deepskyblue",0,191,255, 255 },
		{ "dimgray",105,105,105, 255 },
		{ "dimgrey",105,105,105, 255 },
		{ "dodgerblue",30,144,255, 255 },
		{ "firebrick",178,34,34, 255 },
		{ "floralwhite",255,250,240, 255 },
		{ "forestgreen",34,139,34, 255 },
		{ "fuchsia",255,0,255, 255 },
		{ "gainsboro",220,220,220, 255 },
		{ "ghostwhite",248,248,255, 255 },
		{ "gold",255,215,0, 255 },
		{ "goldenrod",218,165,32, 255 },
		{ "gray",128,128,128, 255 },
		{ "green",0,128,0, 255 },
		{ "greenyellow",173,255,47, 255 },
		{ "grey",128,128,128, 255 },
		{ "honeydew",240,255,240, 255 },
		{ "hotpink",255,105,180, 255 },
		{ "indianred",205,92,92, 255 },
		{ "indigo",75,0,130, 255 },
		{ "ivory",255,255,240, 255 },
		{ "khaki",240,230,140, 255 },
		{ "lavender",230,230,250, 255 },
		{ "lavenderblush",255,240,245, 255 },
		{ "lawngreen",124,252,0, 255 },
		{ "lemonchiffon",255,250,205, 255 },
		{ "lightblue",173,216,230, 255 },
		{ "lightcoral",240,128,128, 255 },
		{ "lightcyan",224,255,255, 255 },
		{ "lightgoldenrodyellow",250,250,210, 255 },
		{ "lightgray",211,211,211, 255 },
		{ "lightgreen",144,238,144, 255 },
		{ "lightgrey",211,211,211, 255 },
		{ "lightpink",255,182,193, 255 },
		{ "lightsalmon",255,160,122, 255 },
		{ "lightseagreen",32,178,170, 255 },
		{ "lightskyblue",135,206,250, 255 },
		{ "lightslategray",119,136,153, 255 },
		{ "lightslategrey",119,136,153, 255 },
		{ "lightsteelblue",176,196,222, 255 },
		{ "lightyellow",255,255,224, 255 },
		{ "lime",0,255,0, 255 },
		{ "limegreen",50,205,50, 255 },
		{ "linen",250,240,230, 255 },
		{ "magenta",255,0,255, 255 },
		{ "maroon",128,0,0, 255 },
		{ "mediumaquamarine",102,205,170, 255 },
		{ "mediumblue",0,0,205, 255 },
		{ "mediumorchid",186,85,211, 255 },
		{ "mediumpurple",147,112,219, 255 },
		{ "mediumseagreen",60,179,113, 255 },
		{ "mediumslateblue",123,104,238, 255 },
		{ "mediumspringgreen",0,250,154, 255 },
		{ "mediumturquoise",72,209,204, 255 },
		{ "mediumvioletred",199,21,133, 255 },
		{ "midnightblue",25,25,112, 255 },
		{ "mintcream",245,255,250, 255 },
		{ "mistyrose",255,228,225, 255 },
		{ "moccasin",255,228,181, 255 },
		{ "navajowhite",255,222,173, 255 },
		{ "navy",0,0,128, 255 },
		{ "none", 0, 0, 0, 0 },
		{ "oldlace",253,245,230, 255 },
		{ "olive",128,128,0, 255 },
		{ "olivedrab",107,142,35, 255 },
		{ "orange",255,165,0, 255 },
		{ "orangered",255,69,0, 255 },
		{ "orchid",218,112,214, 255 },
		{ "palegoldenrod",238,232,170, 255 },
		{ "palegreen",152,251,152, 255 },
		{ "paleturquoise",175,238,238, 255 },
		{ "palevioletred",219,112,147, 255 },
		{ "papayawhip",255,239,213, 255 },
		{ "peachpuff",255,218,185, 255 },
		{ "peru",205,133,63, 255 },
		{ "pink",255,192,203, 255 },
		{ "plum",221,160,221, 255 },
		{ "powderblue",176,224,230, 255 },
		{ "purple",128,0,128, 255 },
		{ "red",255,0,0, 255 },
		{ "rosybrown",188,143,143, 255 },
		{ "royalblue",65,105,225, 255 },
		{ "saddlebrown",139,69,19, 255 },
		{ "salmon",250,128,114, 255 },
		{ "sandybrown",244,164,96, 255 },
		{ "seagreen",46,139,87, 255 },
		{ "seashell",255,245,238, 255 },
		{ "sienna",160,82,45, 255 },
		{ "silver",192,192,192, 255 },
		{ "skyblue",135,206,235, 255 },
		{ "slateblue",106,90,205, 255 },
		{ "slategray",112,128,144, 255 },
		{ "slategrey",112,128,144, 255 },
		{ "snow",255,250,250, 255 },
		{ "springgreen",0,255,127, 255 },
		{ "steelblue",70,130,180, 255 },
		{ "tan",210,180,140, 255 },
		{ "teal",0,128,128, 255 },
		{ "thistle",216,191,216, 255 },
		{ "tomato",255,99,71, 255 },
		{ "turquoise",64,224,208, 255 },
		{ "violet",238,130,238, 255 },
		{ "wheat",245,222,179, 255 },
		{ "white",255,255,255, 255 },
		{ "whitesmoke",245,245,245, 255 },
		{ "yellow",255,255,0, 255 },
		{ "yellowgreen",154,205,50, 255 },
		{ "zzzzzzzzzzz",0,0,0, 0 }
	};

	int cmp_color(const void* p1, const void* p2)
	{
		return strcmp(((named_color*)p1)->name, ((named_color*)p2)->name);
	}
} //namespace svg
} //namespace agg

namespace hpcc
{
double MulDiv(double val, double nominator, double denominator)
{
	return (val * nominator) / denominator;
}

Colour CreateColour(const std::string & colour)
{
	Colour retVal;
	if (colour.empty())
	{
		retVal.SetValue(0xff000000);
		return retVal;
	}

	const char * str = colour.c_str();
	while(*str == _T(' '))
		++str;
	unsigned argb = 0;
	if(*str == _T('#'))
	{
		sscanf(str + 1, "%x", &argb);
		retVal.SetValue(argb);
		if (retVal.GetA() == 0x00)
			retVal.SetValue(Colour::MakeARGB(0xff, retVal.GetR(), retVal.GetG(), retVal.GetB()));
	}
	else
	{
		agg::svg::named_color c;
		unsigned len = colour.length();
		if(len > sizeof(c.name) - 1)
		{
			assert(false);
#ifdef WIN32
			throw std::exception("parse_color: Invalid color name.");
#else
			throw std::exception();
#endif
		}
		strcpy(c.name, str);
		const void* p = bsearch(&c,
			agg::svg::colors,
			sizeof(agg::svg::colors) / sizeof(agg::svg::colors[0]),
			sizeof(agg::svg::colors[0]),
			agg::svg::cmp_color);
		if(p == 0)
		{
			assert(false);
#ifdef WIN32
			throw std::exception("parse_color: Invalid color name.");
#else
			throw std::exception();
#endif
		}
		const agg::svg::named_color* pc = (const agg::svg::named_color*)p;
		retVal = Colour(pc->a, pc->r, pc->g, pc->b);
	}
	return retVal;
}

PointD CreatePointD(const std::string & x, const std::string & y, const PointD & offset, int dpi)
{
	PointD retVal;
	try
	{
		retVal.x = boost::lexical_cast<double>(x);
		retVal.y = boost::lexical_cast<double>(y);
	}
	catch (const boost::bad_lexical_cast &)
	{
		assert(false);
	}
	retVal.Offset(offset);
	retVal = retVal.MulDiv(dpi, DOT_DPI);
	return retVal;
}

RectD CreateRectD(const std::string & rect, const PointD & offset, int dpi)
{
	boost::char_separator<char> separators(", ");
	typedef boost::tokenizer<boost::char_separator<char>, std::string::const_iterator, std::string > Tokenizer;
	Tokenizer tokens(rect, separators);
	Tokenizer::iterator itr = tokens.begin();
	assert(itr != tokens.end());
	std::string x = *itr++;
	assert(itr != tokens.end());
	std::string y = *itr++;
	assert(itr != tokens.end());
	std::string w = *itr++;
	assert(itr != tokens.end());
	std::string h = *itr++;
	return CreateRectD(x, y, w, h, offset, dpi);
}

RectD CreateRectD(const std::string & x, const std::string & y, const std::string & w, const std::string & h, const PointD & offset, int dpi)
{
	RectD retVal;
	try
	{
		retVal.x = boost::lexical_cast<double>(x) + offset.x;
		retVal.y = boost::lexical_cast<double>(y) + offset.y;
		retVal.Width = boost::lexical_cast<double>(w);
		retVal.Height = boost::lexical_cast<double>(h);
	}
	catch (const boost::bad_lexical_cast &)
	{
		assert(false);
	}
	retVal = retVal.MulDiv(dpi, DOT_DPI);
	return retVal;
}

Polygon::Polygon(const std::string & fill, const std::string & stroke, const std::string & points, const PointD & offset, int dpi) : m_fill(CreateColour(fill)), m_stroke(CreateColour(stroke))
{
	boost::char_separator<char> separators(", ");
	typedef boost::tokenizer<boost::char_separator<char>, std::string::const_iterator, std::string > Tokenizer;
	Tokenizer tokens(points, separators);
	for (Tokenizer::iterator itr = tokens.begin(); itr != tokens.end();)
	{
		Tokenizer::iterator curr_itr = itr++;
		Tokenizer::iterator next_itr = itr++;
		assert(next_itr != tokens.end());
		m_points.push_back(CreatePointD(*curr_itr, *next_itr, offset, dpi));
	}
}

void Polygon::CalcBoundingBox()
{
	bool first = true;
	m_rect = RectD();
	for (PointDVector::const_iterator itr = m_points.begin(); itr != m_points.end(); ++itr)
	{
		if (first)
		{
			first = false;
			m_rect = RectD(*itr, SizeD());
		}
		else
			m_rect.Union(*itr);
	}
}

Ellipse::Ellipse(const std::string& fill, const std::string & stroke, const std::string & cx, const std::string & cy, const std::string & rx, const std::string & ry, const PointD & offset, int dpi) : m_fill(CreateColour(fill)), m_stroke(CreateColour(stroke)), m_c(CreatePointD(cx, cy, offset, dpi)), m_r(CreatePointD(rx, ry, PointD(), dpi))
{
};

void Ellipse::CalcBoundingBox()
{
	m_rect.x = m_c.x - m_r.x;
	m_rect.y = m_c.y - m_r.y;
	m_rect.Width = m_r.x * 2;
	m_rect.Height = m_r.y * 2;
}

Path::Path(const std::string& fill, const std::string & stroke, const std::string & stroke_dasharray, const std::string & stroke_width, const std::string & d, const PointD & offset, int dpi) : m_fill(CreateColour(fill)), m_stroke(CreateColour(stroke))
{
	m_dash1 = 0;
	m_dash2 = 0;
	if (!stroke_dasharray.empty())
	{
		boost::char_separator<char> separators(", ");
		typedef boost::tokenizer<boost::char_separator<char>, std::string::const_iterator, std::string > Tokenizer;
		Tokenizer tokens(stroke_dasharray, separators);
		Tokenizer::iterator itr = tokens.begin();
		assert(itr != tokens.end());
		m_dash1 = boost::lexical_cast<int>(*itr++);
		assert(itr != tokens.end());
		m_dash2 = boost::lexical_cast<int>(*itr);
	}
	if (stroke_width.empty())
	{
		m_stroke_width = 1.0;
	}
	else 
	{
		try
		{
			m_stroke_width = boost::lexical_cast<double>(stroke_width);
		}
		catch (const boost::bad_lexical_cast &)
		{
			m_stroke_width = 1.0;
		}
	}
	agg::svg::path_tokenizer tok;
	tok.set_path_str(d.c_str());
	while (tok.next())
	{
		double arg[10];
		char cmd = tok.last_command();
		m_d.push_back(cmd);
		switch(cmd)
		{
		case 'M': case 'm':
		case 'L': case 'l':
		case 'T': case 't':
			arg[0] = MulDiv(tok.last_number() + offset.x, dpi, DOT_DPI);
			arg[1] = MulDiv(tok.next(cmd) + offset.y, dpi, DOT_DPI);
			m_d[m_d.size() - 1].m_points.push_back(arg[0]);
			m_d[m_d.size() - 1].m_points.push_back(arg[1]);
			break;

		case 'H': case 'h':
			arg[0] = MulDiv(tok.last_number() + offset.x, dpi, DOT_DPI);
			m_d[m_d.size() - 1].m_points.push_back(arg[0]);
			break;

		case 'V': case 'v':
			arg[0] = MulDiv(tok.last_number()  + offset.y, dpi, DOT_DPI);
			m_d[m_d.size() - 1].m_points.push_back(arg[0]);
			break;

		case 'Q': case 'q':
		case 'S': case 's':
			arg[0] = MulDiv(tok.last_number() + offset.x, dpi, DOT_DPI);
			m_d[m_d.size() - 1].m_points.push_back(arg[0]);
			for(unsigned int i = 1; i < 4; i++)
			{
				arg[i] = MulDiv(tok.next(cmd) + (i % 2 == 0 ? offset.x : offset.y), dpi, DOT_DPI);
				m_d[m_d.size() - 1].m_points.push_back(arg[i]);
			}
			break;

		case 'C': case 'c':
			arg[0] = MulDiv(tok.last_number() + offset.x, dpi, DOT_DPI);
			m_d[m_d.size() - 1].m_points.push_back(arg[0]);
			for(unsigned int i = 1; i < 6; i++)
			{
				arg[i] = MulDiv(tok.next(cmd) + (i % 2 == 0 ? offset.x : offset.y), dpi, DOT_DPI);
				m_d[m_d.size() - 1].m_points.push_back(arg[i]);
			}
			break;

		case 'A': case 'a':
#ifdef WIN32
			throw std::exception("parse_path: Command A: NOT IMPLEMENTED YET");
#else
			throw std::exception();
#endif
			break;

		case 'Z': case 'z':
			break;

		default:
			{
				char buf[100];
				sprintf(buf, "parse_path: Invalid Command %c", cmd);
#ifdef WIN32
				throw std::exception(buf);
#else
				throw std::exception();
#endif
			}
		}
	}
}

void Path::CalcBoundingBox()
{
	bool first = true;
	m_rect = RectD();
	for (AttrDPartVector::const_iterator itr = m_d.begin(); itr != m_d.end(); ++itr)
	{
		for (DoubleVector::const_iterator ditr = itr->m_points.begin(); ditr != itr->m_points.end(); ditr += 2)
		{
			DoubleVector::const_iterator ditr_next = ditr + 1;
			if (ditr_next != itr->m_points.end())
			{
				if (first)
				{
					first = false;
					m_rect.x = *ditr;
					m_rect.y = *ditr_next;
					m_rect.Width = 0;
					m_rect.Height = 0;
				}
				else
					m_rect.Union(PointD(*ditr, *ditr_next));
			}
		}
	}
}

Text::Text(const std::string & text_anchor, const std::string & x, const std::string & y, const std::string & font_family, const std::string & font_size, const std::string & fill, const std::string & text, const PointD & offset, int dpi) : m_font_family(font_family), m_fill(CreateColour(fill)), m_text(text)
{
	if (0 == text_anchor.compare("left"))
		m_text_anchor = ANCHOR_LEFT;
	else if (0 == text_anchor.compare("middle"))
		m_text_anchor = ANCHOR_MIDDLE;
	else if (0 == text_anchor.compare("right"))
		m_text_anchor = ANCHOR_RIGHT;
	else
		m_text_anchor = ANCHOR_UNKNOWN;

	if (boost::algorithm::equals(m_text, "."))
	{
		m_text_anchor = ANCHOR_LEFT;
		m_text="";
	}	
	try
	{
		m_pos = CreatePointD(x, y, offset, dpi);
		m_font_size = boost::lexical_cast<double>(font_size);
	}
	catch (const boost::bad_lexical_cast &)
	{
		assert(false);
	}
}

void Text::CalcBoundingBox()
{
	double textWidth = m_text.length() * (m_font_size / (1.75));
	m_rect = RectD(m_pos.x - textWidth / 2.0, m_pos.y - m_font_size / 2.0, textWidth, m_font_size);
}

ElementG::ElementG()
{
	m_visible = true;
}

ElementG::ElementG(const RectD & forcedSize)
{
	m_visible = false;
	m_rect = forcedSize;
}

bool ElementG::IsVisible() const
{
	return m_visible;
}

void ElementG::CalcBoundingBox()
{
	bool first = true;
	m_rect = RectD();
	for(PathVector::const_iterator itr = m_paths.begin(); itr != m_paths.end(); ++itr)
	{
		if (first)
		{
			first = false;
			m_rect = itr->get()->GetBoundingBox();
		}
		else
			m_rect.Union(itr->get()->GetBoundingBox());
	}
	for(PolygonVector::const_iterator itr = m_polygons.begin(); itr != m_polygons.end(); ++itr)
	{
		if (first)
		{
			first = false;
			m_rect = itr->get()->GetBoundingBox();
		}
		else
			m_rect.Union(itr->get()->GetBoundingBox());
	}
	for(EllipseVector::const_iterator itr = m_ellipses.begin(); itr != m_ellipses.end(); ++itr)
	{
		if (first)
		{
			first = false;
			m_rect = itr->get()->GetBoundingBox();
		}
		else
			m_rect.Union(itr->get()->GetBoundingBox());
	}
	for(TextVector::const_iterator itr = m_lines.begin(); itr != m_lines.end(); ++itr)
	{
		if (first)
		{
			first = false;
			m_rect = itr->get()->GetBoundingBox();
		}
		else
			m_rect.Union(itr->get()->GetBoundingBox());
	}
}
}
