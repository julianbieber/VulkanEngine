//
// Created by julian on 5/10/17.
//

#ifndef ENGINE_PHYSICALDEVICE_H
#define ENGINE_PHYSICALDEVICE_H

#include <vulkan/vulkan.h>

namespace Engine::VulkanSetup {
    class PhysicalDevice {
    public:
        PhysicalDevice(const VkPhysicalDevice& device);
        const VkPhysicalDevice& getVk() const;
        bool isDiscrete() const;
        bool supportsGeometryShader() const;
        const VkPhysicalDeviceFeatures& getVkPhysicalDeviceFeatures() const;
    private:
        const VkPhysicalDevice device;

        VkPhysicalDeviceFeatures deviceFeatures;
        VkPhysicalDeviceProperties deviceProperties;
    };
}



#endif //ENGINE_PHYSICALDEVICE_H
