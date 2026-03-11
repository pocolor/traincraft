#pragma once

#include "engine/event/event.h"
#include "log/log.h"

#include <GLFW/glfw3.h>
#include <string>
#include <functional>

struct WindowData {
    std::string title;
    unsigned int width;
    unsigned int height;
    bool fullscreen;
    bool vSync;
    EventCallbackFn eventCallback;

    explicit WindowData(
        const std::string& title = "Window",
        const unsigned int width = 640,
        const unsigned int height = 480,
        const bool fullscreen = false,
        const bool vsync = true,
        const EventCallbackFn& eventCallback = nullptr
    ) : title(title), width(width), height(height), fullscreen(fullscreen),
        vSync(vsync), eventCallback(eventCallback) {
        if (!eventCallback)
            this->eventCallback = [&](const Event&) {
                RC_LOG_ERROR("Event callback not set on window {0}", title);
        };
    }
};

class Window {
public:
    Window();
    ~Window();

    void onUpdate() const;

    static void initGLFW();
    static void terminateGLFW();

    void setTitle(const std::string& title);
    void setSize(int width, int height) const;
    void maximize() const;
    void setFullscreen(bool fullscreen);
    void setVSync(bool enabled);
    void setEventCallback(const EventCallbackFn& eventCallback);

    const WindowData& getData() const { return m_Data; }
    GLFWwindow* getNativeWindow() const { return m_Window; }

private:
    WindowData m_Data;
    GLFWwindow* m_Window;
};
