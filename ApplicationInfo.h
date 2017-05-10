//
// Created by julian on 5/10/17.
//

#ifndef ENGINE_APPLICATIONINFO_H
#define ENGINE_APPLICATIONINFO_H

#include <vulkan/vulkan.h>
#include <string>

namespace Engine::VulkanSetup {

    class ApplicationInfo {
    public:
        ApplicationInfo();
        const VkApplicationInfo& getVk() const;

    private:
        VkApplicationInfo appInfo = {};
        VkStructureType sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        std::string applicationName = "Hello Triangle";
        uint32_t applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        std::string engineName = "No Engine";
        uint32_t engineVersion = VK_MAKE_VERSION(1, 0, 0);
        uint32_t apiVersion = VK_API_VERSION_1_0;
    };

}


#endif //ENGINE_APPLICATIONINFO_H
