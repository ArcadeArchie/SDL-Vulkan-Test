#include "App.h"

void App::Loop()
{
    while (!shouldQuit)
    {
        while (SDL_PollEvent(&currentEvent))
        {
            if (currentEvent.type == SDL_QUIT)
                shouldQuit = true;
        }
    }
}