//
// Created by julian on 5/10/17.
//

#ifndef ENGINE_LOGICALDEVICE_H
#define ENGINE_LOGICALDEVICE_H

#include <vulkan/vulkan.h>
#include "DeviceQueueCreateInfo.h"
#include "PhysicalDevice.h"
#include "ApplicationInfo.h"
#include "InstanceCreateInfo.h"

namespace Engine::VulkanSetup {
    class LogicalDevice {
    public:
        LogicalDevice(const DeviceQueueCreateInfo& queueCreateInfo, const PhysicalDevice& physicalDevice, const InstanceCreateInfo& instanceCreateInfo);

        virtual ~LogicalDevice();

        const VkDevice& getVk() const;

    private:
        VkDevice device;
        VkDeviceCreateInfo createInfo = {};
        VkStructureType sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        uint32_t queueCreateInfoCount = 1;
        uint32_t enabledExtensionCount = 0;
    };
}

#endif //ENGINE_LOGICALDEVICE_H
