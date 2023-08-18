#include "Engine/VulkanContext.h"
#include <SDL2/SDL.h>
#include <vector>

VulkanContext::VulkanErrors VulkanContext::vulkanErrors = {
    {VK_ERROR_OUT_OF_HOST_MEMORY, "VK_ERROR_OUT_OF_HOST_MEMORY"},
    {VK_ERROR_OUT_OF_DEVICE_MEMORY, "VK_ERROR_OUT_OF_DEVICE_MEMORY"},
    {VK_ERROR_INITIALIZATION_FAILED, "VK_ERROR_INITIALIZATION_FAILED"},
    {VK_ERROR_DEVICE_LOST, "VK_ERROR_DEVICE_LOST"},
    {VK_ERROR_MEMORY_MAP_FAILED, "VK_ERROR_MEMORY_MAP_FAILED"},
    {VK_ERROR_LAYER_NOT_PRESENT, "VK_ERROR_LAYER_NOT_PRESENT"},
    {VK_ERROR_EXTENSION_NOT_PRESENT, "VK_ERROR_EXTENSION_NOT_PRESENT"},
    {VK_ERROR_FEATURE_NOT_PRESENT, "VK_ERROR_FEATURE_NOT_PRESENT"},
    {VK_ERROR_INCOMPATIBLE_DRIVER, "VK_ERROR_INCOMPATIBLE_DRIVER"},
    {VK_ERROR_TOO_MANY_OBJECTS, "VK_ERROR_TOO_MANY_OBJECTS"},
    {VK_ERROR_FORMAT_NOT_SUPPORTED, "VK_ERROR_FORMAT_NOT_SUPPORTED"},
    {VK_ERROR_FRAGMENTED_POOL, "VK_ERROR_FRAGMENTED_POOL"},
    {VK_ERROR_UNKNOWN, "VK_ERROR_UNKNOWN"},
    {VK_ERROR_OUT_OF_POOL_MEMORY, "VK_ERROR_OUT_OF_POOL_MEMORY"},
    {VK_ERROR_INVALID_EXTERNAL_HANDLE, "VK_ERROR_INVALID_EXTERNAL_HANDLE"},
    {VK_ERROR_FRAGMENTATION, "VK_ERROR_FRAGMENTATION"},
    {VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS, "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS"},
    {VK_ERROR_SURFACE_LOST_KHR, "VK_ERROR_SURFACE_LOST_KHR"},
    {VK_ERROR_NATIVE_WINDOW_IN_USE_KHR, "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR"},
    {VK_ERROR_OUT_OF_DATE_KHR, "VK_ERROR_OUT_OF_DATE_KHR"},
    {VK_ERROR_INCOMPATIBLE_DISPLAY_KHR, "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR"},
    {VK_ERROR_VALIDATION_FAILED_EXT, "VK_ERROR_VALIDATION_FAILED_EXT"},
    {VK_ERROR_INVALID_SHADER_NV, "VK_ERROR_INVALID_SHADER_NV"},
    {VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR, "VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR"},
    {VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR, "VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR"},
    {VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR, "VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR"},
    {VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR, "VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR"},
    {VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR, "VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR"},
    {VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR, "VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR"},
    {VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT, "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT"},
    {VK_ERROR_NOT_PERMITTED_KHR, "VK_ERROR_NOT_PERMITTED_KHR"},
    {VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT, "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT"},
    {VK_ERROR_COMPRESSION_EXHAUSTED_EXT, "VK_ERROR_COMPRESSION_EXHAUSTED_EXT"},
    {VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT, "VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT"},
    {VK_ERROR_OUT_OF_POOL_MEMORY_KHR, "VK_ERROR_OUT_OF_POOL_MEMORY_KHR"},
    {VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR, "VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR"},
    {VK_ERROR_FRAGMENTATION_EXT, "VK_ERROR_FRAGMENTATION_EXT"},
    {VK_ERROR_NOT_PERMITTED_EXT, "VK_ERROR_NOT_PERMITTED_EXT"},
    {VK_ERROR_INVALID_DEVICE_ADDRESS_EXT, "VK_ERROR_INVALID_DEVICE_ADDRESS_EXT"},
    {VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR, "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR"},
    {VK_ERROR_PIPELINE_COMPILE_REQUIRED_EXT, "VK_ERROR_PIPELINE_COMPILE_REQUIRED_EXT"}};

bool initInstance(VulkanContext *context, uint32_t instanceExtensionCount, const char **instanceExtensions)
{
    VkApplicationInfo app_info = {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.apiVersion = VK_API_VERSION_1_3;
    app_info.pApplicationName = context->_appName;
    app_info.applicationVersion = VK_MAKE_API_VERSION(1, 0, 0, 0);
    app_info.pEngineName = "test-engine";
    app_info.engineVersion = VK_MAKE_API_VERSION(1, 0, 0, 0);

    VkInstanceCreateInfo instance_info = {};
    instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_info.pApplicationInfo = &app_info;
    instance_info.enabledLayerCount = 0;
    instance_info.ppEnabledLayerNames = NULL;
    instance_info.enabledExtensionCount = instanceExtensionCount;
    instance_info.ppEnabledExtensionNames = instanceExtensions;

    auto res = vkCreateInstance(&instance_info, NULL, &context->Instance);
    if (res != VK_SUCCESS)
    {
        SDL_SetError("Failed to create vulkan instance: %s", VulkanContext::vulkanErrors[res].c_str());
        return false;
    }
    return true;
}
bool selectPhysicalDevice(VulkanContext *context)
{
    unsigned int deviceCount = 0;
    vkEnumeratePhysicalDevices(context->Instance, &deviceCount, 0);
    if (deviceCount == 0)
    {
        SDL_SetError("Failed to find suitable GPU");
        context->HardwareGPU = VK_NULL_HANDLE;
        return false;
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(context->Instance, &deviceCount, devices.data());
    for (auto device : devices)
    {
        VkPhysicalDeviceProperties properties;
        VkPhysicalDeviceFeatures features;
        vkGetPhysicalDeviceProperties(device, &properties);
        vkGetPhysicalDeviceFeatures(device, &features);
        if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && features.geometryShader)
        {
            context->HardwareGPU = device;
            break;
        }
    }
    if (context->HardwareGPU == VK_NULL_HANDLE)
    {
        SDL_SetError("Failed to find suitable GPU");
        return false;
    }
    vkGetPhysicalDeviceProperties(context->HardwareGPU, &context->HwGpuProperties);

    return true;
}
bool createLogicalDevice(VulkanContext *context)
{
    return true;
}

VulkanContext *VulkanContext::Init(const char *appName, uint32_t instanceExtensionsCount, const char **instanceExtensions)
{
    auto *context = new VulkanContext;
    context->_appName = appName;
    if (!initInstance(context, instanceExtensionsCount, instanceExtensions))
        return nullptr;
    if (!selectPhysicalDevice(context))
        return nullptr;
    if (!createLogicalDevice(context))
        return nullptr;

    return context;
}
VulkanContext::~VulkanContext()
{
    vkDestroyInstance(Instance, 0);
}
/*

    unsigned int numQueueFamilies = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physDevice, &numQueueFamilies, 0);
    VkQueueFamilyProperties *queueFamilies = new VkQueueFamilyProperties[numQueueFamilies];
    vkGetPhysicalDeviceQueueFamilyProperties(physDevice, &numQueueFamilies, queueFamilies);

    unsigned int graphicQueueIndex = 0;
    for (uint32_t i = 0; i < numQueueFamilies; i++)
    {
        VkQueueFamilyProperties queueFamily = queueFamilies[i];
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            graphicQueueIndex = i;
            break;
        }
    }
    float priorities[] = {1.0f};
    VkDeviceQueueCreateInfo queueCreateInfo = {VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};
    queueCreateInfo.queueFamilyIndex = graphicQueueIndex;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = priorities;

    VkPhysicalDeviceFeatures enabledFeatures{};
    VkDeviceCreateInfo createDeviceInfo = {VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
    createDeviceInfo.queueCreateInfoCount = 1;
    createDeviceInfo.pQueueCreateInfos = &queueCreateInfo;
    createDeviceInfo.enabledExtensionCount = sdlExtCount;
    createDeviceInfo.ppEnabledExtensionNames = extNames;
    createDeviceInfo.pEnabledFeatures = &enabledFeatures;
    VkDevice logicalDevice;
    if (vkCreateDevice(physDevice, &createDeviceInfo, 0, &logicalDevice))
    {
        SDL_SetError("Failed to create vulkan logical device");
        return false;
    }

    vkGetDeviceQueue(logicalDevice, graphicQueueIndex, 0, nullptr);
*/