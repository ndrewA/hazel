#pragma once

#include "Hazel/Input.h"

namespace hazel
{
	class HZ_API WindowsInput : public Input
	{
	protected:
		bool isKeyPressedImpl(int keyCode) override;
		bool isMouseButtonPressedImpl(int button) override;
		std::pair<double, double> getMousePosImpl() override;
		double getMouseXImpl() override;
		double getMouseYImpl() override;
	};
}
