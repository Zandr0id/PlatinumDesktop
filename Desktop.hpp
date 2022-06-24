#ifndef LIB_GUI_HPP
#define LIB_GUI_HPP
#include "EventQueue.hpp"
#include "libgfx.hpp"
#include "SDL_interface.hpp"
#include "Window.hpp"

struct MouseState
{
    shapes::Point location;
    bool left_mouse_down;
    bool right_mouse_down;
};

class Desktop
{
public:
    Desktop(const unsigned int width, const unsigned int height);
    ~Desktop();
    void Activate();
    bool GetRunning() { return m_running; };
    MouseState GetMouseState() { return m_mouse_state; };
    void CreateWindow(const unsigned int w, const unsigned int h, const shapes::Point location, std::string name);

private:
    // desktop event loop
    void MainLoop();
    void SDL_EventCheck();
    bool m_running;

    // gfx definitions
    gfx::Bitmap m_background;
    gfx::Bitmap m_screen_space;
    SDL_Interface m_sdl;
    unsigned int m_width;
    unsigned int m_height;

    // Pointers to all of the windows
    std::vector<gui::Window *> m_window_list;
    gui::Window *m_focused_window;
    void CompositScreen();

    EventQueue m_events_queue;

    // cursor stuff
    MouseState m_mouse_state;
    gfx::Bitmap m_mouse_image;
    shapes::Point m_mouse_offset_to_focused_window;
};

#endif // LIB_GUI_HPP