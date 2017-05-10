//
// Created by julian on 5/10/17.
//

#include <GLFW/glfw3.h>
#include "InstanceCreateInfo.h"

namespace Engine::VulkanSetup {
    InstanceCreateInfo::InstanceCreateInfo(const ApplicationInfo& appInfo) {

        createInfo.enabledLayerCount = (uint32_t) validationLayers.size();
        createInfo.ppEnabledLayerNames = validationLayers.data();

        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo.getVk();

        createInfo.enabledExtensionCount = (uint32_t) requiredExtensions.size();
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();

        createInfo.enabledLayerCount = 0;

        createInfo.sType = sType;
        createInfo.flags = flags;
    }

    const VkInstanceCreateInfo& InstanceCreateInfo::getVk() const {
        return createInfo;
    }

    std::vector<const char *> InstanceCreateInfo::getGlfwRequiredExtensions() {
        unsigned int glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char *> extensions(glfwExtensionCount);
        for (unsigned int i = 0; i < glfwExtensionCount; ++i) {
            extensions[i] = glfwExtensions[i];
        }

        extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

        return extensions;
    }

    const std::vector<const char*>& InstanceCreateInfo::getValidationLayers() const {
        return this->validationLayers;
    }
}

