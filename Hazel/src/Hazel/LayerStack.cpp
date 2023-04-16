#include "hzpch.h"
#include "LayerStack.h"

namespace hazel
{
	LayerStack::LayerStack()
	{
		layerInsert = layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (auto& layer : layers)
			delete layer;
	}

	void LayerStack::pushLayer(Layer* layer)
	{
		layerInsert = layers.emplace(layerInsert, layer);
	}

	void LayerStack::pushOverlay(Layer* overlay)
	{
		layers.emplace_back(overlay);
	}

	void LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end())
		{
			layers.erase(it);
			layerInsert--;
		}
	}

	void LayerStack::popOverLay(Layer* layer)
	{
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end()) {
			layers.erase(it);
		}
	}
}