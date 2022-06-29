#include "Desktop.hpp"

Desktop::Desktop(const unsigned int width, const unsigned int height) : m_screen_space(width, height),
                                                                        m_background(width, height, gfx::Pixel(0, 0, 0, 255)),
                                                                        m_sdl(m_screen_space, false),
                                                                        m_mouse_image(20, 20, gfx::Pixel(0, 0, 0, 255))
{
    std::cout << "Desktop constructor" << std::endl;
    m_running = true;

    gfx::draw_color = gfx::Pixel(255, 0, 0, 255);
    gfx::fill_rect(m_mouse_image, 0, 0, 10, 10);
    gfx::draw_line(m_mouse_image, 0, 0, 20, 20);

    /*
        gfx::Bitmap *test;
        int ret = gfx::load_bitmap(test, "test.bmp");
        std::cout << test->width() << "x" << test->height() << std::endl;
        m_screen_space.stamp_with(*test, shapes::Point(10, 10));
    */

    MainLoop();
}

Desktop::~Desktop()
{
    std::cout << "Shuting Down Desktop env" << std::endl;

    for (gui::Window *w : m_window_list)
    {
        delete w;
    }
}

// TODO: eventually remove this
// translate SDL events into native events, so SDL can eventually be removed
void Desktop::SDL_EventCheck()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        Event e;
        switch (event.type)
        {
        case SDL_QUIT:
            m_running = false;
            break;
        case SDL_MOUSEMOTION:
            e.type = MOUSE_MOVE;
            e.data.mouse_move_event.x = event.motion.x;
            e.data.mouse_move_event.y = event.motion.y;
            m_events_queue.PushEvent(e);
            break;
        case SDL_MOUSEBUTTONDOWN:
            e.type = MOUSE_BUTTON;
            if ((event.button.button == SDL_BUTTON_LEFT) && (false == m_mouse_state.left_mouse_down))
            {
                e.data.mouse_button_event.left_down = true;
                m_events_queue.PushEvent(e);
            }
            else if ((event.button.button == SDL_BUTTON_RIGHT) && (false == m_mouse_state.right_mouse_down))
            {
                e.data.mouse_button_event.right_down = true;
                m_events_queue.PushEvent(e);
                ;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            e.type = MOUSE_BUTTON;
            if ((event.button.button == SDL_BUTTON_LEFT) && (true == m_mouse_state.left_mouse_down))
            {
                e.data.mouse_button_event.left_down = false;
                m_events_queue.PushEvent(e);
                ;
            }
            else if ((event.button.button == SDL_BUTTON_RIGHT) && (true == m_mouse_state.right_mouse_down))
            {
                e.data.mouse_button_event.left_down = false;
                m_events_queue.PushEvent(e);
                ;
            }
            break;

        default:
            break;
        }
    }
}

void Desktop::MainLoop()
{
    std::cout << "Main Loop Start" << std::endl;
    CreateWindow(400, 150, shapes::Point(255, 255), "Large");
    // CreateWindow(400, 150, shapes::Point(200, 340), "Large");
    CreateWindow(100, 50, shapes::Point(230, 230), "Small");

    while (true == m_running)
    {

        SDL_EventCheck(); // TODO: remove this eventually
        // process through events and set state accordingly
        while (false == m_events_queue.IsEmpty())
        {
            Event e = m_events_queue.PopNextEvent();
            switch (e.type)
            {
            case MOUSE_MOVE:
                m_mouse_state.location.x = e.data.mouse_move_event.x;
                m_mouse_state.location.y = e.data.mouse_move_event.y;

                if (m_mouse_state.left_mouse_down && (m_focused_window->IsMouseOver(m_mouse_state.location)))
                {
                    m_focused_window->SetLocation(m_mouse_state.location - m_mouse_offset_to_focused_window);
                }
                break;
            case MOUSE_BUTTON:
                m_mouse_state.left_mouse_down = e.data.mouse_button_event.left_down;
                m_mouse_state.right_mouse_down = e.data.mouse_button_event.right_down;

                if (m_mouse_state.left_mouse_down)
                {
                    for (int i = m_window_list.size() - 1; i >= 0; i--)
                    {
                        gui::Window *tmp = m_window_list[i];
                        if (tmp->IsMouseOver(m_mouse_state.location))
                        {
                            // this one gets the click, so move it to the top of the list and give it focus
                            m_focused_window = tmp;
                            m_window_list.insert(m_window_list.end(), tmp);
                            m_window_list.erase(m_window_list.begin() + i);
                            m_mouse_offset_to_focused_window = m_mouse_state.location - m_focused_window->Location();
                            break;
                        }
                    }
                }
            default:
                break;
            }
        }

        // calculate the screen and draw it!
        CompositScreen();
    }
    std::cout << "Main Loop End" << std::endl;
}

// this goes through the list of windows and draws them in the order they're found
// only draw if the window is set to show
void Desktop::CompositScreen()
{
    m_screen_space.stamp_with(m_background, shapes::Point(0, 0));

    // draw all windows
    for (gui::Window *w : m_window_list)
    {
        if (false == w->IsHidden())
        {
            w->Canvas()->CopyOut(&m_screen_space, w->Canvas()->RelativeLocation());
            // m_screen_space.stamp_with(*(w->Slate()), shapes::Point(w->Location().x, w->Location().y + gui::TOPBAR_HEIGHT));
            // m_screen_space.stamp_with(*(w->TopBar()), w->Location());
        }
    }

    // draw the mouse cursor
    m_screen_space.stamp_with(m_mouse_image, m_mouse_state.location);

    m_sdl.dump_screen();
}

void Desktop::CreateWindow(const unsigned int w, const unsigned int h, const shapes::Point location, std::string name)
{
    gui::Window *new_window = new gui::Window(w, h, name);
    new_window->SetLocation(location);
    new_window->Show();

    // windows get drawn from back to front. Put the newest window on the
    // end so it will be drawn on top, and mark it as the one that gets focus
    m_window_list.insert(m_window_list.end(), new_window);
    m_focused_window = new_window;
}