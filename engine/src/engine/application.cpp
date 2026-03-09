#include "engine/application.h"

#include "engine/input/input.h"
#include "engine/tmp.h"

#define BIND_EVENT_FN(fn) std::bind(&Application::fn, this, std::placeholders::_1)

Application::Application() {
    Window::initGLFW();

    m_Window = std::make_unique<Window>();

    m_Window->setTitle("RailCraft");
    m_Window->setEventCallback(BIND_EVENT_FN(onEvent));

    Input::setWindow(m_Window->getNativeWindow());
}

Application::~Application() {
    m_Window.reset();
    Window::terminateGLFW();
}

void Application::run() {
    m_Running = true;
    while (m_Running) {
        for (const auto& layer : m_LayerStack)
            layer->onUpdate();

        m_Window->onUpdate();
    }
}

void Application::onEvent(Event& event) {
    TMP::log(event.toString());

    EventDispatcher dispatcher(event);
    dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
        (*--it)->onEvent(event);
        if (event.isHandled()) break;
    }
}

bool Application::onWindowClose(WindowCloseEvent& e) {
    stop();
    return true;
}
