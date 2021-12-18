#include "SDL_interface.hpp"

SDL_Interface::SDL_Interface(gfx::Bitmap &bitmap)
{
    map = &bitmap;
    //m_width = width;
    //m_height = height;
    map->height(m_height);
    map->width(m_width);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(m_width, m_height, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    std::cout << "SDL_interface constructed" << std::endl;
}

SDL_Interface::~SDL_Interface()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDL_Interface::dump_screen()
{
    for (int h = 0; h < m_height; h++)
    {
        for (int w = 0; w < m_width; ++w)
        {
            gfx::Pixel tmp(map->pixel_at(w, h));
            //Alpha will already have been delt with by this point
            //Only care about the RGB
            SDL_SetRenderDrawColor(renderer, tmp.red(), tmp.green(), tmp.blue(), 255);
            SDL_RenderDrawPoint(renderer, w, h);
        }
    }
    SDL_RenderPresent(renderer);
}

//wait to hit the red "close" button
// void SDL_Interface::activate()
// {
//     SDL_Event event;
//     bool quit = false;
//     while (false == quit)
//     {
//         SDL_PollEvent(&event);

//         switch (event.type)
//         {
//         case SDL_QUIT:
//             quit = true;
//             break;
//         case SDL_MOUSEMOTION:
//             //std::cout << "X: " << event.motion.x << " Y: " << event.motion.y << std::endl;
//             break;
//         default:
//             break;
//         }
//     }
// }
