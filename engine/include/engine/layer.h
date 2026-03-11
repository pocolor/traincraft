#pragma once
#include "event/event.h"
#include <string>

class Layer {
public:
    explicit Layer(const std::string& name = "Layer") : m_Name(name) {}
    virtual ~Layer() {}

    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void onUpdate() {}
    virtual void onEvent(Event& event) {}

    const std::string& getName() const { return m_Name; }

protected:
    std::string m_Name;
};
