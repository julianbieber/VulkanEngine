//
// Created by julian on 5/10/17.
//

#ifndef ENGINE_GRAPHICSQUEUE_H
#define ENGINE_GRAPHICSQUEUE_H

#include <vulkan/vulkan.h>
#include "LogicalDevice.h"

namespace Engine::VulkanSetup {
    class GraphicsQueue {
    public:
        GraphicsQueue(const LogicalDevice& logicalDevice, int graphicsQueueIndex);
        VkQueue getVk() const;

    private:
        VkQueue queue;
    };
}

#endif //ENGINE_GRAPHICSQUEUE_H
