#include "libgfx.hpp"
//#include "SDL_interface.hpp"
#include "desktop.hpp"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;

int main()
{
    std::cout << "Main Thread" << std::endl;

    Desktop d(SCREEN_WIDTH, SCREEN_HEIGHT);

    std::cout << "Main Thread end" << std::endl;
    return 0;
}