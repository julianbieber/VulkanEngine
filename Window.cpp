//
// Created by julian on 4/8/17.
//

#include <stdexcept>
#include "Window.h"

Window::Window(const int width, const int height) : width(width), height(height) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindow = glfwCreateWindow(this->width, this->height, "Vulkan window", nullptr, nullptr);
}

Window::~Window() {
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
}

bool Window::shouldClose() {
    return (bool) glfwWindowShouldClose(glfwWindow);
}

void Window::processWindowEvents() {
    glfwPollEvents();
}

void Window::createSurface(VkInstance &instance, VkSurfaceKHR &surface) {
    if (glfwCreateWindowSurface(instance, glfwWindow, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}