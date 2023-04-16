#pragma once

#include "hzpch.h"

#include "Hazel/Core.h"

namespace hazel
{
	enum class eventType
	{
		none = 0,
		windowClose, windowResize, windowFocus, windowLostFocus, windowMoved,
		appTick, appUpdate, appRender,
		keyPressed, keyReleased,
		mouseButtonPressed, mouseButtonReleased, mouseMoved, mouseScrolled
	};

	enum eventCategory
	{
		none = 0,
		eventCategoryApplication	= BIT(0),
		eventCategoryInput			= BIT(1),
		eventCategoryKeyboard		= BIT(2),
		eventCategoryMouse			= BIT(3),
		eventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type)\
	static eventType getStaticType() { return eventType::##type; }\
	eventType getEventType() const override { return getStaticType(); }\
	const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) int getCategoryFlags() const override { return category; }

	class HZ_API Event
	{
		friend class EventDispatcher;

	public:
		bool handled = false;

		virtual eventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCathegory(eventCategory category)
		{
			return getCategoryFlags() & category;
		}
	};

	class EventDispatcher
	{
		template<typename T>
		using eventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: event(event) { }

		template<typename T>
		bool dispatch(eventFn<T> func)
		{
			if (event.getEventType() == T::getStaticType())
			{
				event.handled = func(*(T*)&event);
				return true;
			}
			return false;
		}
	private:
		Event& event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}
}