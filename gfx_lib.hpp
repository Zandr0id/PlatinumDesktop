#ifndef GFX_LIB_HPP_
#define GFX_LIB_HPP_
#include "gfx_types.hpp"

namespace gfx
{
    inline Pixel draw_color(0, 0, 0, 0);
    void draw_line(Bitmap &bitmap, unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1);
    void draw_circle(Bitmap &bitmap, unsigned int x0, unsigned int y0, unsigned int r);
    void fill_circle(Bitmap &bitmap, unsigned int x0, unsigned int y0, unsigned int r);
    void draw_rect(Bitmap &bitmap, unsigned int x, unsigned int y, unsigned int h, unsigned int w);
    void fill_rect(Bitmap &bitmap, unsigned int x, unsigned int y, unsigned int h, unsigned int w);

}

#endif //GFX_LIB_HPP_