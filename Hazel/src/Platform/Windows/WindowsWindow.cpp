#include "hzpch.h"
#include "WindowsWindow.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace hazel
{
	static bool GLFWInitialized = false;

	static void GLFWErrorCallBack(int error_code, const char* description)
	{
		HZ_CORE_ERROR("GLFW_ERROR ({0}): {1}", error_code, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		init(props);
	}

	WindowsWindow::~WindowsWindow() 
	{ 
		shutDown();
		glfwTerminate();
	}

	void WindowsWindow::init(const WindowProps& props)
	{
		data.title = props.title;
		data.width = props.width;
		data.height = props.height;

		HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (!GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int succes = glfwInit();
			HZ_CORE_ASSERT(succes, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallBack);
			GLFWInitialized = true;
		}

		window = glfwCreateWindow((int)props.width, (int)props.height, data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		setVSync(true);

		// set glfw callbacks
		glfwSetWindowSizeCallback(window, [](GLFWwindow* currentWindow, int width, int height) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(currentWindow);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.eventCallBack(event);
		});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* currentWindow)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(currentWindow);
			WindowCloseEvent event;
			data.eventCallBack(event);
		});

		glfwSetKeyCallback(window, [](GLFWwindow* currentWindow, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(currentWindow);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.eventCallBack(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallBack(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.eventCallBack(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* currentWindow, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(currentWindow);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.eventCallBack(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.eventCallBack(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow* currentWindow, double xoffset, double yoffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(currentWindow);

			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			data.eventCallBack(event);
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* currentWindow, double xpos, double ypos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(currentWindow);

			MouseMovedEvent event((float)xpos, (float)ypos);
			data.eventCallBack(event);
		});
	}


	void WindowsWindow::shutDown()
	{
		glfwDestroyWindow(window);
	}

	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowsWindow::setVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		data.vsync = enabled;
	}

	bool WindowsWindow::isVSync() const
	{
		return data.vsync;
	}
}
