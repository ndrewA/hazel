#include "hzpch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace hazel
{
	static GLenum shaderDataTypeToOpenGLBaseType(const shaderDataType type)
	{
		switch (type)
		{
		case shaderDataType::float4:	return GL_FLOAT;
		case shaderDataType::float3:	return GL_FLOAT;
		case shaderDataType::float2:	return GL_FLOAT;
		case shaderDataType::mat3:		return GL_FLOAT;
		case shaderDataType::mat4:		return GL_FLOAT;
		case shaderDataType::int1:		return GL_FLOAT;
		case shaderDataType::int2:		return GL_INT;
		case shaderDataType::int3:		return GL_INT;
		case shaderDataType::int4:		return GL_INT;
		case shaderDataType::bool1:		return GL_BOOL;
		}

		HZ_CORE_ASSERT(false, "Cannot return OpengGL type!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &rendererID);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(rendererID);
	}

	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		HZ_CORE_ASSERT(vertexBuffer, "vertexBuffer is nullptr!");
		HZ_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "There is no layout!");

		glBindVertexArray(rendererID);
		vertexBuffer->bind();

		const BufferLayout& layout = vertexBuffer->getLayout();

		for (const auto& element : layout) {
			GLenum openGLDataType = shaderDataTypeToOpenGLBaseType(element.type);
			uint32_t stride = layout.getStride();
			uint16_t offset = element.offset;
			bool normalized = element.normalized;

			glVertexAttribPointer(index, element.getComponentCount(), openGLDataType, normalized, stride, (const void*)offset);
			glEnableVertexAttribArray(index);

			++index;
		}
		vertexBuffers.push_back(vertexBuffer);
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& newIndexBuffer)
	{
		HZ_CORE_ASSERT(newIndexBuffer, "newIndexBuffer is nullptr!");

		glBindVertexArray(rendererID);
		newIndexBuffer->bind();
		indexBuffer = newIndexBuffer;
		glBindVertexArray(0);
	}
}