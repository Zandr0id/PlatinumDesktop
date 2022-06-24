#include "Window.hpp"
#include "libshapes.hpp"

gui::Window::Window(unsigned int width, unsigned int height, std::string name) : m_name(name),
                                                                                 m_width(width),
                                                                                 m_height(height),
                                                                                 m_slate(width, height, gfx::Pixel(0, 0, 0, 255))
{
    m_hidden = true;
    m_bounds = shapes::calculate_rect(0, 0, width, height);
    gfx::draw_color.set(0, 255, 255, 255);
    gfx::draw_rect(m_slate, 0, 0, m_height, m_width);
}

gui::Window::~Window()
{
}

void gui::Window::SetLocation(shapes::Point new_pos)
{
    m_location = new_pos;
}

shapes::Point gui::Window::Location()
{
    return m_location;
}

gfx::Bitmap *gui::Window::Slate()
{
    return &m_slate;
}

void gui::Window::Hide()
{
    m_hidden = true;
}

void gui::Window::Show()
{
    m_hidden = false;
}

bool gui::Window::IsMouseOver(shapes::Point mouse)
{
    return m_bounds.does_contain_point(mouse, m_location);
}