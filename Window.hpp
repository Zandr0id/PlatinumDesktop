#ifndef WINDOW_HPP
#define WINDOW_HPP
#include "libgfx.hpp"
#include "EventQueue.hpp"
#include <string>

namespace gui
{
    class Window
    {
    public:
        Window(unsigned int width, unsigned int height, std::string name);
        ~Window();
        void Show();
        void Hide();
        bool IsHidden() { return m_hidden; };
        void SetLocation(shapes::Point new_pos);
        shapes::Rect Bounds() { return m_bounds; };
        shapes::Point Location();
        gfx::Bitmap *Slate();
        std::string Name();
        unsigned int Width() { return m_width; };
        unsigned int Height() { return m_height; };

    private:
        std::string m_name;
        unsigned int m_width;
        unsigned int m_height;
        shapes::Point m_location;
        shapes::Rect m_bounds;
        bool m_hidden;
        gfx::Bitmap m_slate; // the bitmap to draw the window on

        EventQueue m_event_queue;
    };

}
#endif // WINDOW_HPP