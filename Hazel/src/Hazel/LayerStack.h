#pragma once

#include "Hazel/Core.h"
#include "Layer.h"

namespace hazel
{
	class HZ_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverLay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }
	private:
		std::vector<Layer*> layers;
		unsigned int layerInsertIndex = 0;
	};
}
