#pragma once

#include "BufferLayout.h"

namespace hazel
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() { }

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		BufferLayout getLayout() const { return layout; }
		void setLayout(const BufferLayout& bufferLayout) { layout = bufferLayout; }

		static VertexBuffer* create(float* vertices, uint32_t size);

	protected:
		BufferLayout layout;
	};
}

