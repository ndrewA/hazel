#include "hzpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include "Hazel/Application.h"

namespace hazel
{
	Input* Input::instance = new WindowsInput;

	bool WindowsInput::isKeyPressedImpl(int keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::isMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<double, double> WindowsInput::getMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		std::pair<double, double> position;
		glfwGetCursorPos(window, &position.first, &position.second);
		return position;
	}

	double WindowsInput::getMouseXImpl()
	{
		auto [x, y] = getMousePosImpl();
		return x;
	}

	double WindowsInput::getMouseYImpl()
	{
		auto [x, y] = getMousePosImpl();
		return y;
	}
}