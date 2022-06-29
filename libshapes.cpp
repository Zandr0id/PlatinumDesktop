#include "libshapes.hpp"
#include <algorithm>
#include <math.h>
#include <iostream>

// Complex line calculator for different types of lines
// returns a line object with a vector containing all points on the line
// always goes from left to right
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

    // these cases are optomized for vert/horz lines
    if (dx == 0)
    {
        if (y0 > y1) // force draw from left to right
        {
            int tmp = y0;
            y0 = y1;
            y1 = tmp;
        }
        for (int y = y0; y < y1; y++)
        {
            Point tmp(x0, y);
            ret.points.push_back(tmp);
            // bitmap.set_pixel(gfx::draw_color, x0, y);
        }
    }
    else if (dy == 0)
    {
        if (x0 > x1) // force draw from left to right
        {
            int tmp = x0;
            x0 = x1;
            x1 = tmp;
        }
        for (int x = x0; x < x1; x++)
        {
            Point tmp(x, y0);
            ret.points.push_back(tmp);
            // bitmap.set_pixel(gfx::draw_color, x, y0);
        }
    }
    // this case for slope of 1
    else if (abs_dx == abs_dy)
    {
        if ((x0 > x1)) // force draw from left to right
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
            // bitmap.set_pixel(gfx::draw_color, x, y0);
            y0 += (abs_dy / dy); // becomes 1 or -1
        }
    }
    // This case is for shallow slope
    else if (abs_dx > abs_dy)
    {
        if (x0 > x1) // force draw from left to right
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
    // This case is for steep slope
    else
    {
        if (y0 > y1) // force draw from left to right
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

// Bresenham's Circle algorithm
// Returns a vector of points on the edge of the requested circle
// 0 degrees is at the top, and they go around counter-clockwise
shapes::Circle shapes::calculate_circle(unsigned int x0, unsigned int y0, unsigned int r)
{
    Circle ret;
    ret.radius = --r;
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
    // these quadrants were calcualted in reverse, so flip them
    std::reverse(q2.begin(), q2.end());
    std::reverse(q3.begin(), q3.end());
    std::reverse(q5.begin(), q5.end());
    std::reverse(q8.begin(), q8.end());

    // the quadrants were calculated out of order, so concatenate them together in
    // a continuous counter-clockwise direction
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
    w--;
    h--;

    // set the corners in a ccw fasion, starting with top left
    ret.corners.a.set(x, y);
    ret.corners.b.set(x, y + h);
    ret.corners.c.set(x + w, y + h);
    ret.corners.d.set(x + w, y);

    tmp = calculate_line(x, y, x, y + h);                                            // calculate the line
    ret.sides.a = tmp;                                                               // save it as a side
    ret.parimeter.insert(ret.parimeter.end(), tmp.points.begin(), tmp.points.end()); // add it to the parimeter points
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

// TODO: finish
shapes::Arc shapes::calculate_arc(unsigned int x, unsigned int y, unsigned int r, unsigned short theta_1, unsigned short theta_2)
{
    Arc ret;
    ret.center.x = x;
    ret.center.y = y;
    ret.radius = r;
    ret.theta_1 = theta_1;
    ret.theta_2 = theta_2;

    Circle base = calculate_circle(x, y, r);
    // std::cout << x << " " << y << " " << r << std::endl;

    // standard trig functions assume 0 deg is down, but we want up, so...
    theta_1 += 180;
    theta_2 += 180;

    r += 5; // make sure the line crosses the circle

    double angle = (theta_1) * (PI / 180.0); // convert to rad
    int opp = sin(angle) * r;                // find the two end points and normalize
    int adj = cos((angle)) * r;
    Line start_angle = calculate_line(x, y, opp + x, adj + y); // find the line
    Point start(x + opp, y + adj);

    int start_index = 0;
    for (int i = 0; i < base.parimeter.size() / 3; i++)
    {
        for (int j = 0; j < start_angle.points.size(); j++)
        {
            // std::cout << "< " << base.parimeter[i].x << "," << base.parimeter[i].y << ">  ---  < " << start_angle.points[j].x << "," << start_angle.points[j].y << ">\n";
            if (base.parimeter[i] == start_angle.points[j])
            {
                start_index = i;
                break;
            }
        }
    }
    // std::cout << start_index << std::endl;

    angle = (theta_2) * (PI / 180.0);
    opp = sin(angle) * r;
    adj = cos(angle) * r;
    Line end_angle = calculate_line(x, y, opp + x, adj + y);
    Point end(x + opp, y + adj);

    ret.parimeter.insert(ret.parimeter.end(), base.parimeter.begin(), base.parimeter.end());
    ret.parimeter.insert(ret.parimeter.end(), start_angle.points.begin(), start_angle.points.end());
    ret.parimeter.insert(ret.parimeter.end(), end_angle.points.begin(), end_angle.points.end());
    // bool in_range = false;
    // for (int i = 0; i < base.parimeter.size(); i++)
    // {
    //     if (base.parimeter[i] == start)
    //     {
    //         std::cout << "true ";
    //         in_range = true;
    //     }
    //     if (true == in_range)
    //     {
    //         //std::cout << "true ";
    //         ret.parimeter.push_back(base.parimeter[i]);
    //     }
    // }
    std::cout << base.parimeter.size() << std::endl;
    return ret;
}

shapes::Ellipse shapes::calculate_ellipse(unsigned int x, unsigned int y, unsigned int r_w, unsigned int r_h)
{
    Ellipse ret;
    ret.center.x = x;
    ret.center.y = y;
    ret.r_h = r_h;
    ret.r_w = r_w;

    std::vector<Point> q1;
    std::vector<Point> q2;
    std::vector<Point> q3;
    std::vector<Point> q4;
    std::vector<Point> q5;
    std::vector<Point> q6;
    std::vector<Point> q7;
    std::vector<Point> q8;

    int error = 0;
    const int twoAsquare = (2 * r_w * r_w);
    const int twoBsquare = (2 * r_h * r_h);
    int dx = (r_h * r_h * (1 - (2 * r_w)));
    int dy = (r_w * r_w);
    int stop_x = twoBsquare * r_w;
    int stop_y = 0;
    int x0 = r_w;
    int y0 = 0;

    while (stop_x >= stop_y)
    {
        // push back 4 quads
        Point tmp(x + x0, y + y0);
        q1.push_back(tmp);
        tmp.set(x - x0, y + y0);
        q3.push_back(tmp);
        tmp.set(x - x0, y - y0);
        q5.push_back(tmp);
        tmp.set(x + x0, y - y0);
        q7.push_back(tmp);

        y0++;
        stop_y += twoAsquare;
        error += dy;
        dy += twoAsquare;
        if ((2 * error) + dx > 0)
        {
            x0--;
            stop_x -= twoBsquare;
            error += dx;
            dx += twoBsquare;
        }
    }

    x0 = 0;
    y0 = r_h;
    dx = r_h * r_h;
    dy = r_w * r_w * (1 - (2 * r_h));
    error = 0;
    stop_x = 0;
    stop_y = twoAsquare * r_h;
    while (stop_x <= stop_y)
    {
        // push back 4 quads
        Point tmp(x + x0, y + y0);
        q2.push_back(tmp);
        tmp.set(x - x0, y + y0);
        q4.push_back(tmp);
        tmp.set(x - x0, y - y0);
        q6.push_back(tmp);
        tmp.set(x + x0, y - y0);
        q8.push_back(tmp);

        x0++;
        stop_x += twoBsquare;
        error += dx;
        dx += twoBsquare;
        if ((2 * error) + dx > 0)
        {
            y0--;
            stop_y -= twoAsquare;
            error += dy;
            dy += twoAsquare;
        }
    }
    // these were calculated cw, so flip to ccw
    std::reverse(q1.begin(), q1.end());
    std::reverse(q4.begin(), q4.end());
    std::reverse(q5.begin(), q5.end());
    std::reverse(q8.begin(), q8.end());

    ret.parimeter.insert(ret.parimeter.end(), q6.begin(), q6.end()); // up up left
    ret.parimeter.insert(ret.parimeter.end(), q5.begin(), q5.end()); // mid up left
    ret.parimeter.insert(ret.parimeter.end(), q3.begin(), q3.end()); // mid low left
    ret.parimeter.insert(ret.parimeter.end(), q4.begin(), q4.end()); // low low left
    ret.parimeter.insert(ret.parimeter.end(), q2.begin(), q2.end()); // low low right
    ret.parimeter.insert(ret.parimeter.end(), q1.begin(), q1.end()); // mid low right
    ret.parimeter.insert(ret.parimeter.end(), q7.begin(), q7.end()); // mid up right
    ret.parimeter.insert(ret.parimeter.end(), q8.begin(), q8.end()); // up up right

    return ret;
}