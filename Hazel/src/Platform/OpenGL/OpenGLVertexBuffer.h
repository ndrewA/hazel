#pragma once

#include "Hazel/Renderer/VertexBuffer.h"

namespace hazel
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		void bind() const override;
		void unbind() const override;

	private:
		uint32_t rendererID;
	};
}

