//
// Created by julian on 5/10/17.
//

#include "ApplicationInfo.h"

namespace Engine::VulkanSetup {
    ApplicationInfo::ApplicationInfo() {
        appInfo.sType = sType;
        appInfo.pApplicationName = applicationName.c_str();
        appInfo.applicationVersion = applicationVersion;
        appInfo.pEngineName = engineName.c_str();
        appInfo.engineVersion = engineVersion;
        appInfo.apiVersion = apiVersion;
    }

    const VkApplicationInfo& ApplicationInfo::getVk() const {
        return appInfo;
    }
}