#ifndef GFX_LIB_HPP_
#define GFX_LIB_HPP_
#include "libgfx_types.hpp"
#include "libshapes_types.hpp"
#include "bmp_FileTypes.hpp"

namespace gfx
{
    inline Pixel draw_color(0, 0, 0, 0);
    void draw_line(Bitmap &bitmap, int x0, int y0, int x1, int y1);
    void draw_line(Bitmap &bitmap, shapes::Point a, shapes::Point b);
    void draw_line(Bitmap &bitmap, shapes::Line line);

    void draw_circle(Bitmap &bitmap, int x0, int y0, unsigned int r);
    void fill_circle(Bitmap &bitmap, int x0, int y0, unsigned int r);

    void draw_ellipse(Bitmap &bitmap, int x, int y, unsigned int r_w, unsigned int r_h);

    void draw_arc(Bitmap &bitmap, int x, int y, unsigned int rad, unsigned short theta_1, unsigned short theta_2);

    void draw_rect(Bitmap &bitmap, int x, int y, unsigned int h, unsigned int w);
    void draw_rect(Bitmap &bitmap, shapes::Point origin, unsigned int h, unsigned int w);
    void fill_rect(Bitmap &bitmap, int x, int y, unsigned int h, unsigned int w);
    void fill_rect(Bitmap &bitmap, shapes::Point origin, unsigned int h, unsigned int w);

    int load_bitmap(gfx::Bitmap *dest, std::string file);
}

#endif // GFX_LIB_HPP_