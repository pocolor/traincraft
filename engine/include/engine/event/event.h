#pragma once
#include <string>
#include <functional>

enum class EventType : unsigned char {
    None,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus,
    KeyPressed, KeyReleased,
    MouseButtonPressed, MouseButtonReleased,
    MouseMoved, MouseScrolled,
};

enum class EventCategory : unsigned char {
    None = 0,
    Application = 1 << 0,
    Input = 1 << 1,
    Keyboard = 1 << 2,
    Mouse = 1 << 3,
    MouseButton = 1 << 4,
};

inline bool operator&(const unsigned char lhs, const EventCategory rhs) {
    return lhs & (unsigned char)rhs;
}
inline bool operator&(const EventCategory lhs, const unsigned char rhs) {
    return (unsigned char)lhs & rhs;
}
inline bool operator|(const EventCategory lhs, const EventCategory rhs) {
    return (unsigned char)lhs | (unsigned char)rhs;
}

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; }\
    virtual EventType getType() const override { return getStaticType(); }\
    virtual std::string getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual unsigned char getCategoryFlags() const override { return (unsigned char)(category); }

class Event {
    friend class EventDispatcher;
public:
    virtual ~Event() = default;

    virtual EventType getType() const = 0;
    virtual std::string getName() const = 0;
    virtual unsigned char getCategoryFlags() const = 0;

    virtual std::string toString() const { return getName(); }

    bool isInCategory(const EventCategory category) const { return getCategoryFlags() & category; }
protected:
    bool m_Handled = false;
};

class EventDispatcher {
    template<typename T>
    using EventFn = std::function<bool(T&)>;
public:
    explicit EventDispatcher(Event& event)
        : m_Event(event) {}

    template<typename T>
    bool dispatch(EventFn<T> func) {
        if (m_Event.getType() == T::getStaticType()) {
            m_Event.m_Handled = func(*(T*)&m_Event);
            return true;
        }
        return false;
    }
private:
    const Event& m_Event;
};

using EventCallbackFn = std::function<void(const Event&)>;
