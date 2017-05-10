//
// Created by julian on 5/10/17.
//

#include "PhysicalDevice.h"

namespace Engine::VulkanSetup {
    PhysicalDevice::PhysicalDevice(const VkPhysicalDevice& device) : device(device) {
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
    }

    bool PhysicalDevice::isDiscrete() const {
        return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
    }

    bool PhysicalDevice::supportsGeometryShader() const {
        return (bool) deviceFeatures.geometryShader;
    }

    const VkPhysicalDeviceFeatures& PhysicalDevice::getVkPhysicalDeviceFeatures() const {
        return this->deviceFeatures;
    }

    const VkPhysicalDevice& PhysicalDevice::getVk() const {
        return this->device;
    }
}

