#include "Window.hpp"
#include "libshapes.hpp"

gui::Window::Window(unsigned int width, unsigned int height, std::string name) : m_name(name)
{
    m_hidden = true;
    m_width = width + (gui::EDGE_WIDTH * 2);                        // the boarder on both sides
    m_height = height + (gui::EDGE_WIDTH * 3) + gui::TOPBAR_HEIGHT; // 3 dividers and the topbar

    // set up the top bar size and location
    m_topbar = new gui::WidgetCanvas(width, gui::TOPBAR_HEIGHT, shapes::Point(0, 0));
    m_topbar->SetRelativeLocation(shapes::Point(m_location.x + (gui::EDGE_WIDTH), m_location.y + gui::EDGE_WIDTH));

    // Set up the main canvas size and location
    m_canvas = new gui::WidgetCanvas(width, height, shapes::Point(0, 0));
    m_canvas->SetRelativeLocation(shapes::Point(m_location.x + (gui::EDGE_WIDTH), m_location.y + (gui::EDGE_WIDTH * 2) + gui::TOPBAR_HEIGHT));

    // set up the bit map that everything will get drawn onto.
    m_slate = new gfx::Bitmap(m_width, m_height, gfx::Pixel(0, 255, 255, 255));
    m_slate_bounds = shapes::calculate_rect(0, 0, m_width, m_height);

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
}

shapes::Point gui::Window::Location()
{
    return m_location;
}

gfx::Bitmap *gui::Window::Slate()
{
    return m_slate;
}

/*
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
    return m_slate_bounds.does_contain_point(mouse, m_location);
}

bool gui::Window::IsMouseOverTopBar(shapes::Point mouse)
{
    return m_topbar->Bounds().does_contain_point(mouse, m_location);
}

bool gui::Window::IsMouseOverCanvas(shapes::Point mouse)
{
    return m_canvas->Bounds().does_contain_point(mouse, m_location);
}

void gui::Window::Paint()
{
    m_canvas->CopyOut(m_slate, m_canvas->RelativeLocation());
    m_topbar->CopyOut(m_slate, m_topbar->RelativeLocation());
}