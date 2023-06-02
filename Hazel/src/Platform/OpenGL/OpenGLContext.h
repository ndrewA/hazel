#pragma once

#include "Hazel/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace hazel
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void init() override;
		void swapBuffers() override;
	private:
		GLFWwindow* windowHandle;
	};
}

