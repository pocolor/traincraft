#pragma once

#include "event.h"

class WindowCloseEvent : public Event {
public:
    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategory::Application)
};

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(const unsigned int width, const unsigned int height, const bool fullscreen)
        : m_Width(width), m_Height(height), m_Fullscreen(fullscreen) {}


    std::string toString() const override {
        std::stringstream ss;
        ss << "WindowResizeEvent: width=" << m_Width <<
            ", height=" << m_Height << ", fullscreen=" << m_Fullscreen;
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategory::Application)
private:
    const unsigned int m_Width, m_Height;
    const bool m_Fullscreen;
};

class WindowFocusEvent : public Event {
public:
    EVENT_CLASS_TYPE(WindowFocus)
    EVENT_CLASS_CATEGORY(EventCategory::Application)
};

class WindowLostFocusEvent : public Event {
public:
    EVENT_CLASS_TYPE(WindowLostFocus)
    EVENT_CLASS_CATEGORY(EventCategory::Application)
};
