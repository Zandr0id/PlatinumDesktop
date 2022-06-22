/*
The purpose of this file is to create an easy way to get pixels drawn to the screen.
It defines an SDL class with the single job of coping all pixels from a bitmap onto the screen.
Keep all SDL functinality in this file, so it can be easily replaced with something else later.
Perhaps a faster use of SDL can be used, but this will work for now.
Author: Zane Youmans
Date: 03/08/2021
*/
#pragma once

#include <SDL2/SDL.h>
#include "libgfx.hpp"
#include <iostream>
#include <thread>

class SDL_Interface
{
public:
    SDL_Interface(gfx::Bitmap &bitmap, bool show_native_cursor);
    ~SDL_Interface();
    void dump_screen();
    //void activate();

private:
    gfx::Bitmap *map; //this is the bitmap that it will read from
    unsigned int m_width;
    unsigned int m_height;
    // SDL render stuff
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
};
