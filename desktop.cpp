#include "desktop.hpp"

Desktop::Desktop(const unsigned int width, const unsigned int height) : m_screen_space(width, height),
                                                                        m_background(width, height, gfx::Pixel(0, 200, 0, 255)),
                                                                        m_sdl(m_screen_space)
{
    std::cout << "Desktop constructor" << std::endl;
    m_running = true;

    //hook up the event loop thread
    m_event_thread = std::thread(&Desktop::event_loop, this);
    m_event_thread.join();
}

Desktop::~Desktop()
{
    std::cout << "Shuting down" << std::endl;

    for (gui::Window *w : m_window_list)
    {
        delete w;
    }
    // delete m_screen_space;
    // delete m_sdl;
}

void Desktop::add_event(Event event)
{
    m_events.push(event);
}

void Desktop::event_loop()
{
    std::cout << "starting loop" << std::endl;
    SDL_Event event;

    create_window(300, 200, shapes::Point(0, 0));
    //create_window(300, 200, shapes::Point(40, 60));

    //m_screen_space.stamp_with(*(m_window_list[0]->slate()), shapes::Point(50, 50));
    // m_screen_space.stamp_with(m_background, shapes::Point(0, 0));
    // gfx::draw_color.set(255, 0, 0, 255);
    // gfx::draw_circle(m_screen_space, 40, 10, 25);
    // gfx::draw_rect(m_screen_space, shapes::Point(20, 20), 180, 180);

    // m_screen_space.stamp_with(smaller, shapes::Point(500, 50));
    // m_screen_space.stamp_with(smaller, shapes::Point(20, 90));

    // gfx::draw_line(m_screen_space, 400, 400, 400, 200);
    // gfx::draw_line(m_screen_space, 400, 400, 200, 400);
    // gfx::draw_line(m_screen_space, 400, 400, 400, 600);
    // gfx::draw_line(m_screen_space, 400, 400, 600, 400);

    // gfx::draw_color.set(255, 0, 0, 255);
    // gfx::draw_line(m_screen_space, 400, 400, 400, 200);
    // gfx::draw_line(m_screen_space, 400, 400, 200, 400);
    // gfx::draw_line(m_screen_space, 400, 400, 400, 600);
    // gfx::draw_line(m_screen_space, 400, 400, 600, 400);

    // gfx::draw_color.set(0, 0, 0, 255);

    // //gfx::draw_arc(bitmap, 500, 400, 20, 90, 140);
    // gfx::draw_color.set(255, 0, 200, 255);
    // gfx::fill_circle(m_screen_space, 600, 600, 100);
    // gfx::draw_color.set(255, 255, 0, 125);
    // gfx::draw_arc(m_screen_space, 300, 300, 200, 0, 45);
    // gfx::fill_rect(m_screen_space, 10, 10, 50, 100);
    // gfx::draw_color.set(0, 0, 255, 125);
    // gfx::fill_rect(m_screen_space, 30, 30, 50, 100);
    // gfx::draw_ellipse(m_screen_space, 400, 400, 100, 200);

    // gfx::draw_color.set(255, 255, 0, 255);
    // gfx::draw_line(m_screen_space, 400, 400, 600, 600);
    // gfx::draw_line(m_screen_space, 400, 400, 200, 200);
    // gfx::draw_line(m_screen_space, 400, 400, 600, 200);
    // gfx::draw_line(m_screen_space, 400, 400, 200, 600);

    // gfx::draw_color.set(0, 0, 255, 255);
    // gfx::draw_line(m_screen_space, 400, 400, 200, 300);
    // gfx::draw_line(m_screen_space, 400, 400, 600, 300);
    // gfx::draw_line(m_screen_space, 400, 400, 200, 500);
    // gfx::draw_line(m_screen_space, 400, 400, 600, 500);

    // gfx::draw_color.set(0, 255, 255, 255);
    // gfx::draw_line(m_screen_space, 400, 400, 300, 200);
    // gfx::draw_line(m_screen_space, 400, 400, 300, 600);
    // gfx::draw_line(m_screen_space, 400, 400, 500, 600);
    // gfx::draw_line(m_screen_space, 400, 400, 500, 200);

    while (true == m_running)
    {
        if (m_window_list[0]->location().x > 500)
        {
            m_window_list[0]->set_location(shapes::Point(0, 0));
        }
        m_window_list[0]->set_location(shapes::Point((m_window_list[0]->location().x) + 5, 0));

        SDL_PollEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            m_running = false;
            break;
        case SDL_MOUSEMOTION:
            break;
        default:
            break;
        }

        composit_screen();
    }
}

void Desktop::composit_screen()
{
    m_screen_space.stamp_with(m_background, shapes::Point(0, 0));

    for (gui::Window *w : m_window_list)
    {
        m_screen_space.stamp_with(*(w->slate()), w->location());
    }

    m_sdl.dump_screen();
}

void Desktop::create_window(const unsigned int w, const unsigned int h, const shapes::Point location)
{
    gui::Window *new_window = new gui::Window(w, h);
    new_window->set_location(location);
    new_window->show();
    m_window_list.push_back(new_window);
}