#ifndef WINDOW_HPP
#define WINDOW_HPP
#include "libgfx.hpp"
#include "EventQueue.hpp"
#include "WidgetCanvas.hpp"
#include <string>

namespace gui
{
    constexpr unsigned int TOPBAR_HEIGHT = 40; // pixels
    constexpr unsigned int EDGE_WIDTH = 1;     // pixel

    class Window
    {
    public:
        Window(unsigned int width, unsigned int height, std::string name);
        ~Window();
        void Show();
        void Hide();
        bool IsHidden() { return m_hidden; };

        // mouse hover checks
        bool IsMouseOver(shapes::Point mouse);
        bool IsMouseOverCanvas(shapes::Point mouse);
        bool IsMouseOverTopBar(shapes::Point mouse);
        void Paint();

        void SetLocation(shapes::Point new_pos);
        // shapes::Rect TotalBounds() { return m_total_bounds; };
        shapes::Rect TotalBounds() { return m_canvas->Bounds(); };
        // shapes::Rect SlateBounds() { return m_slate_bounds; };
        // shapes::Rect TopbarBounds() { return m_topbar_bounds; };
        shapes::Point Location();

        // gfx::Bitmap *TopBar();
        gfx::Bitmap *Slate();
        gui::WidgetCanvas *Canvas() { return m_canvas; };
        std::string Name();
        unsigned int Width() { return m_width; };
        unsigned int Height() { return m_height; };

    private:
        std::string m_name;
        unsigned int m_width;
        unsigned int m_height;
        shapes::Point m_location;
        bool m_hidden;

        gui::WidgetCanvas *m_topbar;
        gui::WidgetCanvas *m_canvas;

        shapes::Rect m_slate_bounds;
        gfx::Bitmap *m_slate; // the bitmap to draw the window on

        EventQueue m_event_queue;
        bool m_dirty; //;this window needs to be repainted
    };

}
#endif // WINDOW_HPP