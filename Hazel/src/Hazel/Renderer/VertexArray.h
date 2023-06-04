#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace hazel
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() { }

		virtual void bind() const  = 0;
		virtual void unbind() const = 0;

		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffers() const = 0;
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0;

		static VertexArray* create();
	};
}

