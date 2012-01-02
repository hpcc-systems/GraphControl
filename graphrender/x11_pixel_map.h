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

#include <X11/Xlib.h>
#include <gtk/gtk.h>

#include <stdlib.h>
#include <memory.h>
#include "agg_basics.h"

namespace agg
{
    enum org_e
    {
        org_mono8   = 8,
        org_color16 = 16,
        org_color24 = 24,
        org_color32 = 32,
        org_color48 = 48,
        org_color64 = 64
    };

class pixel_map
{
protected:
    GdkPixbuf *_data;
    unsigned _width;
    unsigned _height;
    unsigned _bpp;

public:
    pixel_map()
    {
        _width = 0;
        _height = 0;
        _bpp = 0;
        _data = gdk_pixbuf_new(GDK_COLORSPACE_RGB, true, 8, 1, 1);
    }

    ~pixel_map()
    {
        g_object_unref(G_OBJECT(_data));
    }

    bool create(unsigned w, unsigned h, unsigned z)
    {
        g_object_unref(G_OBJECT(_data));
        _data = gdk_pixbuf_new(GDK_COLORSPACE_RGB, true, 8, w, h);
        if(!_data)
            return false;
        _width = w;
        _height = h;
        _bpp = z;
        return true;
    }

    unsigned int width() const { return _width; }
    unsigned int height() const { return _height; }

    guchar * buf() const
    {
        if (_data)
            return gdk_pixbuf_get_pixels(_data);
        return NULL;
    }

    int stride() const { return (_bpp / 8) * _width; }
    unsigned int bpp() const { return _bpp; }

    void draw(GtkWidget * widget, int dest_x, int dest_y) const
    {
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window),
                    NULL,
                    _data,
                    0, 0,
                    dest_x, dest_y,
                    -1, -1,
                    GDK_RGB_DITHER_NONE,
                    0, 0);
    }
};
}


