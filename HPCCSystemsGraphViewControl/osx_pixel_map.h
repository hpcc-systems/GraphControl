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
#ifndef PIXEL_MAP_H_INCLUDED
#define PIXEL_MAP_H_INCLUDED

#ifdef XP_UNIX
#include <X11/Xlib.h>
#include <gtk/gtk.h>
#endif
#include <stdlib.h>
#include <memory.h>
#include "agg_basics.h"

namespace aggXXX
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
     unsigned char* _data;
     unsigned int   _width;
     unsigned int   _height;
     unsigned int   _bpp;

   public:
     pixel_map(): _data(0), _width(0), _height(0), _bpp(0) {}
     ~pixel_map() { delete _data; }

     bool create( unsigned w, unsigned h, unsigned z, unsigned clear_val = 256 )
     {
       size_t sz = w*h*(z/8);
       _data = new unsigned char[ sz ];
       if(!_data)
         return false;
       _width = w;
       _height = h;
       _bpp = z;
       if( clear_val < 256 ) memset( _data, 0, sz );
       return true;
     }

     unsigned int width() const { return _width; }
     unsigned int height() const { return _height; }

     unsigned char* buf() const { return _data; }
              int   stride() const { return (_bpp / 8) * _width; }
     unsigned int   bpp() const { return _bpp; }

     void draw(GtkWidget * widget, GdkEventExpose * event, int device_x, int device_y, int device_width, int device_height) const;

     //void draw(Display* d, Window w, int gc, agg::rect_i* dst, agg::rect_i* src );
     //void blend(Display* d, Window w, int gc, agg::rect_i* dst, agg::rect_i* src );
   };

}

#endif // PIXEL_MAP_H_INCLUDED
