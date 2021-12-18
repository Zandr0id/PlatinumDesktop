#ifndef LIB_GUI_HPP
#define LIB_GUI_HPP
#include "events.hpp"
#include "queue"
#include "libgfx.hpp"
#include "SDL_interface.hpp"
#include "thread"
#include "window.hpp"

class Desktop
{
public:
    Desktop(const unsigned int width, const unsigned int height);
    ~Desktop();
    // unsigned int mouse_x();
    // unsigned int mouse_y();
    void activate();
    void add_event(Event event);
    bool get_running() { return m_running; };

private:
    //desktop event loop
    void event_loop();
    std::thread m_event_thread;

    //gfx definitions
    gfx::Bitmap m_screen_space;
    SDL_Interface m_sdl;
    unsigned int m_width;
    unsigned int m_height;

    //Pointers to all of the windows
    std::vector<gui::Window *> m_window_list;

    bool m_running;

    std::queue<Event> m_events;
    // unsigned int m_mouse_x;
    // unsigned int m_mouse_y;
};

#endif //LIB_GUI_HPP