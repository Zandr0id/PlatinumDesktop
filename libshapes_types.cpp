#include "libshapes_types.hpp"

bool shapes::Rect::does_contain_point(shapes::Point point, shapes::Point absolute_offset)
{
    // see if the given point is inside or on the edges
    shapes::Point tmp = point - absolute_offset;
    return ((corners.a.x <= tmp.x) && (corners.d.x >= tmp.x) && (corners.a.y <= tmp.y) && (corners.b.y >= tmp.y));
}