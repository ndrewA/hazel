#pragma once

#include "Hazel/Layer.h"

namespace hazel
{
	class HZ_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach() override;
		void onDetach() override;
		void onUpdate() override;
		void onEvent(Event& event) override;
	private:
		float time = 0;
	};
}