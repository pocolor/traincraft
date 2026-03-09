#include "engine/layer_stack.h"

#include <algorithm>

LayerStack::LayerStack() {
    m_LayerInsert = m_Layers.begin();
}

LayerStack::~LayerStack() {
    for (const Layer* layer : m_Layers)
        delete layer;
}

void LayerStack::pushLayer(Layer* layer) {
    m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
}

void LayerStack::popLayer(Layer* layer) {
    if (
        const auto it = std::ranges::find(m_Layers, layer);
        it != m_Layers.end()
    ) {
        m_Layers.erase(it);
        --m_LayerInsert;
    }
}

void LayerStack::pushOverlay(Layer* overlay) {
    m_Layers.emplace_back(overlay);
}

void LayerStack::popOverlay(Layer* overlay) {
    if (
        const auto it = std::ranges::find(m_Layers, overlay);
        it != m_Layers.end()
    ) {
        m_Layers.erase(it);
    }
}
