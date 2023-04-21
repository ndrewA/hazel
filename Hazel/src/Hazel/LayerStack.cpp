#include "hzpch.h"
#include "LayerStack.h"

namespace hazel
{
	LayerStack::LayerStack()
	{
		layerInsertIndex = 0;
	}

	LayerStack::~LayerStack()
	{
		for (auto& layer : layers)
			delete layer;
	}

	void LayerStack::pushLayer(Layer* layer)
	{
		layers.emplace(layers.begin()+layerInsertIndex, layer);
		layerInsertIndex++;
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
			layerInsertIndex--;
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