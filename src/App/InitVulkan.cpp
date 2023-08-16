#include "App.h"
#include <vector>


bool IsDeviceSuitable(VkPhysicalDevice device)
{
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
           deviceFeatures.geometryShader;
}

bool App::InitVulkan()
{
    // create instance
    VkApplicationInfo app_info = {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.apiVersion = VK_API_VERSION_1_3;
    app_info.pApplicationName = windowName.c_str();
    app_info.applicationVersion = VK_MAKE_API_VERSION(1, 0, 0, 0);
    app_info.pEngineName = "test-engine";
    app_info.engineVersion = VK_MAKE_API_VERSION(1, 0, 0, 0);

    VkInstanceCreateInfo instance_info = {};
    instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_info.pApplicationInfo = &app_info;
    instance_info.enabledLayerCount = 0;
    instance_info.ppEnabledLayerNames = NULL;

    SDL_Vulkan_GetInstanceExtensions(window, &sdlExtCount, NULL);
    extNames = (const char **)malloc(sizeof(char *) * sdlExtCount);
    SDL_Vulkan_GetInstanceExtensions(window, &sdlExtCount, extNames);

    instance_info.enabledExtensionCount = sdlExtCount;
    instance_info.ppEnabledExtensionNames = extNames;
    VkResult res = vkCreateInstance(&instance_info, NULL, &vkInst);
    if (res != VK_SUCCESS)
    {
        SDL_SetError("Failed to create vulkan instance: %s", vulkanErrors[res].c_str());
        return false;
    }
    if (SDL_FALSE == SDL_Vulkan_CreateSurface(window, vkInst, &vkSurf))
        return false;

    // enumerate devices

    unsigned int deviceCount = 0;
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(vkInst, &deviceCount, devices.data());
    if (deviceCount == 0)
    {
        SDL_SetError("Failed to enumerate devices");
        return false;
    }
    VkPhysicalDevice physDevice;
    for (const auto &device : devices)
    {
        if (IsDeviceSuitable(device))
        {
            physDevice = device;
            break;
        }
    }
    if (physDevice == VK_NULL_HANDLE)
    {
        SDL_SetError("Failed to find suitable GPU");
        return false;
    }

    return true;
}