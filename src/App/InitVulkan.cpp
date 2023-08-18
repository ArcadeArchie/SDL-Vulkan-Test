#include "App.h"

bool App::InitVulkan()
{

    uint32_t sdlExtCount = 0;
    SDL_Vulkan_GetInstanceExtensions(window, &sdlExtCount, NULL);
    const char **extNames = new const char *[sdlExtCount];
    SDL_Vulkan_GetInstanceExtensions(window, &sdlExtCount, extNames);
    context = VulkanContext::Init(windowName.c_str(), sdlExtCount, extNames);

    return context != nullptr;
}