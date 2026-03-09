#pragma once

#include "engine/window.h"
#include "engine/layer_stack.h"
#include "engine/event/event.h"
#include "engine/event/application_event.h"

#include <memory>

class Application {
public:
    Application() = delete;

    static void init();
    static void shutdown();

    static void run();
    static void stop() { s_Running = false; }

    static void onEvent(Event& event);

    static LayerStack& getLayerStack() { return s_LayerStack; }

private:
    static bool onWindowClose(WindowCloseEvent& e);

    static std::unique_ptr<Window> s_Window;
    static LayerStack s_LayerStack;
    static bool s_Running;
};
