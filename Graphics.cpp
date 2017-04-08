//
// Created by julian on 4/8/17.
//

#include <iostream>
#include "Graphics.h"

Graphics::Graphics(Window& window) : instance(VK_NULL_HANDLE), appInfo(Graphics::createApplicationInfo()), callback(), requiredExtensions(getGlfwRequiredExtensions()) {
    auto createInfo = this->createInstanceCreateInfo();

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    if (!checkRequiredExtensions()) {
        throw std::runtime_error("missing extensions");
    }

    if (!checkValidationLayers()) {
        throw std::runtime_error("missing validation layer");
    }

    auto callbackCreateInfo = createCallbackCreationInfo();
    if (createDebugCallback(instance, &callbackCreateInfo, nullptr, &callback) != VK_SUCCESS) {
        throw std::runtime_error("failed to set up debug callback!");
    }

    window.createSurface(instance, surface);

    this->physicalDevice = pickPhysicalDevice();

    logicalDevice = createLogicalDevice();

    graphicsQueue = createGraphicsQueue();
}

Graphics::~Graphics() {
    destroyDebugCallback(instance, callback, nullptr);
    vkDestroyDevice(logicalDevice, nullptr);
    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);

}

VkApplicationInfo Graphics::createApplicationInfo() {
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    return appInfo;
}

VkInstanceCreateInfo Graphics::createInstanceCreateInfo() {
    VkInstanceCreateInfo createInfo = {};

    createInfo.enabledLayerCount = validationLayers.size();
    createInfo.ppEnabledLayerNames = validationLayers.data();

    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = & this->appInfo;

    createInfo.enabledExtensionCount = requiredExtensions.size();
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();

    createInfo.enabledLayerCount = 0;

    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    return createInfo;
}

std::vector<const char *> Graphics::getGlfwRequiredExtensions() {
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

bool Graphics::checkRequiredExtensions() {
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
    std::cout << "Extensions:" << std::endl;
    for (auto extension :  extensions) {
        std::cout << extension.extensionName << std::endl;
    }
    return true; //TODO
}

bool Graphics::checkValidationLayers() {
    return true; // TODO
}

VkDebugReportCallbackCreateInfoEXT Graphics::createCallbackCreationInfo() {
    VkDebugReportCallbackCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    createInfo.pfnCallback = debugCallback;
    return createInfo;
}

VkResult Graphics::createDebugCallback(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT *pCreateInfo,
                                       const VkAllocationCallbacks *pAllocator, VkDebugReportCallbackEXT *pCallback) {
    auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pCallback);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void Graphics::destroyDebugCallback(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
    if (func != nullptr) {
        func(instance, callback, pAllocator);
    }
}

VkPhysicalDevice Graphics::pickPhysicalDevice() {
    auto devices = getPhysicalDevices();
    for (auto& device : devices) {
        if (isSuitable(device) && getGraphicsQueueIndex(device) >= 0)
            return device;
    }
    throw std::runtime_error("No suitable devices");
}

bool Graphics::isSuitable(const VkPhysicalDevice &device) {
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ;//&&
           //deviceFeatures.geometryShader;
}

std::vector<VkPhysicalDevice> Graphics::getPhysicalDevices() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
    return devices;
}


int Graphics::getGraphicsQueueIndex(const VkPhysicalDevice &device) {
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            return i;
        }
        ++i;
    }

    return -1;

}

VkDeviceQueueCreateInfo Graphics::createDeviceQueueCreateInfo() {
    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = getGraphicsQueueIndex(physicalDevice);
    queueCreateInfo.queueCount = 1;

    queueCreateInfo.pQueuePriorities = &queuePriority;
    return queueCreateInfo;
}

VkPhysicalDeviceFeatures Graphics::getPhysicalDeviceFeatures() {
    VkPhysicalDeviceFeatures deviceFeatures = {};
    return deviceFeatures;
}

VkDevice Graphics::createLogicalDevice() {
    deviceQueueCreateInfo = createDeviceQueueCreateInfo();
    physicalDeviceFeatures = getPhysicalDeviceFeatures();
    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
    createInfo.queueCreateInfoCount = 1;

    createInfo.pEnabledFeatures = &physicalDeviceFeatures;
    createInfo.enabledExtensionCount = 0;

    createInfo.enabledLayerCount = validationLayers.size();
    createInfo.ppEnabledLayerNames = validationLayers.data();

    VkDevice device;

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    return device;
}

VkQueue Graphics::createGraphicsQueue() {
    VkQueue queue;
    vkGetDeviceQueue(logicalDevice, getGraphicsQueueIndex(physicalDevice), 0, &queue);
    return queue;
}



