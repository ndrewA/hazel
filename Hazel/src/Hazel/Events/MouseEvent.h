#pragma once

#include "Event.h"

namespace hazel
{
	class HZ_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(double x, double y)
			: mouseX(x), mouseY(y) { }

		inline double getX() const { return mouseX; }
		inline double getY() const { return mouseY; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "mouseMovedEvent x: " << mouseX << ", y: " << mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouseMoved)
		EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryInput)
	private:
		double mouseX, mouseY;
	};

	class HZ_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: xOffset(xOffset), yOffset(yOffset) { }

		inline float getXOffset() const { return xOffset; }
		inline float getYOffset() const { return yOffset; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "mouseScrolledEvent x: " << xOffset << ", " << yOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouseScrolled)
		EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryInput)
	private:
		float xOffset, yOffset;
	};

	class HZ_API MouseButtonEvent : public Event
	{
	public:
		inline int getButton() const { return button; }
		inline int getMods() const { return mods; }

		EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryInput);
	protected:
		MouseButtonEvent(int button, int mods)
			: button(button), mods(mods) { }

		int button;
		int mods;
	};

	class HZ_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button, int mods)
			: MouseButtonEvent(button, mods) { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "mouseButtonPressedEvent: " << button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouseButtonPressed)
	};

	class HZ_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button, int mods)
			: MouseButtonEvent(button, mods) { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "mouseButtonReleasedEvent: " << button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouseButtonReleased)
	};
}