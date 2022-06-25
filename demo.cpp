#include "libgfx.hpp"
#include "Desktop.hpp"
#include "ErrorOr.hpp"

constexpr int SCREEN_WIDTH = 1000;
constexpr int SCREEN_HEIGHT = 1000;

ErrorOr<int> RunDesktop()
{
    Desktop d(SCREEN_WIDTH, SCREEN_HEIGHT);

    ErrorOr<int> ret;
    ret.MakeValue(0);
    return ret;
}

int main()
{
    ErrorOr<int> ret = RunDesktop();
    if (ret.IsError())
    {
        return 1;
        std::cout << ret.Error().ToString() << std::endl;
    }
    else
    {
        return 0;
    }
}
