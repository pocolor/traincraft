#include "engine/window.h"
#include "engine/tmp.h"

#include "engine/event/application_event.h"
#include "engine/event/key_event.h"
#include "engine/event/mouse_event.h"

#include <glad/glad.h>
#include <cassert>

static void glfwErrorCallback(int error_code, const char* description) {
    TMP::logError("GLFW error: code=", error_code, ", description=", description);
}

Window::Window() {
    m_Window = glfwCreateWindow(
        m_Data.width,
        m_Data.height,
        m_Data.title.c_str(),
        nullptr,
        nullptr
    );
    assert(m_Window);

    glfwMakeContextCurrent(m_Window);
    const int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    assert(status);
    setVSync(m_Data.vSync);

    // glfw callbacks
    glfwSetWindowUserPointer(m_Window, &m_Data);
#define DATA WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window)
#define EVENT(event) auto evnt = event;\
    data.eventCallback(evnt)

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        DATA;
        data.width = width;
        data.height = height;
        EVENT(WindowResizeEvent(width, height, data.fullscreen));
    });

    glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
        const DATA;
        if (focused) {
            EVENT(WindowFocusEvent());
        } else {
            EVENT(WindowLostFocusEvent());
        }
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        const DATA;
        EVENT(WindowCloseEvent());
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        const DATA;

        switch (action) {
            case GLFW_PRESS: {
                EVENT(KeyPressedEvent(key));
                break;
            }
            case GLFW_RELEASE: {
                EVENT(KeyReleasedEvent(key));
                break;
            }
            case GLFW_REPEAT: {
                EVENT(KeyRepeatEvent(key));
                break;
            }
        }
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
        const DATA;

        switch (action) {
            case GLFW_PRESS: {
                EVENT(MouseButtonPressedEvent(button));
                break;
            }
            case GLFW_RELEASE: {
                EVENT(MouseButtonReleasedEvent(button));
                break;
            }
        }
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
        const DATA;
        EVENT(MouseScrolledEvent((float) xOffset, (float) yOffset));
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
        const DATA;
        EVENT(MouseMovedEvent((float) xPos, (float) yPos));
    });

#undef DATA
#undef EVENT
}

Window::~Window() {
    glfwDestroyWindow(m_Window);
}

void Window::initGLFW() {
    const int success = glfwInit();
    assert(success);

    glfwSetErrorCallback(glfwErrorCallback);
}

void Window::terminateGLFW() {
    glfwTerminate();
}

void Window::onUpdate() const {
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

void Window::setTitle(const std::string& title) {
    glfwSetWindowTitle(m_Window, title.c_str());
    m_Data.title = title;
}

void Window::setSize(const int width, const int height) const {
    glfwSetWindowSize(m_Window, width, height);
}

void Window::maximize() const {
    glfwMaximizeWindow(m_Window);
}

void Window::setFullscreen(const bool fullscreen) {
    if (fullscreen) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(
            m_Window,
            monitor,
            0, 0,
            mode->width,
            mode->height,
            mode->refreshRate
        );
    } else
        glfwSetWindowSize(m_Window, m_Data.width, m_Data.height);
    m_Data.fullscreen = fullscreen;
}

void Window::setVSync(const bool enabled) {
    glfwSwapInterval(enabled ? 1 : 0);
    m_Data.vSync = enabled;
}

void Window::setEventCallback(const EventCallbackFn &eventCallback) {
    m_Data.eventCallback = eventCallback;
}
