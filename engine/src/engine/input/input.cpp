#include "engine/input/input.h"

#include "engine/input/mouse_codes.h"

GLFWwindow* Input::s_Window;

bool Input::isKeyPressed(const int key) {
    // GLFW_RELEASE is 0
    // GLFW_PRESS is 1
    // GLFW_REPEAT is 2
    return glfwGetKey(s_Window, key);
}

bool Input::isMouseButtonDown(const int button) {
    // GLFW_RELEASE is 0
    // GLFW_PRESS is 1
    return glfwGetMouseButton(s_Window, button);
}

bool Input::isMouseButtonLeftDown() {
    // GLFW_RELEASE is 0
    // GLFW_PRESS is 1
    return glfwGetMouseButton(s_Window, RC_MOUSE_BUTTON_LEFT);
}

bool Input::isMouseButtonRightDown() {
    // GLFW_RELEASE is 0
    // GLFW_PRESS is 1
    return glfwGetMouseButton(s_Window, RC_MOUSE_BUTTON_LEFT);
}

std::pair<float, float> Input::getMousePosition() {
    double x, y;
    glfwGetCursorPos(s_Window, &x, &y);
    return {(float) x, (float) y};
}

float Input::getMouseX() {
    double x, y;
    glfwGetCursorPos(s_Window, &x, &y);
    return (float) x;
}

float Input::getMouseY() {
    double x, y;
    glfwGetCursorPos(s_Window, &x, &y);
    return (float) y;
}
