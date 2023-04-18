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
		if (hazel::Input::isKeyPressed(HZ_KEY_TAB))
			HZ_TRACE("TAB IS PRESSED (POLL)");
		//HZ_INFO("ExampleLayer::onUpdate");
	}

	void ExampleLayer::onEvent(hazel::Event& event) override
	{
		if (event.getEventType() == hazel::eventType::keyPressed)
		{
			hazel::KeyPressedEvent& e = (hazel::KeyPressedEvent&)event;
			if (e.getKeyCode() == HZ_KEY_TAB)
				HZ_TRACE("TAB IS PRESSED (EVENT)");
			HZ_TRACE("{0}", (char)e.getKeyCode());
		}
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