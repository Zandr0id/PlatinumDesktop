#include "libshapes_types.hpp"

bool shapes::Rect::does_contain_point(const shapes::Point point)
{
    // see if the given point is inside or on the edges
    return ((corners.a.x <= point.x) && (corners.d.x >= point.x) && (corners.a.y <= point.y) && (corners.b.y >= point.y));
}