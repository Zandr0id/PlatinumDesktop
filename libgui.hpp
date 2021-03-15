#ifndef LIB_GUI_HPP
#define LIB_GUI_HPP
#include "libgfx.hpp"

class Desktop
{
public:
    unsigned int mouse_x();
    unsigned int mouse_y();

private:
    unsigned int mouse_x;
    unsigned int mouse_y;
    gfx::Bitmap screen_space;
};

#endif //LIB_GUI_HPP