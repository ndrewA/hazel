#pragma once

#include "Event.h"

namespace hazel
{
	class HZ_API KeyEvent : public Event
	{
	public:
		inline int getKeyCode() const { return keyCode; }
		inline int getScanCode() const { return scancode; }
		inline int getMods() const { return mods; }
		
		EVENT_CLASS_CATEGORY(eventCategoryKeyboard | eventCategoryInput)
	protected:
		KeyEvent(int keyCode, int scancode, int mods)
			: keyCode(keyCode), scancode(scancode), mods(mods) { }

		int keyCode;
		int scancode;
		int mods;
	};

	class HZ_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int scancode, int mods, int repeatCount)
			: KeyEvent(keyCode, scancode, mods), repeatCount(repeatCount) { }

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
		KeyReleasedEvent(int keyCode, int scancode, int mods)
			: KeyEvent(keyCode, scancode, mods) { }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "keyReleasedEvent: " << keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(keyReleased)
	};
}