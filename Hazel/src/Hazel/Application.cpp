#include "Application.h"

#include <iostream>

namespace hazel
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (true)
		{
			std::cout << "RUNNING\n";
		}
	}
}