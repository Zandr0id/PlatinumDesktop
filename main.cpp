#include "gfx_lib.hpp"
#include "SDL_interface.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main()
{

    Bitmap bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Interface sdl(SCREEN_WIDTH, SCREEN_HEIGHT, bitmap);
    //Pixel p(255, 0, 0, 255);
    //Pixel p2(0, 255, 0, 255);
    //Pixel p3(0, 0, 255, 255);

    //bitmap.set_pixel(p, 10, 10);
    //bitmap.set_pixel(p2, 20, 20);
    //bitmap.set_pixel(p3, 30, 30);

    gfx::draw_color.set(255, 0, 0, 0);
    gfx::draw_line(bitmap, 400, 400, 400, 200);
    gfx::draw_line(bitmap, 400, 400, 200, 400);
    gfx::draw_line(bitmap, 400, 400, 400, 600);
    gfx::draw_line(bitmap, 400, 400, 600, 400);

    gfx::draw_color.set(0, 255, 200, 0);
    gfx::fill_circle(bitmap, 500, 400, 200);
    gfx::draw_color.set(255, 0, 200, 0);
    gfx::draw_circle(bitmap, 400, 400, 200);
    gfx::draw_color.set(0, 255, 0, 0);
    gfx::draw_circle(bitmap, 300, 300, 100);
    gfx::fill_rect(bitmap, 10, 10, 50, 100);

    gfx::draw_color.set(255, 255, 0, 0);
    gfx::draw_line(bitmap, 400, 400, 600, 600);
    gfx::draw_line(bitmap, 400, 400, 200, 200);
    gfx::draw_line(bitmap, 400, 400, 600, 200);
    gfx::draw_line(bitmap, 400, 400, 200, 600);

    gfx::draw_color.set(0, 0, 255, 0);
    gfx::draw_line(bitmap, 400, 400, 200, 300);
    gfx::draw_line(bitmap, 400, 400, 600, 300);
    gfx::draw_line(bitmap, 400, 400, 200, 500);
    gfx::draw_line(bitmap, 400, 400, 600, 500);

    gfx::draw_color.set(0, 255, 255, 0);
    gfx::draw_line(bitmap, 400, 400, 300, 200);
    gfx::draw_line(bitmap, 400, 400, 300, 600);
    gfx::draw_line(bitmap, 400, 400, 500, 600);
    gfx::draw_line(bitmap, 400, 400, 500, 200);
    sdl.update_screen();
    sdl.wait_for_close();

    return 0;
}