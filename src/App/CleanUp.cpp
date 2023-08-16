#include "App.h"

void App::CleanUp()
{
    vkDestroySurfaceKHR(vkInst, vkSurf, NULL);
    vkDestroyInstance(vkInst, NULL);
    free(extNames);
    SDL_DestroyWindow(window);
    SDL_Quit();
}