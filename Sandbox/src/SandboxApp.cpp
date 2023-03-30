#include <Hazel.h>

class Sandbox : public hazel::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{
	}

private:
};

hazel::Application* hazel::createApplication()
{
	return new Sandbox;
}