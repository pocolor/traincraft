#pragma once

#include "engine/event/event.h"

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(const float x, const float y)
        : m_X(x), m_Y(y) {}

    float getX() const { return m_X; }
    float getY() const { return m_Y; }

    std::string toString() const override {
        std::stringstream ss;
        ss << "MouseMovedEvent: x=" << m_X << ", y=" << m_Y;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved);
    EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
private:
    const float m_X, m_Y;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(const float xOffset, const float yOffset)
        : m_XOffset(xOffset), m_YOffset(yOffset) {}

    float getXOffset() const { return m_XOffset; }
    float getYOffset() const { return m_YOffset; }

    std::string toString() const override {
        std::stringstream ss;
        ss << "MouseScrolledEvent: xOffset=" << m_XOffset << ", yOffset=" << m_YOffset;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled);
    EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
private:
    const float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event {
public:
    int getMouseButton() const { return m_Button; }

    EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
protected:
    explicit MouseButtonEvent(const int button)
        : m_Button(button) {}

    const int m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonPressedEvent(const int button)
        : MouseButtonEvent(button) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: button=" << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed);
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonReleasedEvent(const int button)
        : MouseButtonEvent(button) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: button=" << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased);
};