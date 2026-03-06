#pragma once

#include "engine/event/event.h"

class KeyEvent : public Event {
public:
    int getKeyCode() const { return m_KeyCode; }

    EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Keyboard)
protected:
    explicit KeyEvent(const int keyCode) : m_KeyCode(keyCode) {}
    const int m_KeyCode;
};

class KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(const int keycode, const int repeatCount)
        : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

    int getRepeatCount() const { return m_RepeatCount; }

    std::string toString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent: keycode=" << m_KeyCode << ", repeatCount" << m_RepeatCount;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
private:
    const int m_RepeatCount;
};

class KeyReleasedEvent : public KeyEvent {
public:
    explicit KeyReleasedEvent(const int keycode) : KeyEvent(keycode) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent: keycode=" << m_KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};
