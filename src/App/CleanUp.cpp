#include "App.h"

void App::CleanUp()
{
    delete context;
    SDL_DestroyWindow(window);
    SDL_Quit();
}