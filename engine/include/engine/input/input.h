#pragma once

#include <GLFW/glfw3.h>

#include <utility>

class Input {
public:
    static bool isKeyPressed(int key);
    static bool isMouseButtonDown(int button);
    static bool isMouseButtonLeftDown();
    static bool isMouseButtonRightDown();
    static std::pair<float, float> getMousePosition();
    static float getMouseX();
    static float getMouseY();

    static void setWindow(GLFWwindow* window) { s_Window = window; }

private:
    static GLFWwindow* s_Window;
};
