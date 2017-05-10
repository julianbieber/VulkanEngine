//
// Created by julian on 4/8/17.
//

#include <iostream>
#include <algorithm>
#include "Graphics.h"
#include "GraphicsQueue.h"

namespace Engine {

    Graphics::Graphics(Window &window) : instance(VK_NULL_HANDLE), callback(), requiredExtensions(getGlfwRequiredExtensions()) {
        auto createInfo = VulkanSetup::InstanceCreateInfo(this->appInfo);

        this->physicalDevice = pickPhysicalDevice();

        auto graphicsQueueIndex = this->getGraphicsQueueIndex(this->physicalDevice);
        auto deviceQueueCreateInfo = VulkanSetup::DeviceQueueCreateInfo(graphicsQueueIndex);

        this->logicalDevice = VulkanSetup::LogicalDevice(deviceQueueCreateInfo, this->physicalDevice, createInfo);

        if (vkCreateInstance(&createInfo.getVk(), nullptr, &instance) != VK_SUCCESS) {
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

        window.createSurface(this);

        auto graphicsQueue = VulkanSetup::GraphicsQueue(logicalDevice, graphicsQueueIndex);
    }

    const VkInstance& Graphics::getInstance() const {
        return instance;
    }

    const VkSurfaceKHR& Graphics::getSurface() const {
        return surface;
    }

    Graphics::~Graphics() {
        destroyDebugCallback(instance, callback, nullptr);
        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);
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
                                           const VkAllocationCallbacks *pAllocator,
                                           VkDebugReportCallbackEXT *pCallback) {
        auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance,
                                                                               "vkCreateDebugReportCallbackEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pCallback);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void Graphics::destroyDebugCallback(VkInstance instance, VkDebugReportCallbackEXT callback,
                                        const VkAllocationCallbacks *pAllocator) {
        auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance,
                                                                                "vkDestroyDebugReportCallbackEXT");
        if (func != nullptr) {
            func(instance, callback, pAllocator);
        }
    }

    VulkanSetup::PhysicalDevice Graphics::pickPhysicalDevice() {
        auto devices = getPhysicalDevices();
        for (auto &device : devices) {
            if (isSuitable(device) && getGraphicsQueueIndex(device) >= 0)
                return device;
        }
        throw std::runtime_error("No suitable devices");
    }

    bool Graphics::isSuitable(const VulkanSetup::PhysicalDevice &device) {
        return true;
    }

    std::vector<VulkanSetup::PhysicalDevice> Graphics::getPhysicalDevices() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        std::vector<VulkanSetup::PhysicalDevice> physicalDevices;
        physicalDevices.reserve(deviceCount);
        std::for_each(devices.begin(), devices.end(), [&physicalDevices](const auto &device) {
            physicalDevices.push_back(VulkanSetup::PhysicalDevice(device));
        });

        return physicalDevices;
    }


    int Graphics::getGraphicsQueueIndex(const VulkanSetup::PhysicalDevice &device) {
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device.getVk(), &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device.getVk(), &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto &queueFamily : queueFamilies) {
            if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                return i;
            }
            ++i;
        }

        return -1;

    }
}


