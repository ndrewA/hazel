#pragma once

#include "Hazel/Renderer/IndexBuffer.h"

namespace hazel
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* vertices, size_t count);
		virtual ~OpenGLIndexBuffer();

		void bind() const override;
		void unbind() const override;

		size_t getCount() const override { return count; };

	private:
		uint32_t rendererID;
		uint32_t count;
	};
}
