#pragma once

#include "Event.h"

namespace hazel
{
	class HZ_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: width(width), height(height) { }

		inline unsigned int getWidth() const { return width; }
		inline unsigned int getHeight() const { return height; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "windowResizeEvent width: " << width << ", height: " << height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(windowResize)
		EVENT_CLASS_CATEGORY(eventCategoryApplication)
	private:
		unsigned int width, height;
	};

	class HZ_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() { }

		EVENT_CLASS_TYPE(windowClose)
		EVENT_CLASS_CATEGORY(eventCategoryApplication)
	};

	class HZ_API WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowFocusEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(windowFocus)
		EVENT_CLASS_CATEGORY(eventCategoryApplication)
	};

	class HZ_API WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowLostFocusEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(windowLostFocus)
		EVENT_CLASS_CATEGORY(eventCategoryApplication)
	};

	class HZ_API CursorEnteredWindowEvent : public Event
	{
	public:
		CursorEnteredWindowEvent() { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "CursorEnteredWindowEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(cursorEntered)
		EVENT_CLASS_CATEGORY(eventCategoryApplication)
	};

	class HZ_API CursorLeftWindowEvent : public Event
	{
	public:
		CursorLeftWindowEvent() { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "CursorLeftWindowEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(cursorLeft)
		EVENT_CLASS_CATEGORY(eventCategoryApplication)
	};

	class HZ_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() { }

		EVENT_CLASS_TYPE(appTick)
		EVENT_CLASS_CATEGORY(eventCategoryApplication)
	};

	class HZ_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() { }

		EVENT_CLASS_TYPE(appUpdate)
		EVENT_CLASS_CATEGORY(eventCategoryApplication)
	};

	class HZ_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() { }

		EVENT_CLASS_TYPE(appRender)
		EVENT_CLASS_CATEGORY(eventCategoryApplication)
	};
}