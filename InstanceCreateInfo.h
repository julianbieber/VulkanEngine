//
// Created by julian on 5/10/17.
//

#ifndef ENGINE_INSTANCECREATEINFO_H
#define ENGINE_INSTANCECREATEINFO_H


#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include "ApplicationInfo.h"

namespace Engine::VulkanSetup {
    class InstanceCreateInfo {
    public:
        InstanceCreateInfo(const ApplicationInfo& appInfo);
        const VkInstanceCreateInfo& getVk() const;
        const std::vector<const char*>& getValidationLayers() const;

    private:
        VkInstanceCreateInfo createInfo = {};
        std::vector<const char*> validationLayers = {
                "VK_LAYER_LUNARG_standard_validation"
        };

        std::vector<const char*> requiredExtensions = getGlfwRequiredExtensions();

        VkStructureType sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;

        VkDebugReportFlagBitsEXT flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;

        static std::vector<const char *> getGlfwRequiredExtensions();
    };
}


#endif //ENGINE_INSTANCECREATEINFO_H
