#include "hzpch.h"
#include "IndexBuffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace hazel
{
	IndexBuffer* IndexBuffer::create(uint32_t* vertices, size_t count)
	{
		switch (Renderer::getAPI())
		{
		case rendererAPI::none:
			HZ_CORE_ASSERT(false, "rendererAPI::none not supported");
			return nullptr;
		case rendererAPI::opengl:
			return new OpenGLIndexBuffer(vertices, count);
		}

		HZ_CORE_ASSERT(false, "Unknown rendererAPI!");
		return nullptr;
	}
}