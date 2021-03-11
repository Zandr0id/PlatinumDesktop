#include "libshapes.hpp"
#include <algorithm>
#include <math.h>

//Complex line calculator for different types of lines
//retursn a line object with a vector containing all points on the line
//always goes from left to right
shapes::Line shapes::calculate_line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1)
{
    Line ret;
    ret.a.x = x0;
    ret.a.y = y0;
    ret.b.x = x1;
    ret.b.y = y1;

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
            Point tmp(x0, y);
            ret.points.push_back(tmp);
            //bitmap.set_pixel(gfx::draw_color, x0, y);
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
            Point tmp(x, y0);
            ret.points.push_back(tmp);
            //bitmap.set_pixel(gfx::draw_color, x, y0);
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
            Point tmp(x, y0);
            ret.points.push_back(tmp);
            //bitmap.set_pixel(gfx::draw_color, x, y0);
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
            Point tmp(x, y);
            ret.points.push_back(tmp);
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
            Point tmp(x, y);
            ret.points.push_back(tmp);
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
    return ret;
}

//Bresenham's Circle algorithm
//Returns a vector of points on the edge of the requested circle
//0 degrees is at the top, and they go around counter-clockwise
shapes::Circle shapes::calculate_circle(unsigned int x0, unsigned int y0, unsigned int r)
{
    Circle ret;
    ret.radius = r;
    ret.center.x = x0;
    ret.center.y = y0;

    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    std::vector<Point> q1;
    std::vector<Point> q2;
    std::vector<Point> q3;
    std::vector<Point> q4;
    std::vector<Point> q5;
    std::vector<Point> q6;
    std::vector<Point> q7;
    std::vector<Point> q8;

    Point tmp(x0 + x, y0 + y);
    q1.push_back(tmp);
    tmp.set(x0 - x, y0 + y);
    q2.push_back(tmp);
    tmp.set(x0 + x, y0 - y);
    q3.push_back(tmp);
    tmp.set(x0 - x, y0 - y);
    q4.push_back(tmp);
    tmp.set(x0 + y, y0 + x);
    q5.push_back(tmp);
    tmp.set(x0 - y, y0 + x);
    q6.push_back(tmp);
    tmp.set(x0 + y, y0 - x);
    q7.push_back(tmp);
    tmp.set(x0 - y, y0 - x);
    q8.push_back(tmp);

    while (y >= x)
    {
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

        tmp.set(x0 + x, y0 + y);
        q1.push_back(tmp);
        tmp.set(x0 - x, y0 + y);
        q2.push_back(tmp);
        tmp.set(x0 + x, y0 - y);
        q3.push_back(tmp);
        tmp.set(x0 - x, y0 - y);
        q4.push_back(tmp);
        tmp.set(x0 + y, y0 + x);
        q5.push_back(tmp);
        tmp.set(x0 - y, y0 + x);
        q6.push_back(tmp);
        tmp.set(x0 + y, y0 - x);
        q7.push_back(tmp);
        tmp.set(x0 - y, y0 - x);
        q8.push_back(tmp);
    }
    //these quadrants were calcualted in reverse, so flip them
    std::reverse(q2.begin(), q2.end());
    std::reverse(q3.begin(), q3.end());
    std::reverse(q5.begin(), q5.end());
    std::reverse(q8.begin(), q8.end());

    //the quadrants were calculated out of order, so concatenate them together in
    //a continuous counter-clockwise direction
    ret.parimeter.insert(ret.parimeter.end(), q4.begin(), q4.end());
    ret.parimeter.insert(ret.parimeter.end(), q8.begin(), q8.end());
    ret.parimeter.insert(ret.parimeter.end(), q6.begin(), q6.end());
    ret.parimeter.insert(ret.parimeter.end(), q2.begin(), q2.end());
    ret.parimeter.insert(ret.parimeter.end(), q1.begin(), q1.end());
    ret.parimeter.insert(ret.parimeter.end(), q5.begin(), q5.end());
    ret.parimeter.insert(ret.parimeter.end(), q7.begin(), q7.end());
    ret.parimeter.insert(ret.parimeter.end(), q3.begin(), q3.end());
    return ret;
}

shapes::Rect shapes::calculate_rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
    shapes::Rect ret;
    shapes::Line tmp;

    //set the corners in a counter clock-wise fasion, starting with top left
    ret.corners.a.set(x, y);
    ret.corners.b.set(x, y + h);
    ret.corners.c.set(x + w, y + h);
    ret.corners.d.set(x + w, y);

    tmp = calculate_line(x, y, x, y + h);                                            //calculate the line
    ret.sides.a = tmp;                                                               //save it as a side
    ret.parimeter.insert(ret.parimeter.end(), tmp.points.begin(), tmp.points.end()); //add it to the parimeter points
    tmp = calculate_line(x, y + h, x + w, y + h);
    ret.sides.b = tmp;
    ret.parimeter.insert(ret.parimeter.end(), tmp.points.begin(), tmp.points.end());
    tmp = calculate_line(x + w, y + h, x + w, y);
    ret.sides.c = tmp;
    ret.parimeter.insert(ret.parimeter.end(), tmp.points.begin(), tmp.points.end());
    tmp = calculate_line(x + w, y, x, y);
    ret.sides.d = tmp;
    ret.parimeter.insert(ret.parimeter.end(), tmp.points.begin(), tmp.points.end());

    return ret;
}