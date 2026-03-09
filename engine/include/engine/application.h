#pragma once

#include "engine/window.h"
#include "engine/layer_stack.h"
#include "engine/event/event.h"
#include "engine/event/application_event.h"

#include <memory>

class Application {
public:
    Application();
    ~Application();

    void run();
    void stop() { m_Running = false; }

    void onEvent(Event& event);

    LayerStack& getLayerStack() { return m_LayerStack; }

private:
    bool onWindowClose(WindowCloseEvent& e);

    std::unique_ptr<Window> m_Window;
    LayerStack m_LayerStack;
    bool m_Running;
};
