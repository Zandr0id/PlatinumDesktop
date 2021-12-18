#include "window.hpp"

gui::Window::Window(unsigned int width, unsigned int height) : m_width(width), m_height(height), m_bitmap(width, height)
{
}

gui::Window::~Window()
{
}