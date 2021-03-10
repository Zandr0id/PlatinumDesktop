#include "gfx_lib.hpp"
#include <math.h>
#include <iostream>

///circle drawing
void gfx::draw_circle(Bitmap &bitmap, unsigned int x0, unsigned int y0, unsigned int r)
{
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    bitmap.set_pixel(gfx::draw_color, x0 + x, y0 + y);
    bitmap.set_pixel(gfx::draw_color, x0 - x, y0 + y);
    bitmap.set_pixel(gfx::draw_color, x0 + x, y0 - y);
    bitmap.set_pixel(gfx::draw_color, x0 - x, y0 - y);
    bitmap.set_pixel(gfx::draw_color, x0 + y, y0 + x);
    bitmap.set_pixel(gfx::draw_color, x0 - y, y0 + x);
    bitmap.set_pixel(gfx::draw_color, x0 + y, y0 - x);
    bitmap.set_pixel(gfx::draw_color, x0 - y, y0 - x);

    while (y >= x)
    {
        // for each pixel we will
        // draw all eight pixels

        x++;

        // check for decision parameter
        // and correspondingly
        // update d, x, y
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }

        bitmap.set_pixel(gfx::draw_color, x0 + x, y0 + y);
        bitmap.set_pixel(gfx::draw_color, x0 - x, y0 + y);
        bitmap.set_pixel(gfx::draw_color, x0 + x, y0 - y);
        bitmap.set_pixel(gfx::draw_color, x0 - x, y0 - y);
        bitmap.set_pixel(gfx::draw_color, x0 + y, y0 + x);
        bitmap.set_pixel(gfx::draw_color, x0 - y, y0 + x);
        bitmap.set_pixel(gfx::draw_color, x0 + y, y0 - x);
        bitmap.set_pixel(gfx::draw_color, x0 - y, y0 - x);
    }
}

void gfx::fill_circle(Bitmap &bitmap, unsigned int x0, unsigned int y0, unsigned int r)
{
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    draw_line(bitmap, x0 + y, y0 + x, x0, y0 + x);
    draw_line(bitmap, x0 - y, y0 + x, x0, y0 + x);
    draw_line(bitmap, x0 + y, y0 - x, x0, y0 - x);
    draw_line(bitmap, x0 - y, y0 - x, x0, y0 - x);
    draw_line(bitmap, x0 + x, y0 + y, x0, y0 + y);
    draw_line(bitmap, x0 - x, y0 + y, x0, y0 + y);
    draw_line(bitmap, x0 + x, y0 - y, x0, y0 - y);
    draw_line(bitmap, x0 - x, y0 - y, x0, y0 - y);

    // bitmap.set_pixel(gfx::draw_color, x0 - x, y0 + y);
    // bitmap.set_pixel(gfx::draw_color, x0 + x, y0 - y);
    // bitmap.set_pixel(gfx::draw_color, x0 - x, y0 - y);
    // bitmap.set_pixel(gfx::draw_color, x0 + y, y0 + x);
    // bitmap.set_pixel(gfx::draw_color, x0 - y, y0 + x);
    // bitmap.set_pixel(gfx::draw_color, x0 + y, y0 - x);
    // bitmap.set_pixel(gfx::draw_color, x0 - y, y0 - x);
    while (y >= x)
    {
        // for each pixel we will
        // draw all eight pixels

        x++;

        // check for decision parameter
        // and correspondingly
        // update d, x, y
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }
        draw_line(bitmap, x0 + y, y0 + x, x0, y0 + x);
        draw_line(bitmap, x0 - y, y0 + x, x0, y0 + x);
        draw_line(bitmap, x0 + y, y0 - x, x0, y0 - x);
        draw_line(bitmap, x0 - y, y0 - x, x0, y0 - x);
        draw_line(bitmap, x0 + x, y0 + y, x0, y0 + y);
        draw_line(bitmap, x0 - x, y0 + y, x0, y0 + y);
        draw_line(bitmap, x0 + x, y0 - y, x0, y0 - y);
        draw_line(bitmap, x0 - x, y0 - y, x0, y0 - y);
    }
}

//line drawing (ugh..)

void gfx::draw_line(Bitmap &bitmap, unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1)
{

    int dy = y1 - y0;
    int dx = x1 - x0;

    int abs_dx = abs(dx);
    int abs_dy = abs(dy);

    //these cases are optomized for vert/horz lines
    if (dx == 0)
    {
        if (y0 > y1) //force draw from left to right
        {
            int tmp = y0;
            y0 = y1;
            y1 = tmp;
        }
        for (int y = y0; y < y1; y++)
        {
            bitmap.set_pixel(gfx::draw_color, x0, y);
        }
    }
    else if (dy == 0)
    {
        if (x0 > x1) //force draw from left to right
        {
            int tmp = x0;
            x0 = x1;
            x1 = tmp;
        }
        for (int x = x0; x < x1; x++)
        {
            bitmap.set_pixel(gfx::draw_color, x, y0);
        }
    }
    //this case for slope of 1
    else if (abs_dx == abs_dy)
    {
        if ((x0 > x1)) //force draw from left to right
        {
            int tmp = y0;
            y0 = y1;
            y1 = tmp;
            dy *= -1;
            tmp = x0;
            x0 = x1;
            x1 = tmp;
        }
        for (int x = x0; x < x1; x++)
        {
            bitmap.set_pixel(gfx::draw_color, x, y0);
            y0 += (abs_dy / dy); //becomes 1 or -1
        }
    }
    //This case is for shallow slope
    else if (abs_dx > abs_dy)
    {
        if (x0 > x1) //force draw from left to right
        {
            int tmp = y0;
            y0 = y1;
            y1 = tmp;
            tmp = x0;
            x0 = x1;
            x1 = tmp;
            dx = x1 - x0;
            dy = y1 - y0;
        }

        int y_step = 1;
        if (dy < 0)
        {
            y_step = -1;
            dy = -dy;
        }
        int D = (2 * dy) - dx;
        int y = y0;
        for (int x = x0; x < x1; x++)
        {
            bitmap.set_pixel(gfx::draw_color, x, y);
            if (D > 0)
            {
                y += y_step;
                D = D + (2 * (dy - dx));
            }
            else
            {
                D = D + (2 * dy);
            }
        }
    }
    //This case is for steep slope
    else
    {
        if (y0 > y1) //force draw from left to right
        {
            int tmp = y0;
            y0 = y1;
            y1 = tmp;
            tmp = x0;
            x0 = x1;
            x1 = tmp;
            dx = x1 - x0;
            dy = y1 - y0;
        }
        int x_step = 1;
        if (dx < 0)
        {
            x_step = -1;
            dx = -dx;
        }
        int D = (2 * dx) - dy;
        int x = x0;
        for (int y = y0; y < y1; y++)
        {
            bitmap.set_pixel(gfx::draw_color, x, y);
            if (D > 0)
            {
                x += x_step;
                D = D + (2 * (dx - dy));
            }
            else
            {
                D = D + (2 * dx);
            }
        }
    }
}

void gfx::draw_rect(Bitmap &bitmap, unsigned int x, unsigned int y, unsigned int h, unsigned int w)
{
    draw_line(bitmap, x, y, x + w, y);
    draw_line(bitmap, x, y, x, y + h);
    draw_line(bitmap, x + w, y, x + w, y + h);
    draw_line(bitmap, x, y + h, x + w, y + h);
}

void gfx::fill_rect(Bitmap &bitmap, unsigned int x, unsigned int y, unsigned int h, unsigned int w)
{
    for (int i = x; i < (x + w); i++)
    {
        draw_line(bitmap, i, y, i, y + h);
    }
}
