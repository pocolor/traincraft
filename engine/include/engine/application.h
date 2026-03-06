#pragma once
#include "window.h"
#include <memory>

class Application {
public:
    Application();

    void run();
    void stop();

    void onEvent(const Event& event);

private:
    std::unique_ptr<Window> m_Window;
    bool m_Running = false;
};
