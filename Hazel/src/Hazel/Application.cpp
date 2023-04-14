#include "hzpch.h"
#include "Application.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

namespace hazel
{
	Application::Application() { }

	Application::~Application() { }

	void Application::run()
	{
		WindowResizeEvent e(1280, 720);
		if(e.isInCathegory(eventCategoryApplication))
			HZ_TRACE(e);
		HZ_ERROR("ERROR404");
	}
}