#include "hzpch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Input.h"

#include "glm/glm.hpp"

namespace hazel
{
	Application* Application::instance = nullptr;

	Application::Application() 
	{
		HZ_CORE_ASSERT(!instance, "Application already exists!");
		instance = this;

		window = std::unique_ptr<Window>(Window::Create());
		window->setEventCallback(BIND_EVENT_FN(Application::onEvent));

		imGuiLayer = new ImGuiLayer;
		pushOverlay(imGuiLayer);
	}

	Application::~Application() 
	{ 
	}

	void Application::pushLayer(Layer* layer)
	{
		layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* layer)
	{
		layerStack.pushOverlay(layer);
		layer->onAttach();
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));

		for (auto it = layerStack.end(); it != layerStack.begin();) {
			(*--it)->onEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::run()
	{
		while (running)
		{
			glClearColor(0.3f, 0.8f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto& layer : layerStack)
				layer->onUpdate();

			imGuiLayer->begin();
			for (auto& layer : layerStack)
				layer->onImGuiRender();
			imGuiLayer->end();

			window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		running = false;

		return true;
	}
}