#include "libgfx.hpp"
#include "libshapes.hpp"
#include <math.h>
#include <iostream>

//Circles
void gfx::draw_circle(Bitmap &bitmap, const int x0, const int y0, const unsigned int r)
{
    shapes::Circle circle = shapes::calculate_circle(x0, y0, r);

    for (int i = 0; i < circle.parimeter.size(); i++)
    {
        int x = circle.parimeter[i].x;
        int y = circle.parimeter[i].y;
        bitmap.set_pixel(gfx::draw_color, x, y);
    }
}

void gfx::fill_circle(Bitmap &bitmap, const int x0, const int y0, const unsigned int r)
{
    shapes::Circle circle = shapes::calculate_circle(x0, y0, r);

    for (int i = 0; i < circle.parimeter.size(); i++)
    {
        int x = circle.parimeter[i].x;
        int y = circle.parimeter[i].y;
        draw_line(bitmap, x, y, x0, y);
    }
}

//Ellipses
void gfx::draw_ellipse(Bitmap &bitmap, const int x, const int y, const unsigned int r_w, const unsigned int r_h)
{
    shapes::Ellipse ellipse = shapes::calculate_ellipse(x, y, r_w, r_h);
    for (int i = 0; i < ellipse.parimeter.size(); i++)
    {
        //draw_color.set(0, ((float)i / float(ellipse.parimeter.size())) * 255, 0, 255);
        int x = ellipse.parimeter[i].x;
        int y = ellipse.parimeter[i].y;
        bitmap.set_pixel(gfx::draw_color, x, y);
    }
}

//Arcs
void gfx::draw_arc(Bitmap &bitmap, const int x, const int y, const unsigned int r, const unsigned short theta_1, const unsigned short theta_2)
{
    shapes::Arc arc = shapes::calculate_arc(x, y, r, theta_1, theta_2);
    for (int i = 0; i < arc.parimeter.size(); i++)
    {
        int x = arc.parimeter[i].x;
        int y = arc.parimeter[i].y;
        bitmap.set_pixel(gfx::draw_color, x, y);
    }
}

//Lines
void gfx::draw_line(Bitmap &bitmap, const int x0, const int y0, const int x1, const int y1)
{
    shapes::Line line = shapes::calculate_line(x0, y0, x1, y1);

    for (int i = 0; i < line.points.size(); i++)
    {
        bitmap.set_pixel(gfx::draw_color, line.points[i].x, line.points[i].y);
    }
}

void gfx::draw_line(Bitmap &bitmap, const shapes::Point a, const shapes::Point b)
{
    draw_line(bitmap, a.x, a.y, b.x, b.y);
}

void gfx::draw_line(Bitmap &bitmap, shapes::Line line)
{
    draw_line(bitmap, line.a.x, line.a.y, line.b.x, line.b.y);
}

//Rectangles
void gfx::draw_rect(Bitmap &bitmap, const int x, const int y, const unsigned int h, const unsigned int w)
{
    shapes::Rect rect = shapes::calculate_rect(x, y, w, h);
    draw_line(bitmap, rect.sides.a);
    draw_line(bitmap, rect.sides.b);
    draw_line(bitmap, rect.sides.c);
    draw_line(bitmap, rect.sides.d);
}

void gfx::draw_rect(Bitmap &bitmap, const shapes::Point origin, const unsigned int h, const unsigned int w)
{
    draw_rect(bitmap, origin.x, origin.y, h, w);
}

void gfx::fill_rect(Bitmap &bitmap, const int x, const int y, const unsigned int h, const unsigned int w)
{
    shapes::Rect rect = shapes::calculate_rect(x, y, w, h);
    for (int i = 0; i < rect.sides.a.points.size(); i++)
    {
        draw_line(bitmap, rect.sides.a.points[i], rect.sides.c.points[i]);
    }
}

void gfx::fill_rect(Bitmap &bitmap, const shapes::Point origin, const unsigned int h, const unsigned int w)
{
    fill_rect(bitmap, origin.x, origin.y, h, w);
}
