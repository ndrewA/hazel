#include "hzpch.h"
#include "Application.h"

#include <glad/glad.h>

namespace hazel
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() 
	{
		window = std::unique_ptr<Window>(Window::Create());
		window->setEventCallback(BIND_EVENT_FN(onEvent));

		unsigned int id;
		glGenVertexArrays(1, &id);
	}

	Application::~Application() 
	{ 
	}

	void Application::pushLayer(Layer* layer)
	{
		layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* layer)
	{
		layerStack.pushOverlay(layer);
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

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

			window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		running = false;

		return true;
	}
}