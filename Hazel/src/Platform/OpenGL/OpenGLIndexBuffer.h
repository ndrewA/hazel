#pragma once

#include "Hazel/Renderer/IndexBuffer.h"

namespace hazel
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* vertices, uint32_t count);
		~OpenGLIndexBuffer() override;

		void bind() const override;
		void unbind() const override;

		uint32_t getCount() const override { return count; };

	private:
		uint32_t rendererID;
		uint32_t count;
	};
}