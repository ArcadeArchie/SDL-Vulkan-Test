#include "App.h"

App::App()
{
    window = NULL;
    shouldQuit = false;
}

bool App::Init()
{
    windowHeight = 600;
    windowWidth = 800;
    windowName = "Vulkan Test";
    if (!InitSDL())
    {
        std::cout << SDL_GetError();
        shouldQuit = true;
        return false;
    }
    if (!InitVulkan())
    {
        std::cout << SDL_GetError();
        shouldQuit = true;
        return false;
    }
    return true;
}

App::~App()
{
}