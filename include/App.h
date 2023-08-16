#ifndef APP_H
#define APP_H

/*  Required Standard Headers  */
#include <stdlib.h>
#include <string>
#include <iostream>
#include <map>

/* SDL2 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

/* Vulkan */
#include <vulkan/vulkan.h>

class App
{
private:
    std::map<VkResult, std::string> vulkanErrors;
    SDL_Window *window;
    int windowHeight;
    int windowWidth;
    std::string windowName;
    SDL_Event currentEvent;
    bool shouldQuit;
    VkInstance vkInst;
    VkSurfaceKHR vkSurf;
    uint32_t sdlExtCount;
    const char **extNames;

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