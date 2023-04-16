#pragma once

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"
 
namespace hazel
{
	class HZ_API Layer
	{
	public:
		Layer(const std::string& name = "layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getName() const { return debugName; }
	protected:
		std::string debugName;
	};
}