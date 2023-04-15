#pragma once

#include "hzpch.h"

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace hazel
{
	class HZ_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	private:
		std::unique_ptr<Window> window;
		bool running = true;
	};

	// TO BE DEFINED IN CLIENT
	Application* createApplication();
}
