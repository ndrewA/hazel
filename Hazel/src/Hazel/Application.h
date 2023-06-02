#pragma once

#include "hzpch.h"

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Hazel/ImGui/ImGuiLayer.h"

#include "Hazel/Renderer/Shader.h"

namespace hazel
{
	class HZ_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);

		inline Window& getWindow() const { return *window; }

		inline static Application& get() { return *instance; }
	private:
		bool onWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;
		bool running = true;
		LayerStack layerStack;

		unsigned int vertexArray, vertexBuffer, indexBuffer;
		std::unique_ptr<Shader> shader;
	private:
		static Application* instance;
	};

	// TO BE DEFINED IN CLIENT
	Application* createApplication();
}
