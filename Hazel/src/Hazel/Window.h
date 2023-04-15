#pragma once

#include "hzpch.h"

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace hazel
{
	struct WindowProps
	{
		std::string title;
		unsigned int width, height;

		WindowProps(const std::string& title = "Hazel Engine",
					unsigned int width = 1280,
					unsigned int height = 720) :
			title(title), width(width), height(height) { }
	};

	// Interface representing a desktop system based Window
	class HZ_API Window
	{
	public:
		using eventCallBackFn = std::function<void(Event&)>;

		virtual ~Window() { }

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		// Window attributes
		virtual void setEventCallback(const eventCallBackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}