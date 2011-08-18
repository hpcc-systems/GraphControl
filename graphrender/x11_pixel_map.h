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


