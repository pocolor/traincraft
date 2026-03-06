#include "engine/application.h"

#include "engine/tmp.h"

Application::Application() {
    m_Window = std::make_unique<Window>();
    m_Window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
}

void Application::run() {
    m_Running = true;
    while (m_Running) {
        m_Window->onUpdate();
    }
}

void Application::stop() {
    m_Running = false;
}

void Application::onEvent(const Event& event) {
    TMP::log(event.toString());

    if (event.getType() == EventType::WindowClose) {
        m_Running = false;
    }
}
