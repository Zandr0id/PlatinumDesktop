#include "gfx_lib.hpp"
#include <math.h>
#include <iostream>

///circle drawing
void plot_circle(Bitmap &bitmap, int xc, int yc, int x, int y)
{

    bitmap.set_pixel(gfx::draw_color, xc + x, yc + y);
    bitmap.set_pixel(gfx::draw_color, xc - x, yc + y);
    bitmap.set_pixel(gfx::draw_color, xc + x, yc - y);
    bitmap.set_pixel(gfx::draw_color, xc - x, yc - y);
    bitmap.set_pixel(gfx::draw_color, xc + y, yc + x);
    bitmap.set_pixel(gfx::draw_color, xc - y, yc + x);
    bitmap.set_pixel(gfx::draw_color, xc + y, yc - x);
    bitmap.set_pixel(gfx::draw_color, xc - y, yc - x);
}

void gfx::draw_circle(Bitmap &bitmap, unsigned int x0, unsigned int y0, unsigned int r)
{
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    plot_circle(bitmap, x0, y0, x, y);
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
            d = d + 4 * x + 6;
        plot_circle(bitmap, x0, y0, x, y);
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

        std::cout << x0 << " " << y0 << " " << x1 << " " << y1 << std::endl;
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