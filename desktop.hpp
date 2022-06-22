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
    unsigned int mouseX;
    unsigned int mouseY;
    bool left_mouse_down;
    bool right_mouse_down;
};

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
    void create_window(const unsigned int w, const unsigned int h, const shapes::Point location);

private:
    //desktop event loop
    void event_loop();
    std::thread m_event_thread;
    bool m_running;

    void draw_loop();
    std::thread m_draw_thread;

    //gfx definitions
    gfx::Bitmap m_background;
    gfx::Bitmap m_screen_space;
    SDL_Interface m_sdl;
    unsigned int m_width;
    unsigned int m_height;

    //Pointers to all of the windows
    std::vector<gui::Window *> m_window_list;

    std::queue<Event> m_events;
    // unsigned int m_mouse_x;
    // unsigned int m_mouse_y;

    void composit_screen();

    MouseState m_mouse_state;
};

#endif //LIB_GUI_HPP