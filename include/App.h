#ifndef APP_H
#define APP_H

/*  Required Standard Headers  */
#include <stdlib.h>
#include <string>
#include <iostream>

/* SDL2 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

/* Vulkan */
#include <vulkan/vulkan.h>
#include "Engine/VulkanContext.h"
class App
{
private:
    SDL_Window *window;
    int windowHeight;
    int windowWidth;
    std::string windowName;
    SDL_Event currentEvent;
    bool shouldQuit;
    VulkanContext* context;

    bool InitSDL();
    bool InitVulkan();

public:
    App();
    ~App();
    bool Init();
    void Loop();
    void CleanUp();
};
#endif