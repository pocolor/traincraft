#include "engine/application.h"

#include "engine/input/input.h"
#include "engine/tmp.h"

std::unique_ptr<Window> Application::s_Window;
LayerStack Application::s_LayerStack;
bool Application::s_Running;

void Application::init() {
    Window::initGLFW();

    s_Window = std::make_unique<Window>();

    s_Window->setTitle("RailCraft");
    s_Window->setEventCallback(onEvent);

    Input::setWindow(s_Window->getNativeWindow());
}

void Application::shutdown() {
    s_Window.reset();
    Window::terminateGLFW();
}

void Application::run() {
    s_Running = true;
    while (s_Running) {
        for (const auto& layer : s_LayerStack)
            layer->onUpdate();

        s_Window->onUpdate();
    }
}

void Application::onEvent(Event& event) {
    TMP::log(event.toString());

    EventDispatcher dispatcher(event);
    dispatcher.dispatch<WindowCloseEvent>(onWindowClose);

    for (auto it = s_LayerStack.end(); it != s_LayerStack.begin();) {
        (*--it)->onEvent(event);
        if (event.isHandled()) break;
    }
}

bool Application::onWindowClose(WindowCloseEvent& e) {
    stop();
    return true;
}
