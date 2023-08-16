#define VK_USE_PLATFORM_WIN32_KHR
#include "main.h"
#define SDL_MAIN_HANDLED

int main(int, char **)
{
    App app;
    if (!app.Init())
        return -1;
    app.Loop();
    app.CleanUp();
    return 0;
}
