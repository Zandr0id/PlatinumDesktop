#ifndef LIB_SHAPES_TYPES_HPP_
#define LIB_SHAPES_TYPES_HPP_
#include <vector>

namespace shapes
{
    struct Point
    {
        unsigned int x;
        unsigned int y;
        Point()
        {
            x = 0;
            y = 0;
        }
        Point(unsigned int x0, unsigned int y0)
        {
            x = x0;
            y = y0;
        }
        void set(unsigned int x0, unsigned int y0)
        {
            x = x0;
            y = y0;
        }
        bool operator==(const Point &b)
        {
            if ((x == b.x) && (y == b.y))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    };

    struct Line
    {
        Point a;
        Point b;
        std::vector<Point> points;
        Line()
        {
            a.x = 0;
            a.y = 0;
            b.x = 0;
            b.y = 0;
        }
        Line(Point a0, Point b0)
        {
            a = a0;
            b = b0;
        }
    };

    struct Circle
    {
        Point center;
        unsigned int radius;
        std::vector<Point> parimeter;
    };

    struct Triangle
    {
        std::vector<Point> parimeter;
        struct corners
        {
            Point a;
            Point b;
            Point c;
        } corners;
        struct sides
        {
            Line a;
            Line b;
            Line c;
        } sides;
    };

    struct Rect
    {
        std::vector<Point> parimeter;
        struct corners
        {
            Point a;
            Point b;
            Point c;
            Point d;
        } corners;
        struct sides
        {
            Line a;
            Line b;
            Line c;
            Line d;
        } sides;
    };

    struct Arc
    {
        std::vector<Point> parimeter;
        Point center;
        unsigned int radius;
        unsigned short theta_1;
        unsigned short theta_2;
    };

    struct Ellipse
    {
        std::vector<Point> parimeter;
        Point center;
        unsigned int r_w;
        unsigned int r_h;
    };

    struct Polygon
    {
        std::vector<Line> sides;
        std::vector<Point> parimeter;
    };
}

#endif //LIB_SHAPES_TYPES_HPP_