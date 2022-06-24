#ifndef LIB_GUI_HPP
#define LIB_GUI_HPP
#include "events.hpp"
#include "queue"
#include "libgfx.hpp"
#include "SDL_interface.hpp"
#include "thread"
#include "window.hpp"

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
    void activate();
    void add_event(const Event event) { m_events.push(event); };
    bool get_running() { return m_running; };
    MouseState get_mouse_state() { return m_mouse_state; };
    void create_window(const unsigned int w, const unsigned int h, const shapes::Point location, std::string name);

private:
    // desktop event loop
    void main_loop();
    void SDL_event_check();
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
    void composit_screen();

    std::queue<Event> m_events;

    // cursor stuff
    MouseState m_mouse_state;
    gfx::Bitmap m_mouse_image;
};

#endif // LIB_GUI_HPP