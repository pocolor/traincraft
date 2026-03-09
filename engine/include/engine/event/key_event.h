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
    explicit KeyPressedEvent(const int keycode)
        : KeyEvent(keycode) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent: keycode=" << m_KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
};

class KeyRepeatEvent : public KeyEvent {
public:
    KeyRepeatEvent(const int keycode)
        : KeyEvent(keycode) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "KeyRepeatEvent: keycode=" << m_KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
};

class KeyReleasedEvent : public KeyEvent {
public:
    explicit KeyReleasedEvent(const int keycode)
        : KeyEvent(keycode) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent: keycode=" << m_KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};
