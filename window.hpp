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
        void set_location(shapes::Point new_pos);
        shapes::Point location();
        gfx::Bitmap *slate();

    private:
        unsigned int m_width;
        unsigned int m_height;
        gfx::Bitmap m_slate;
        shapes::Point m_location;
        bool m_hidden;
    };

}
#endif //WINDOW_HPP