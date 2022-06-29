#include "WidgetCanvas.hpp"
#include <stdlib.h>

gui::WidgetCanvas::WidgetCanvas(unsigned int w, unsigned int h, shapes::Point location)
{
    m_width = w;
    m_height = h;
    SetRelativeLocation(location);

    // m_bitmap = new gfx::Bitmap(w, h, gfx::Pixel(20, 20, 20, 255));
    m_bitmap = new gfx::Bitmap(w, h);
    // gfx::draw_color = gfx::Pixel(0, 255, 255, 255);
    // gfx::draw_rect(*m_bitmap, shapes::Point(0, 0), h, w);
    gfx::draw_color = gfx::Pixel(20, 20, 20, 255);
    gfx::fill_rect(*m_bitmap, 0, 0, h, w);
    // m_bitmap->set_pixel(gfx::Pixel(0, 255, 255, 255), 0, 0);
    // m_bitmap->set_pixel(gfx::Pixel(0, 255, 255, 255), 0, 49);
    // m_bitmap->set_pixel(gfx::Pixel(0, 255, 255, 255), 99, 0);
    // m_bitmap->set_pixel(gfx::Pixel(0, 255, 255, 255), 99, 49);
}

gui::WidgetCanvas::~WidgetCanvas()
{
    delete m_bitmap;
}

void gui::WidgetCanvas::Hovered(shapes::Point mouse)
{
    shapes::Point relative_mouse(mouse.x - m_relative_location.x, mouse.y - m_relative_location.y);
    for (Widget *w : m_children)
    {
        // pass the hovered event down
        if (w->Bounds().does_contain_point(relative_mouse, w->RelativeLocation()))
        {
            w->Hovered(relative_mouse);
        }
    }
}

void gui::WidgetCanvas::Clicked(shapes::Point mouse)
{
    shapes::Point relative_mouse(mouse.x - m_relative_location.x, mouse.y - m_relative_location.y);
    for (Widget *w : m_children)
    {
        // pass the hovered event down
        if (w->Bounds().does_contain_point(relative_mouse, w->RelativeLocation()))
        {
            w->Clicked(relative_mouse);
        }
    }
}

ErrorOr<bool> gui::WidgetCanvas::CopyOut(gfx::Bitmap *dest, shapes::Point location)
{
    dest->stamp_with(*m_bitmap, location);
    ErrorOr<bool> ret;
    ret.MakeValue(true);
    return ret;
}