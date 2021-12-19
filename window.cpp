#include "window.hpp"
#include "libshapes.hpp"

gui::Window::Window(unsigned int width, unsigned int height) : m_width(width), m_height(height), m_slate(width, height, gfx::Pixel(0, 0, 0, 255))
{
    m_hidden = true;
    gfx::draw_color.set(0, 255, 255, 255);
    gfx::draw_rect(m_slate, 0, 0, m_height, m_width);
}

gui::Window::~Window()
{
}

void gui::Window::set_location(shapes::Point new_pos)
{
    m_location = new_pos;
}

shapes::Point gui::Window::location()
{
    return m_location;
}

gfx::Bitmap *gui::Window::slate()
{
    return &m_slate;
}

void gui::Window::hide()
{
    m_hidden = true;
}

void gui::Window::show()
{
    m_hidden = false;
}