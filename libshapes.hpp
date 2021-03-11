/*
This library contians functions that provide calculations for shapes and coordinates
Author: Zane Youmans
Date: 03/10/2021
*/

#ifndef LIB_SHAPES_HPP_
#define LIB_SHAPES_HPP_

#include "libshapes_types.hpp"

namespace shapes
{
    Line calculate_line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1);
    Circle calculate_circle(unsigned int x, unsigned int y, unsigned int r);
    Rect calculate_rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
    Triangle calculate_triangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
}

#endif //LIB_SHAPES_HPP_