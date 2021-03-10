/*
The purpose of this file is to create an easy way to get pixels drawn to the screen.
It defines an SDL class with the single job of coping all pixels from a bitmap onto the screen.
Keep all SDL functinality in this file, so it can be easily replaced with something else later.
Perhaps a faster use of SDL can be used, but this will work for now.
Author: Zane Youmans
Date: 03/08/2021
*/

#include <SDL2/SDL.h>
#include "gfx_types.hpp"

class SDL_Interface
{
public:
    SDL_Interface(int width, int height, Bitmap &bitmap);
    ~SDL_Interface();
    void update_screen();
    void wait_for_close();

private:
    Bitmap *map; //this is the bitmap that it will read from
    int m_width;
    int m_height;
    // SDL render stuff
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
};

SDL_Interface::SDL_Interface(int width, int height, Bitmap &bitmap)
{
    map = &bitmap;
    m_width = width;
    m_height = height;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

SDL_Interface::~SDL_Interface()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDL_Interface::update_screen()
{
    for (int h = 0; h < m_height; h++)
    {
        for (int w = 0; w < m_width; ++w)
        {
            Pixel tmp(map->pixel_at(w, h));
            //Alpha will already have been delt with by this point
            //Only care about the RGB
            SDL_SetRenderDrawColor(renderer, tmp.red(), tmp.green(), tmp.blue(), 255);
            SDL_RenderDrawPoint(renderer, w, h);
        }
    }
    SDL_RenderPresent(renderer);
}

//wait to hit the red "close" button
void SDL_Interface::wait_for_close()
{
    while (1)
    {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
}
