//
// Created by julian on 5/10/17.
//

#include "GraphicsQueue.h"

namespace Engine::VulkanSetup {
    GraphicsQueue::GraphicsQueue(const LogicalDevice &logicalDevice, int graphicsQueueIndex) {
        vkGetDeviceQueue(logicalDevice.getVk(), (uint32_t) graphicsQueueIndex, 0, &queue);
    }

    VkQueue GraphicsQueue::getVk() const {
        return this->queue;
    }
}