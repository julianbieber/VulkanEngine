//
// Created by julian on 5/10/17.
//

#include "DeviceQueueCreateInfo.h"

namespace Engine::VulkanSetup {
    DeviceQueueCreateInfo::DeviceQueueCreateInfo(const int queueFamilyIndex) : queueFamilyIndex(queueFamilyIndex) {
        queueCreateInfo.sType = sType;
        queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        queueCreateInfo.queueCount = queueCount;
        queueCreateInfo.pQueuePriorities = &queuePriorities;
    }

    const VkDeviceQueueCreateInfo& DeviceQueueCreateInfo::getVk() const {
        return queueCreateInfo;
    }

}