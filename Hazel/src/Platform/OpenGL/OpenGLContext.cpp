#include "hzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace hazel
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: windowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(windowHandle, "windowHandle is nullptr");
	}

	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize glad!");

		HZ_CORE_INFO("OpenGL Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		HZ_CORE_INFO("OpenGL Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		HZ_CORE_INFO("OpenGL Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(windowHandle);
	}
}