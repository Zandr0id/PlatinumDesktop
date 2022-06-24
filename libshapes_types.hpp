#ifndef LIB_SHAPES_TYPES_HPP_
#define LIB_SHAPES_TYPES_HPP_
#include <vector>

namespace shapes
{
    struct Point
    {
        int x;
        int y;
        Point()
        {
            x = 0;
            y = 0;
        }
        Point(int x0, int y0)
        {
            x = x0;
            y = y0;
        }
        void set(int x0, int y0)
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

    struct Shape
    {
        virtual bool does_contain_point(const Point point) = 0;
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
        // virtual bool does_contain_point(Point point);
    };

    struct Circle
    {
        Point center;
        unsigned int radius;
        std::vector<Point> parimeter;
        // virtual bool does_contain_point(Point point);
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
        // virtual bool does_contain_point(Point point);
    };

    struct Rect : public Shape
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
        virtual bool does_contain_point(const Point point);
    };

    struct Arc
    {
        std::vector<Point> parimeter;
        Point center;
        unsigned int radius;
        unsigned short theta_1;
        unsigned short theta_2;
        // virtual bool does_contain_point(Point point);
    };

    struct Ellipse
    {
        std::vector<Point> parimeter;
        Point center;
        unsigned int r_w;
        unsigned int r_h;
        // virtual bool does_contain_point(Point point);
    };

    struct Polygon
    {
        std::vector<Line> sides;
        std::vector<Point> parimeter;
        // virtual bool does_contain_point(Point point);
    };
}

#endif // LIB_SHAPES_TYPES_HPP_