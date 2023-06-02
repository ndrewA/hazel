#pragma once

namespace hazel
{
	class GraphicsContext
	{
	public:
		virtual void init() = 0;
		virtual void swapBuffers() = 0;
	};
}