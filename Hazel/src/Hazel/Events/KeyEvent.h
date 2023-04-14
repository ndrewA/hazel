#pragma once

#include "Event.h"

namespace hazel
{
	class HZ_API KeyEvent : public Event
	{
	public:
		inline int getKeyCode() { return keyCode; }
		
		EVENT_CLASS_CATEGORY(eventCategoryKeyboard | eventCategoryInput)
	protected:
		KeyEvent(int keyCode)
			: keyCode(keyCode) { }

		int keyCode;
	};

	class HZ_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), repeatCount(repeatCount) { }

		inline int getRepeatCount() const { return repeatCount; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "keyPressedEvent: " << keyCode << " (" << repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(keyPressed)
	private:
		int repeatCount;
	};

	class HZ_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode){ }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "keyReleasedEvent: " << keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(keyReleased)
	};
}