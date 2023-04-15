#include "hzpch.h"
#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

namespace hazel
{
	Application::Application() 
	{
		window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() { }

	void Application::run()
	{
		while (running)
		{
			glClearColor(0.3f, 0.8f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			window->onUpdate();
		}
	}
}