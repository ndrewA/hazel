#include "hzpch.h"
#include "Application.h"

// #define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace hazel
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() 
	{
		window = std::unique_ptr<Window>(Window::Create());
		window->setEventCallback(BIND_EVENT_FN(onEvent));
	}

	Application::~Application() 
	{ 
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

		HZ_CORE_TRACE("{0}", e);
	}

	void Application::run()
	{
		while (running)
		{
			glClearColor(0.3f, 0.8f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		running = false;

		return true;
	}
}