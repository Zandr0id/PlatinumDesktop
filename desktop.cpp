#include "desktop.hpp"

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

    main_loop();
}

Desktop::~Desktop()
{
    std::cout << "Shuting Down Desktop env" << std::endl;

    for (gui::Window *w : m_window_list)
    {
        delete w;
    }
}

//translate SDL events into native events, so SDL can eventually be removed
void Desktop::SDL_event_check()
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
            add_event(e);
            break;
        case SDL_MOUSEBUTTONDOWN:
            e.type = MOUSE_BUTTON;
            if ((event.button.button == SDL_BUTTON_LEFT) && (false == m_mouse_state.left_mouse_down))
            {
                m_mouse_state.left_mouse_down = true;
                add_event(e);
            }
            else if ((event.button.button == SDL_BUTTON_RIGHT) && (false == m_mouse_state.right_mouse_down))
            {
                m_mouse_state.right_mouse_down = true;
                add_event(e);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            e.type = MOUSE_BUTTON;
            if ((event.button.button == SDL_BUTTON_LEFT) && (true == m_mouse_state.left_mouse_down))
            {
                m_mouse_state.left_mouse_down = false;
                add_event(e);
            }
            else if ((event.button.button == SDL_BUTTON_RIGHT) && (true == m_mouse_state.right_mouse_down))
            {
                m_mouse_state.right_mouse_down = false;
                add_event(e);
            }
            break;

        default:
            break;
        }
    }
}

void Desktop::main_loop()
{
    std::cout << "Main Loop Start" << std::endl;
    create_window(400, 150, shapes::Point(255, 255));
    create_window(100, 50, shapes::Point(0, 0));

    shapes::Circle path = shapes::calculate_circle(250, 250, 100);
    gfx::draw_color = gfx::Pixel(255, 0, 255, 255);
    gfx::fill_circle(m_background, 250, 250, 100);

    while (true == m_running)
    {

        SDL_event_check(); //TODO: remove this eventually

        while (false == m_events.empty())
        {
            Event e = m_events.front();
            switch (e.type)
            {
            case MOUSE_MOVE:
                m_mouse_state.location.x = e.data.mouse_move_event.x;
                m_mouse_state.location.y = e.data.mouse_move_event.y;
                break;
            default:
                break;
            }
            m_events.pop();
        }

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

        composit_screen();
    }
    std::cout << "Main Loop End" << std::endl;
}

void Desktop::composit_screen()
{
    m_screen_space.stamp_with(m_background, shapes::Point(0, 0));

    //draw all windows
    for (gui::Window *w : m_window_list)
    {
        m_screen_space.stamp_with(*(w->slate()), w->location());
    }

    //draw the mouse cursor
    m_screen_space.stamp_with(m_mouse_image, m_mouse_state.location);

    m_sdl.dump_screen();
}

void Desktop::create_window(const unsigned int w, const unsigned int h, const shapes::Point location)
{
    gui::Window *new_window = new gui::Window(w, h);
    new_window->set_location(location);
    new_window->show();
    m_window_list.push_back(new_window);
}