#include "libgfx.hpp"
#include "SDL_interface.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main()
{
    gfx::Bitmap bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Interface sdl(SCREEN_WIDTH, SCREEN_HEIGHT, bitmap);

    // gfx::draw_color.set(255, 0, 0, 255);
    // gfx::draw_line(bitmap, 400, 400, 400, 200);
    // gfx::draw_line(bitmap, 400, 400, 200, 400);
    // gfx::draw_line(bitmap, 400, 400, 400, 600);
    // gfx::draw_line(bitmap, 400, 400, 600, 400);

    gfx::draw_color.set(0, 255, 200, 100);
    gfx::fill_circle(bitmap, 500, 400, 200);
    gfx::draw_color.set(255, 0, 200, 100);
    gfx::fill_circle(bitmap, 400, 400, 200);
    gfx::draw_color.set(0, 255, 100, 255);
    gfx::draw_circle(bitmap, 300, 300, 255);
    gfx::fill_rect(bitmap, 10, 10, 50, 100);
    gfx::draw_color.set(255, 50, 50, 100);
    gfx::fill_rect(bitmap, 30, 30, 50, 100);

    // gfx::draw_color.set(255, 255, 0, 255);
    // gfx::draw_line(bitmap, 400, 400, 600, 600);
    // gfx::draw_line(bitmap, 400, 400, 200, 200);
    // gfx::draw_line(bitmap, 400, 400, 600, 200);
    // gfx::draw_line(bitmap, 400, 400, 200, 600);

    // gfx::draw_color.set(0, 0, 255, 255);
    // gfx::draw_line(bitmap, 400, 400, 200, 300);
    // gfx::draw_line(bitmap, 400, 400, 600, 300);
    // gfx::draw_line(bitmap, 400, 400, 200, 500);
    // gfx::draw_line(bitmap, 400, 400, 600, 500);

    // gfx::draw_color.set(0, 255, 255, 255);
    // gfx::draw_line(bitmap, 400, 400, 300, 200);
    // gfx::draw_line(bitmap, 400, 400, 300, 600);
    // gfx::draw_line(bitmap, 400, 400, 500, 600);
    // gfx::draw_line(bitmap, 400, 400, 500, 200);
    sdl.update_screen();
    sdl.wait_for_close();

    return 0;
}