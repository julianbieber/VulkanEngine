//
// Created by julian on 5/10/17.
//

#ifndef ENGINE_DEVICEQUEUECREATEINFO_H
#define ENGINE_DEVICEQUEUECREATEINFO_H

#include <vulkan/vulkan.h>

namespace Engine::VulkanSetup {
    class DeviceQueueCreateInfo {
    public:
        DeviceQueueCreateInfo(const int queueFamilyIndex);
        const VkDeviceQueueCreateInfo& getVk() const;

    private:
        const VkStructureType sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        const uint32_t queueFamilyIndex;
        const uint32_t queueCount = 1;

        const float queuePriorities = 1.0f;

        VkDeviceQueueCreateInfo queueCreateInfo = {};
    };
}




#endif //ENGINE_DEVICEQUEUECREATEINFO_H
