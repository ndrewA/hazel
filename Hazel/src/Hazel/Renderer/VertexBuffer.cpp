#include "hzpch.h"
#include "VertexBuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace hazel
{
	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch (Renderer::getAPI())
		{
		case rendererAPI::none:
			HZ_CORE_ASSERT(false, "rendererAPI::none not supported");
			return nullptr;
		case rendererAPI::opengl:
			return new OpenGLVertexBuffer(vertices, size);
		}

		HZ_CORE_ASSERT(false, "Unknown rendererAPI!");
		return nullptr;
	}
}