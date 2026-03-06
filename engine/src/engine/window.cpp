#include "engine/window.h"
#include "engine/tmp.h"

#include "engine/event/application_event.h"
#include "engine/event/key_event.h"
#include "engine/event/mouse_event.h"

static void glfwErrorCallback(int error_code, const char* description) {
    TMP::logError("GLFW error: code=", error_code, ", description=", description);
}

Window::Window(const WindowData& data) : m_Data(data) {
    const int success = glfwInit();
    TMP::assert(success, "Failed to initialize glfw.");

    glfwSetErrorCallback(glfwErrorCallback);

    m_Window = glfwCreateWindow(
        m_Data.width,
        m_Data.height,
        m_Data.title.c_str(),
        nullptr,
        nullptr
    );
    TMP::assert(m_Window, "Failed to create window. Title=", m_Data.title);

    glfwMakeContextCurrent(m_Window);
    setVSync(m_Data.vSync);

    // glfw callbacks
    glfwSetWindowUserPointer(m_Window, &m_Data);
#define DATA(name) WindowData& name = *(WindowData*)glfwGetWindowUserPointer(window)
#define EVENT(event) ((WindowData*)glfwGetWindowUserPointer(window))->eventCallback(event)

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        DATA(d);
        d.width = width;
        d.height = height;
        d.eventCallback(WindowResizeEvent(width, height, d.fullscreen));
    });

    glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
        const DATA(d);
        if (focused)
            d.eventCallback(WindowFocusEvent());
        else
            d.eventCallback(WindowLostFocusEvent());
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        EVENT(WindowCloseEvent());
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        const DATA(d);

        switch (action) {
            case GLFW_PRESS:
                d.eventCallback(KeyPressedEvent(key, 0));
                break;
            case GLFW_RELEASE:
                d.eventCallback(KeyReleasedEvent(key));
                break;
            case GLFW_REPEAT:
                d.eventCallback(KeyPressedEvent(key, 1));
                break;
        }
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
        const DATA(d);

        switch (action) {
            case GLFW_PRESS:
                d.eventCallback(MouseButtonPressedEvent(button));
                break;
            case GLFW_RELEASE:
                d.eventCallback(MouseButtonReleasedEvent(button));
                break;
        }
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
        EVENT(MouseScrolledEvent((float) xOffset, (float) yOffset));
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
        EVENT(MouseMovedEvent((float) xPos, (float) yPos));
    });

#undef DATA
#undef EVENT
}

Window::~Window() {
    glfwDestroyWindow(m_Window);
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
