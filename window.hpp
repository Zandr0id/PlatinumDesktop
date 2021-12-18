#ifndef WINDOW_HPP
#define WINDOW_HPP
#include "libgfx.hpp"

namespace gui
{

    class Window
    {
    public:
        Window(unsigned int width, unsigned int height);
        ~Window();
        void show();
        void hide();
        void position_at(shapes::Point pos);

    private:
        unsigned int m_width;
        unsigned int m_height;
        gfx::Bitmap m_bitmap;
        shapes::Point m_location;
    };

}
#endif //WINDOW_HPP