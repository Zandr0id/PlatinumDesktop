#include "libgfx.hpp"
#include "libshapes.hpp"
#include <math.h>
#include <iostream>

//Circles
void gfx::draw_circle(Bitmap &bitmap, unsigned int x0, unsigned int y0, unsigned int r)
{
    shapes::Circle circle = shapes::calculate_circle(x0, y0, r);

    for (int i = 0; i < circle.parimeter.size(); i++)
    {
        int x = circle.parimeter[i].x;
        int y = circle.parimeter[i].y;
        bitmap.set_pixel(gfx::draw_color, x, y);
    }
}

void gfx::fill_circle(Bitmap &bitmap, unsigned int x0, unsigned int y0, unsigned int r)
{
    shapes::Circle circle = shapes::calculate_circle(x0, y0, r);

    for (int i = 0; i < circle.parimeter.size(); i++)
    {
        int x = circle.parimeter[i].x;
        int y = circle.parimeter[i].y;
        draw_line(bitmap, x, y, x0, y);
    }
}

//Lines
void gfx::draw_line(Bitmap &bitmap, unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1)
{
    shapes::Line line = shapes::calculate_line(x0, y0, x1, y1);

    for (int i = 0; i < line.points.size(); i++)
    {
        bitmap.set_pixel(gfx::draw_color, line.points[i].x, line.points[i].y);
    }
}

void gfx::draw_line(Bitmap &bitmap, shapes::Point a, shapes::Point b)
{
    draw_line(bitmap, a.x, a.y, b.x, b.y);
}

void gfx::draw_line(Bitmap &bitmap, shapes::Line line)
{
    draw_line(bitmap, line.a.x, line.a.y, line.b.x, line.b.y);
}

//Rectangles
void gfx::draw_rect(Bitmap &bitmap, unsigned int x, unsigned int y, unsigned int h, unsigned int w)
{
    shapes::Rect rect = shapes::calculate_rect(x, y, w, h);
    draw_line(bitmap, rect.sides.a);
    draw_line(bitmap, rect.sides.b);
    draw_line(bitmap, rect.sides.c);
    draw_line(bitmap, rect.sides.d);
}

void gfx::draw_rect(Bitmap &bitmap, shapes::Point origin, unsigned int h, unsigned int w)
{
    draw_rect(bitmap, origin.x, origin.y, h, w);
}

void gfx::fill_rect(Bitmap &bitmap, unsigned int x, unsigned int y, unsigned int h, unsigned int w)
{
    shapes::Rect rect = shapes::calculate_rect(x, y, w, h);
    for (int i = 0; i < rect.sides.a.points.size(); i++)
    {
        draw_line(bitmap, rect.sides.a.points[i], rect.sides.c.points[i]);
    }
}

void gfx::fill_rect(Bitmap &bitmap, shapes::Point origin, unsigned int h, unsigned int w)
{
    fill_rect(bitmap, origin.x, origin.y, h, w);
}