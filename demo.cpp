#include "libgfx.hpp"
//#include "SDL_interface.hpp"
#include "desktop.hpp"

constexpr int SCREEN_WIDTH = 500;
constexpr int SCREEN_HEIGHT = 500;

int main()
{
    std::cout << "Program Start" << std::endl;

    Desktop d(SCREEN_WIDTH, SCREEN_HEIGHT);

    std::cout << "Program End" << std::endl;
    return 0;
}