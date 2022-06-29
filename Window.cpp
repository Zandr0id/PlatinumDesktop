#include "Window.hpp"
#include "libshapes.hpp"

gui::Window::Window(unsigned int width, unsigned int height, std::string name) : m_name(name),
                                                                                 m_width(width),
                                                                                 m_height(height)
// m_slate(width, height, gfx::Pixel(0, 0, 0, 255)),
// m_topbar(width, TOPBAR_HEIGHT, gfx::Pixel(20, 20, 20, 255))
{
    m_hidden = true;
    // m_total_bounds = shapes::calculate_rect(0, 0, width, height + TOPBAR_HEIGHT);
    m_canvas = new gui::WidgetCanvas(m_width, m_height);
    m_canvas->SetRelativeLocation(m_location);
    // m_slate_bounds = shapes::calculate_rect(0, 0, width, height);
    // m_topbar_bounds = shapes::calculate_rect(0, 0, width, TOPBAR_HEIGHT);
    /*
        gfx::draw_color.set(0, 255, 255, 255);
        gfx::draw_rect(m_slate, 0, 0, m_height, m_width);
        gfx::draw_color.set(255, 0, 0, 255);
        gfx::draw_rect(m_topbar, 0, 0, TOPBAR_HEIGHT, m_width);
    */
}

gui::Window::~Window()
{
    delete m_canvas;
}

void gui::Window::SetLocation(shapes::Point new_pos)
{
    m_location = new_pos;
    m_canvas->SetRelativeLocation(new_pos);
}

shapes::Point gui::Window::Location()
{
    return m_location;
}
/*
gfx::Bitmap *gui::Window::Slate()
{
    return &m_slate;
}

gfx::Bitmap *gui::Window::TopBar()
{
    return &m_topbar;
}
*/
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
    // return m_total_bounds.does_contain_point(mouse, m_location);
    return m_canvas->Bounds().does_contain_point(mouse, m_location);
}

/*
bool gui::Window::IsMouseOverTopBar(shapes::Point mouse)
{
    return m_topbar_bounds.does_contain_point(mouse, m_location);
}

bool gui::Window::IsMouseOverSlate(shapes::Point mouse)
{
    return m_slate_bounds.does_contain_point(mouse, m_location);
}
*/