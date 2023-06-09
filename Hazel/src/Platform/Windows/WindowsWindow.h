#pragma once

#include "Hazel/Window.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace hazel
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override { return data.width; }
		inline unsigned int getHeight() const override { return data.height; }

		inline void* getNativeWindow() const override { return window; }

		// Window attributes
		inline void setEventCallback(const eventCallBackFn& callback) override { data.eventCallBack = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;

	private:
		virtual void init(const WindowProps& props);
		virtual void shutDown();

	private:
		GLFWwindow* window;
		GraphicsContext* context;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vsync;

			eventCallBackFn eventCallBack;
		};

		WindowData data;
	};
}
