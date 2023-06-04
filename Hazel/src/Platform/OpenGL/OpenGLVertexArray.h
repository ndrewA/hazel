#pragma once

#include "Hazel/Renderer/VertexArray.h"

namespace hazel
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		void bind() const override;
		void unbind() const override;

		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& newIndexBuffer) override;

		std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffers() const override { return vertexBuffers; }
		std::shared_ptr<IndexBuffer> getIndexBuffer() const override { return indexBuffer; }

	private:
		uint32_t rendererID;
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;

		uint32_t index = 0;
	};
}

