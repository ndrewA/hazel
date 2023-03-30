#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern hazel::Application* hazel::createApplication();

int main(int argc, char** argv)
{
	auto app = hazel::createApplication();
	app->run();
	delete app;
	return 0;
}

#endif 
