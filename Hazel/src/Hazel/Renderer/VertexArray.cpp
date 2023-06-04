#include "hzpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace hazel
{
	VertexArray* VertexArray::create()
	{
		switch (Renderer::getAPI())
		{
		case rendererAPI::none:
			HZ_CORE_ASSERT(false, "rendererAPI::none not supported!");
			return nullptr;
		case rendererAPI::opengl:
			return new OpenGLVertexArray();
		}

		HZ_CORE_ASSERT(false, "Unknown rendererAPI!");
		return nullptr;
	}
}
