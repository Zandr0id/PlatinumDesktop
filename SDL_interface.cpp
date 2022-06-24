#include "SDL_interface.hpp"

static GLuint texture;

SDL_Interface::SDL_Interface(gfx::Bitmap &bitmap, bool show_native_cursor)
{
    map = &bitmap;
    //m_width = width;
    //m_height = height;
    map->height(m_height);
    map->width(m_width);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(m_width, m_height, SDL_WINDOW_OPENGL, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_ShowCursor(show_native_cursor);
    gl = SDL_GL_CreateContext(window);
}

SDL_Interface::~SDL_Interface()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDL_Interface::dump_screen()
{
    SDL_Surface *new_surf = SDL_CreateRGBSurfaceFrom(map->m_data, m_width, m_height, 32, m_width * 4, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, new_surf);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}
