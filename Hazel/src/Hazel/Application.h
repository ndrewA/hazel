#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace hazel
{
	class HZ_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	private:
	};

	// TO BE DEFINED IN CLIENT
	Application* createApplication();
}
