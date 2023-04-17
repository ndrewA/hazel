#include <Hazel.h>

class ExampleLayer : public hazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void ExampleLayer::onUpdate() override
	{
		HZ_INFO("ExampleLayer::onUpdate");
	}

	void ExampleLayer::onEvent(hazel::Event& event) override
	{
		HZ_TRACE("{0}", event);
	}
};

class Sandbox : public hazel::Application
{
public:
	Sandbox()
	{
		pushLayer(new ExampleLayer);
		pushOverlay(new hazel::ImGuiLayer);
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