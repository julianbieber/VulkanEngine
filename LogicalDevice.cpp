//
// Created by julian on 5/10/17.
//

#include <stdexcept>
#include "LogicalDevice.h"

namespace Engine::VulkanSetup {
    LogicalDevice::LogicalDevice(const DeviceQueueCreateInfo &queueCreateInfo, const PhysicalDevice &physicalDevice, const InstanceCreateInfo& instanceCreateInfo) {
        createInfo.sType = sType;

        createInfo.pQueueCreateInfos = &queueCreateInfo.getVk();
        createInfo.queueCreateInfoCount = queueCreateInfoCount;

        createInfo.pEnabledFeatures = &physicalDevice.getVkPhysicalDeviceFeatures();
        createInfo.enabledExtensionCount = enabledExtensionCount;
        const auto& validationLayers = instanceCreateInfo.getValidationLayers();
        createInfo.enabledLayerCount = (uint32_t) validationLayers.size();
        createInfo.ppEnabledLayerNames = validationLayers.data();

        if (vkCreateDevice(physicalDevice.getVk(), &createInfo, nullptr, &device) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

    }

    LogicalDevice::~LogicalDevice() {
        vkDestroyDevice(device, nullptr);
    }

    const VkDevice& LogicalDevice::getVk() const {
        return device;
    }
}