#include "libgfx.hpp"
//#include "SDL_interface.hpp"
#include "desktop.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main()
{

    Desktop d(SCREEN_WIDTH, SCREEN_HEIGHT);
    std::cout << "Main Thread" << std::endl;

    return 0;
}