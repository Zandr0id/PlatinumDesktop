#include "libgfx.hpp"
//#include "SDL_interface.hpp"
#include "Desktop.hpp"
#include "ErrorOr.hpp"

constexpr int SCREEN_WIDTH = 1000;
constexpr int SCREEN_HEIGHT = 1000;

ErrorOr<bool> RunDesktop();

int main()
{

    ErrorOr<bool> ret = RunDesktop();

    if (ret.IsError())
    {
        if (ret.HasMessage())
        {
            std::cout << ret.Message() << std::endl;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

ErrorOr<bool> RunDesktop()
{
    Desktop d(SCREEN_WIDTH, SCREEN_HEIGHT);

    ErrorOr<bool> ret(true);
    return ret;
}
