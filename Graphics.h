//
// Created by julian on 4/8/17.
//

#ifndef ENGINE_GRAPHICS_H
#define ENGINE_GRAPHICS_H

#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>
#include <GLFW/glfw3.h>
#include "Window.h"

class Graphics {
public:
    Graphics(Window& window);
    ~Graphics();

private:
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice logicalDevice;
    VkApplicationInfo appInfo;
    VkDebugReportCallbackEXT callback;
    std::vector<const char *> requiredExtensions;

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_LUNARG_standard_validation"
    };

    static VkApplicationInfo createApplicationInfo();
    VkInstanceCreateInfo createInstanceCreateInfo();

    static std::vector<const char *> getGlfwRequiredExtensions();

    bool checkRequiredExtensions();

    bool checkValidationLayers();

    VkDebugReportCallbackCreateInfoEXT createCallbackCreationInfo();

    VkResult createDebugCallback(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
    void destroyDebugCallback(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);

    VkPhysicalDevice pickPhysicalDevice();

    std::vector<VkPhysicalDevice> getPhysicalDevices();

    bool isSuitable(const VkPhysicalDevice& device);

    int getGraphicsQueueIndex(const VkPhysicalDevice &device);

    VkDevice createLogicalDevice();

    float queuePriority = 1.0f;

    VkDeviceQueueCreateInfo deviceQueueCreateInfo;
    VkDeviceQueueCreateInfo createDeviceQueueCreateInfo();

    VkPhysicalDeviceFeatures physicalDeviceFeatures;
    VkPhysicalDeviceFeatures getPhysicalDeviceFeatures();

    VkQueue graphicsQueue;
    VkQueue createGraphicsQueue();

    VkSurfaceKHR surface;

};

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugReportFlagsEXT flags,
        VkDebugReportObjectTypeEXT objType,
        uint64_t obj,
        size_t location,
        int32_t code,
        const char* layerPrefix,
        const char* msg,
        void* userData) {

    std::cerr << "validation layer: " << msg << std::endl;

    return VK_FALSE;
}



#endif //ENGINE_GRAPHICS_H
