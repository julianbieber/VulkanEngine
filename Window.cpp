//
// Created by julian on 4/8/17.
//

#include <stdexcept>
#include "Window.h"

namespace Engine {
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

    void Window::createSurface(Graphics &graphics) {
        if (glfwCreateWindowSurface(graphics.getInstance(), glfwWindow, nullptr, &graphics.getSurface()) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }
}