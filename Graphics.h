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
#include "PhysicalDevice.h"
#include "LogicalDevice.h"

namespace Engine {
    class Graphics {
    public:
        Graphics(Window &window);

        ~Graphics();

        const VkInstance& getInstance() const;
        const VkSurfaceKHR& getSurface() const;

    private:
        VkInstance instance;

        VulkanSetup::PhysicalDevice physicalDevice = nullptr;
        VulkanSetup::LogicalDevice logicalDevice = nullptr;
        VulkanSetup::ApplicationInfo appInfo = VulkanSetup::ApplicationInfo();

        VkDebugReportCallbackEXT callback;
        std::vector<const char *> requiredExtensions;

        static std::vector<const char *> getGlfwRequiredExtensions();

        bool checkRequiredExtensions();

        bool checkValidationLayers();

        VkDebugReportCallbackCreateInfoEXT createCallbackCreationInfo();

        VkResult createDebugCallback(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT *pCreateInfo,
                                     const VkAllocationCallbacks *pAllocator, VkDebugReportCallbackEXT *pCallback);

        void destroyDebugCallback(VkInstance instance, VkDebugReportCallbackEXT callback,
                                  const VkAllocationCallbacks *pAllocator);

        VulkanSetup::PhysicalDevice pickPhysicalDevice();

        std::vector<VulkanSetup::PhysicalDevice> getPhysicalDevices();

        bool isSuitable(const VulkanSetup::PhysicalDevice &device);

        int getGraphicsQueueIndex(const VulkanSetup::PhysicalDevice &device);

        VkQueue createGraphicsQueue();

        VkSurfaceKHR surface;

    };

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugReportFlagsEXT flags,
            VkDebugReportObjectTypeEXT objType,
            uint64_t obj,
            size_t location,
            int32_t code,
            const char *layerPrefix,
            const char *msg,
            void *userData) {

        std::cerr << "validation layer: " << msg << std::endl;

        return VK_FALSE;
    }
}


#endif //ENGINE_GRAPHICS_H
