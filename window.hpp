#ifndef WINDOW_HPP
#define WINDOW_HPP
#include "libgfx.hpp"
#include "event_queue.hpp"
#include <string>
#include <queue>

namespace gui
{
    class Window
    {
    public:
        Window(unsigned int width, unsigned int height, std::string name);
        ~Window();
        void show();
        void hide();
        void set_location(shapes::Point new_pos);
        shapes::Point location();
        gfx::Bitmap *slate();
        std::string name();
        unsigned int width() { return m_width; };
        unsigned int height() { return m_height; };

    private:
        std::string m_name;
        unsigned int m_width;
        unsigned int m_height;
        shapes::Point m_location;
        bool m_hidden;
        gfx::Bitmap m_slate; // the bitmap to draw the window on

        EventQueue m_event_queue;
    };

}
#endif // WINDOW_HPP