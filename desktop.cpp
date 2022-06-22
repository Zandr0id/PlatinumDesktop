#include "desktop.hpp"

Desktop::Desktop(const unsigned int width, const unsigned int height) : m_screen_space(width, height),
                                                                        m_background(width, height, gfx::Pixel(0, 0, 0, 255)),
                                                                        m_sdl(m_screen_space, false)
{
    std::cout << "Desktop constructor" << std::endl;
    m_running = true;

    //hook up the event loop thread
    m_event_thread = std::thread(&Desktop::event_loop, this);
    m_draw_thread = std::thread(&Desktop::draw_loop, this);
    m_event_thread.join();
    m_draw_thread.join();
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
    std::cout << "Event Loop" << std::endl;
    SDL_Event event;

    while (true == m_running)
    {
        while (SDL_PollEvent(&event))
        {

            // if (m_window_list[0]->location().x > 500)
            // {
            //     m_window_list[0]->set_location(shapes::Point(0, 0));
            // }
            // m_window_list[0]->set_location(shapes::Point((m_window_list[0]->location().x) + 5, 0));

            switch (event.type)
            {
            case SDL_QUIT:
                m_running = false;
                break;
            case SDL_MOUSEMOTION:
                m_mouse_state.mouseX = event.motion.x;
                m_mouse_state.mouseY = event.motion.y;
                //printf("x:%i y:%i", m_mouse_state.mouseX, m_mouse_state.mouseY);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if ((event.button.button == SDL_BUTTON_LEFT) && (false == m_mouse_state.left_mouse_down))
                {
                    m_mouse_state.left_mouse_down = true;
                    std::cout << "left down" << std::endl;
                }
                else if ((event.button.button == SDL_BUTTON_RIGHT) && (false == m_mouse_state.right_mouse_down))
                {
                    m_mouse_state.right_mouse_down = true;
                    std::cout << "right down" << std::endl;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if ((event.button.button == SDL_BUTTON_LEFT) && (true == m_mouse_state.left_mouse_down))
                {
                    m_mouse_state.left_mouse_down = false;
                    std::cout << "left up" << std::endl;
                }
                else if ((event.button.button == SDL_BUTTON_RIGHT) && (true == m_mouse_state.right_mouse_down))
                {
                    m_mouse_state.right_mouse_down = false;
                    std::cout << "right up" << std::endl;
                }
                break;
            default:
                break;
            }
        }
    }

    std::cout << "Event Loop end" << std::endl;
}

void Desktop::draw_loop()
{
    std::cout << "Draw Loop" << std::endl;
    create_window(400, 150, shapes::Point(255, 255));
    create_window(100, 50, shapes::Point(0, 0));

    shapes::Circle path = shapes::calculate_circle(250, 250, 100);
    gfx::draw_color = gfx::Pixel(255, 0, 255, 255);
    gfx::fill_circle(m_background, 250, 250, 100);

    // int j = 0;
    while (true == m_running)
    {
        // gfx::draw_color.set(255, 0, 0, 255);
        // gfx::draw_circle(m_screen_space, 40, 10, 25);
        // gfx::draw_rect(m_screen_space, shapes::Point(20, 20), 180, 180);

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

        /*
        if (j >= path.parimeter.size())
        {
            j = 0;
        }
        m_window_list[1]->set_location(path.parimeter[j]);
        j += 10;
*/
        m_window_list[1]->set_location(shapes::Point(m_mouse_state.mouseX, m_mouse_state.mouseY));
        composit_screen();
    }
    std::cout << "Draw Loop end" << std::endl;
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