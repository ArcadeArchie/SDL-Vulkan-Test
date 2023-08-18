#include <vulkan/vulkan.h>
#include <map>
#include <string>


class VulkanQueue
{
public:
    VkQueue Queue;
    unsigned int familyIndex;
};

class VulkanContext
{
private:
public:
    const char *_appName;
    typedef std::map<VkResult, std::string> VulkanErrors;
    static VulkanErrors vulkanErrors;
    VkInstance Instance;
    VkPhysicalDevice HardwareGPU = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties HwGpuProperties;
    VkDevice LogicalGPU;
    VulkanQueue GraphicsQueue;
    ~VulkanContext();
    static VulkanContext *Init(const char *appName, unsigned int instanceExtensionsCount, const char **instanceExtensions);
};
