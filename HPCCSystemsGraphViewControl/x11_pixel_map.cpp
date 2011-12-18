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
#ifdef XP_UNIXXXX
#include "x11_pixel_map.h"

#include <agg_basics.h>
#include <util/agg_color_conv_rgb8.h>
#include <platform/agg_platform_support.h>

void calcDisplayType(GdkVisual * visual, int & depth, int & sys_bpp, const agg::pix_format_e & format, agg::pix_format_e & sys_format, int & byte_order)
{
	depth   = visual->depth;

	unsigned long r_mask = visual->red_mask;
	unsigned long g_mask = visual->green_mask;
	unsigned long b_mask = visual->blue_mask;

	if(depth < 15 || r_mask == 0 || g_mask == 0 || b_mask == 0)
	{
		fprintf(stderr,
			"There's no Visual compatible with minimal Graphin requirements:\n"
			"At least 15-bit color depth and True- or DirectColor class.\n\n");
		return;
	}

	int t = 1;
	int hw_byte_order = visual->byte_order;
	//if(*(char*)&t == 0) hw_byte_order = MSBFirst;

	// Perceive SYS-format by mask
	switch(depth)
	{
	case 15:
		sys_bpp = 16;
		if(r_mask == 0x7C00 && g_mask == 0x3E0 && b_mask == 0x1F)
		{
			sys_format = agg::pix_format_rgb555;
			byte_order = hw_byte_order;
		}
		break;

	case 16:
		sys_bpp = 16;
		if(r_mask == 0xF800 && g_mask == 0x7E0 && b_mask == 0x1F)
		{
			sys_format = agg::pix_format_rgb565;
			byte_order = hw_byte_order;
		}
		break;

	case 2444:
		sys_bpp = 32;
		if(g_mask == 0xFF00)
		{
			if(r_mask == 0xFF && b_mask == 0xFF0000)
			{
				switch(format)
				{
				case agg::pix_format_argb32:
					sys_format = agg::pix_format_argb32;
					byte_order = LSBFirst;
					break;

				case agg::pix_format_abgr32:
					sys_format = agg::pix_format_abgr32;
					byte_order = MSBFirst;
					break;

				default:
					byte_order = hw_byte_order;
					sys_format = (hw_byte_order == LSBFirst) ? agg::pix_format_argb32 : agg::pix_format_abgr32;
					break;
				}
			}
			if(r_mask == 0xFF0000 && b_mask == 0xFF)
			{
				switch(format)
				{
				case agg::pix_format_argb32:
					sys_format = agg::pix_format_argb32;
					byte_order = MSBFirst;
					break;

				case agg::pix_format_abgr32:
					sys_format = agg::pix_format_abgr32;
					byte_order = LSBFirst;
					break;

				default:
					byte_order = hw_byte_order;
					sys_format = (hw_byte_order == MSBFirst) ? agg::pix_format_argb32 : agg::pix_format_abgr32;
					break;
				}
			}
		}
		break;
	case 24:
	case 32:
		sys_bpp = 32;
		if(g_mask == 0xFF00)
		{
			if(r_mask == 0xFF && b_mask == 0xFF0000)
			{
				switch(format)
				{
				case agg::pix_format_rgba32:
					sys_format = agg::pix_format_rgba32;
					byte_order = LSBFirst;
					break;

				case agg::pix_format_abgr32:
					sys_format = agg::pix_format_abgr32;
					byte_order = MSBFirst;
					break;

				default:
					byte_order = hw_byte_order;
					sys_format = (hw_byte_order == LSBFirst) ? agg::pix_format_rgba32 : agg::pix_format_abgr32;
					break;
				}
			}
			if(r_mask == 0xFF0000 && b_mask == 0xFF)
			{
				switch(format)
				{
				case agg::pix_format_argb32:
					sys_format = agg::pix_format_argb32;
					byte_order = MSBFirst;
					break;

				case agg::pix_format_abgr32:
					sys_format = agg::pix_format_abgr32;
					byte_order = LSBFirst;
					break;

				default:
					byte_order = hw_byte_order;
					sys_format = (hw_byte_order == MSBFirst) ? agg::pix_format_argb32 : agg::pix_format_abgr32;
					break;
				}
			}
		}
		break;
	}

	if(sys_format == agg::pix_format_undefined)
	{
		fprintf(stderr,
			"RGB masks of Visual are not compatible with Graphin pixel formats:\n"
			"R=%08lx, R=%08lx, B=%08lx\n", r_mask, g_mask, b_mask);
		return;
	}
}

void put_image(GdkEventExpose * event, GtkWidget * widget, GdkVisual * visual, agg::pixel_map * pixalmap, agg::pix_format_e format)
{
	if(pixalmap == 0) return;

	int depth = 0;
	int sys_bpp = 0;
	//agg::pix_format_e format = agg::pix_format_rgba32;
	agg::pix_format_e sys_format;
	int byte_order;
	calcDisplayType(visual, depth, sys_bpp, agg::pix_format_undefined, sys_format, byte_order);
	sys_format = agg::pix_format_rgba32;

	if(format == sys_format)
	{
		//ximg->data = (char*)src->buf();
		//ximg->width = src->width(),
		//ximg->height = src->height(),
		//ximg->bytes_per_line = (src->stride());
		gdk_draw_rgb_32_image(widget->window, widget->style->fg_gc[GTK_WIDGET_STATE(widget)], event->area.x, event->area.y, event->area.width, event->area.height, GDK_RGB_DITHER_NORMAL, pixalmap->buf(), pixalmap->stride());
		return;
	}

	int row_len = pixalmap->width() * sys_bpp / 8;
	unsigned char* buf_tmp = new unsigned char[row_len * pixalmap->height()];

	agg::rendering_buffer _src;
	_src.attach(pixalmap->buf(), pixalmap->width(), pixalmap->height(), pixalmap->stride());
	agg::rendering_buffer * src = &_src;

	agg::rendering_buffer rbuf_tmp;
	rbuf_tmp.attach(buf_tmp, pixalmap->width(), pixalmap->height(), row_len);

	switch(sys_format)
	{
	default: break;
	case agg::pix_format_rgb555:
		switch(format)
		{
		default: break;
		case agg::pix_format_rgb555: color_conv(&rbuf_tmp, src, agg::color_conv_rgb555_to_rgb555()); break;
		case agg::pix_format_rgb565: color_conv(&rbuf_tmp, src, agg::color_conv_rgb565_to_rgb555()); break;
		case agg::pix_format_rgb24:  color_conv(&rbuf_tmp, src, agg::color_conv_rgb24_to_rgb555());  break;
		case agg::pix_format_bgr24:  color_conv(&rbuf_tmp, src, agg::color_conv_bgr24_to_rgb555());  break;
		case agg::pix_format_rgba32: color_conv(&rbuf_tmp, src, agg::color_conv_rgba32_to_rgb555()); break;
		case agg::pix_format_argb32: color_conv(&rbuf_tmp, src, agg::color_conv_argb32_to_rgb555()); break;
		case agg::pix_format_bgra32: color_conv(&rbuf_tmp, src, agg::color_conv_bgra32_to_rgb555()); break;
		case agg::pix_format_abgr32: color_conv(&rbuf_tmp, src, agg::color_conv_abgr32_to_rgb555()); break;
		}
		break;

	case agg::pix_format_rgb565:
		switch(format)
		{
		default: break;
		case agg::pix_format_rgb555: color_conv(&rbuf_tmp, src, agg::color_conv_rgb555_to_rgb565()); break;
		case agg::pix_format_rgb565: color_conv(&rbuf_tmp, src, agg::color_conv_rgb565_to_rgb565()); break;
		case agg::pix_format_rgb24:  color_conv(&rbuf_tmp, src, agg::color_conv_rgb24_to_rgb565());  break;
		case agg::pix_format_bgr24:  color_conv(&rbuf_tmp, src, agg::color_conv_bgr24_to_rgb565());  break;
		case agg::pix_format_rgba32: color_conv(&rbuf_tmp, src, agg::color_conv_rgba32_to_rgb565()); break;
		case agg::pix_format_argb32: color_conv(&rbuf_tmp, src, agg::color_conv_argb32_to_rgb565()); break;
		case agg::pix_format_bgra32: color_conv(&rbuf_tmp, src, agg::color_conv_bgra32_to_rgb565()); break;
		case agg::pix_format_abgr32: color_conv(&rbuf_tmp, src, agg::color_conv_abgr32_to_rgb565()); break;
		}
		break;

	case agg::pix_format_bgr24:
		switch(format)
		{
		default: break;
		case agg::pix_format_rgb555: color_conv(&rbuf_tmp, src, agg::color_conv_rgb555_to_bgr24()); break;
		case agg::pix_format_rgb565: color_conv(&rbuf_tmp, src, agg::color_conv_rgb565_to_bgr24()); break;
		case agg::pix_format_rgb24:  color_conv(&rbuf_tmp, src, agg::color_conv_rgb24_to_bgr24());  break;
		case agg::pix_format_bgr24:  color_conv(&rbuf_tmp, src, agg::color_conv_bgr24_to_bgr24());  break;
		case agg::pix_format_abgr32: color_conv(&rbuf_tmp, src, agg::color_conv_abgr32_to_bgr24()); break;
		case agg::pix_format_rgba32: color_conv(&rbuf_tmp, src, agg::color_conv_rgba32_to_bgr24()); break;
		case agg::pix_format_argb32: color_conv(&rbuf_tmp, src, agg::color_conv_argb32_to_bgr24()); break;
		case agg::pix_format_bgra32: color_conv(&rbuf_tmp, src, agg::color_conv_bgra32_to_bgr24()); break;
		}
		break;

	case agg::pix_format_rgb24:
		switch(format)
		{
		default: break;
		case agg::pix_format_rgb555: color_conv(&rbuf_tmp, src, agg::color_conv_rgb555_to_rgb24()); break;
		case agg::pix_format_rgb565: color_conv(&rbuf_tmp, src, agg::color_conv_rgb565_to_rgb24()); break;
		case agg::pix_format_rgb24:  color_conv(&rbuf_tmp, src, agg::color_conv_rgb24_to_rgb24());  break;
		case agg::pix_format_bgr24:  color_conv(&rbuf_tmp, src, agg::color_conv_bgr24_to_rgb24());  break;
		case agg::pix_format_rgba32: color_conv(&rbuf_tmp, src, agg::color_conv_rgba32_to_rgb24()); break;
		case agg::pix_format_argb32: color_conv(&rbuf_tmp, src, agg::color_conv_argb32_to_rgb24()); break;
		case agg::pix_format_abgr32: color_conv(&rbuf_tmp, src, agg::color_conv_abgr32_to_rgb24()); break;
		case agg::pix_format_bgra32: color_conv(&rbuf_tmp, src, agg::color_conv_bgra32_to_rgb24()); break;
		}
		break;

	case agg::pix_format_rgba32:
		switch(format)
		{
		default: break;
		case agg::pix_format_rgb555: color_conv(&rbuf_tmp, src, agg::color_conv_rgb555_to_rgba32()); break;
		case agg::pix_format_rgb565: color_conv(&rbuf_tmp, src, agg::color_conv_rgb565_to_rgba32()); break;
		case agg::pix_format_rgb24:  color_conv(&rbuf_tmp, src, agg::color_conv_rgb24_to_rgba32());  break;
		case agg::pix_format_bgr24:  color_conv(&rbuf_tmp, src, agg::color_conv_bgr24_to_rgba32());  break;
		case agg::pix_format_rgba32: color_conv(&rbuf_tmp, src, agg::color_conv_rgba32_to_rgba32()); break;
		case agg::pix_format_argb32: color_conv(&rbuf_tmp, src, agg::color_conv_argb32_to_rgba32()); break;
		case agg::pix_format_bgra32: color_conv(&rbuf_tmp, src, agg::color_conv_bgra32_to_rgba32()); break;
		case agg::pix_format_abgr32: color_conv(&rbuf_tmp, src, agg::color_conv_abgr32_to_rgba32()); break;
		}
		break;

	case agg::pix_format_abgr32:
		switch(format)
		{
		default: break;
		case agg::pix_format_rgb555: color_conv(&rbuf_tmp, src, agg::color_conv_rgb555_to_abgr32()); break;
		case agg::pix_format_rgb565: color_conv(&rbuf_tmp, src, agg::color_conv_rgb565_to_abgr32()); break;
		case agg::pix_format_rgb24:  color_conv(&rbuf_tmp, src, agg::color_conv_rgb24_to_abgr32());  break;
		case agg::pix_format_bgr24:  color_conv(&rbuf_tmp, src, agg::color_conv_bgr24_to_abgr32());  break;
		case agg::pix_format_abgr32: color_conv(&rbuf_tmp, src, agg::color_conv_abgr32_to_abgr32()); break;
		case agg::pix_format_rgba32: color_conv(&rbuf_tmp, src, agg::color_conv_rgba32_to_abgr32()); break;
		case agg::pix_format_argb32: color_conv(&rbuf_tmp, src, agg::color_conv_argb32_to_abgr32()); break;
		case agg::pix_format_bgra32: color_conv(&rbuf_tmp, src, agg::color_conv_bgra32_to_abgr32()); break;
		}
		break;

	case agg::pix_format_argb32:
		switch(format)
		{
		default: break;
		case agg::pix_format_rgb555: color_conv(&rbuf_tmp, src, agg::color_conv_rgb555_to_argb32()); break;
		case agg::pix_format_rgb565: color_conv(&rbuf_tmp, src, agg::color_conv_rgb565_to_argb32()); break;
		case agg::pix_format_rgb24:  color_conv(&rbuf_tmp, src, agg::color_conv_rgb24_to_argb32());  break;
		case agg::pix_format_bgr24:  color_conv(&rbuf_tmp, src, agg::color_conv_bgr24_to_argb32());  break;
		case agg::pix_format_rgba32: color_conv(&rbuf_tmp, src, agg::color_conv_rgba32_to_argb32()); break;
		case agg::pix_format_argb32: color_conv(&rbuf_tmp, src, agg::color_conv_argb32_to_argb32()); break;
		case agg::pix_format_abgr32: color_conv(&rbuf_tmp, src, agg::color_conv_abgr32_to_argb32()); break;
		case agg::pix_format_bgra32: color_conv(&rbuf_tmp, src, agg::color_conv_bgra32_to_argb32()); break;
		}
		break;

	case agg::pix_format_bgra32:
		switch(format)
		{
		default: break;
		case agg::pix_format_rgb555: color_conv(&rbuf_tmp, src, agg::color_conv_rgb555_to_bgra32()); break;
		case agg::pix_format_rgb565: color_conv(&rbuf_tmp, src, agg::color_conv_rgb565_to_bgra32()); break;
		case agg::pix_format_rgb24:  color_conv(&rbuf_tmp, src, agg::color_conv_rgb24_to_bgra32());  break;
		case agg::pix_format_bgr24:  color_conv(&rbuf_tmp, src, agg::color_conv_bgr24_to_bgra32());  break;
		case agg::pix_format_rgba32: color_conv(&rbuf_tmp, src, agg::color_conv_rgba32_to_bgra32()); break;
		case agg::pix_format_argb32: color_conv(&rbuf_tmp, src, agg::color_conv_argb32_to_bgra32()); break;
		case agg::pix_format_abgr32: color_conv(&rbuf_tmp, src, agg::color_conv_abgr32_to_bgra32()); break;
		case agg::pix_format_bgra32: color_conv(&rbuf_tmp, src, agg::color_conv_bgra32_to_bgra32()); break;
		}
		break;
	}

	gdk_draw_rgb_32_image(widget->window, widget->style->fg_gc[GTK_WIDGET_STATE(widget)], event->area.x, event->area.y, event->area.width, event->area.height, GDK_RGB_DITHER_NORMAL, (const guchar *)buf_tmp, rbuf_tmp.stride());

	delete [] buf_tmp;
}

namespace agg
{
void pixel_map::draw(GtkWidget * widget, GdkEventExpose * event, int device_x, int device_y, int device_width, int device_height) const
{
    std::cout << "draw 1\n;"
    put_image(event, widget, gtk_widget_get_visual(widget), (pixel_map *)this, agg::pix_format_bgra32);
    std::cout << "draw 2\n;"
}
}
#endif
