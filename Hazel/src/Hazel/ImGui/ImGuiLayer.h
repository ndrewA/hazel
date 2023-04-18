#pragma once
#include "Hazel/Layer.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

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
		bool handleFocus(WindowFocusEvent& e);
		bool handleLostFocus(WindowLostFocusEvent& e);
		bool handleKeyPressed(KeyPressedEvent& e);
		bool handleKeyReleased(KeyReleasedEvent& e);
		bool handleMouseButtonPressed(MouseButtonPressedEvent& e);
		bool handleMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool handleMouseMoved(MouseMovedEvent& e);
		bool handleMouseScrolled(MouseScrolledEvent& e);
		
	private:
		float time = 0;
	};
}