#pragma once

#include "Hazel/Core.h"

namespace hazel
{
	class HZ_API Input
	{
	public:
		inline static bool isKeyPressed(int keyCode) { return instance->isKeyPressedImpl(keyCode); }
		inline static bool isMouseButtonPressed(int button) { return instance->isMouseButtonPressedImpl(button); }
		inline static std::pair<double, double> getMousePos() { return instance->getMousePosImpl(); };
		inline static double getMouseX() { return instance->getMouseXImpl(); }
		inline static double getMouseY() { return instance->getMouseYImpl(); }

	protected:
		virtual bool isKeyPressedImpl(int keyCode) = 0;
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<double, double> getMousePosImpl() = 0;
		virtual double getMouseXImpl() = 0;
		virtual double getMouseYImpl() = 0;

	private:
		static Input* instance;
	};
}