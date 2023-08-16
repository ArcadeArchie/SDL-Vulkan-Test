#include "App.h"

bool App::InitSDL()
{
    if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
        return false;
    window = SDL_CreateWindow(
        windowName.c_str(), 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        windowWidth, 
        windowHeight, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
    return NULL != window;
}