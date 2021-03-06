//
// Created by julian on 4/8/17.
//

#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "Graphics.h"

namespace Engine {
    class Window {
    public:
        Window(const int width, const int height); // set up glfw window
        ~Window();

        void createSurface(Graphics &graphics);

        bool shouldClose();

        void processWindowEvents();

    private:
        int height;
        int width;
        GLFWwindow *glfwWindow;
    };
}

#endif //ENGINE_WINDOW_H
