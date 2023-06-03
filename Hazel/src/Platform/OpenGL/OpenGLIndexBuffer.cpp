#include "hzpch.h"

#include <glad/glad.h>

#include "OpenGLIndexBuffer.h"


namespace hazel
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* vertices, size_t count)
		: count(count)
	{
		glCreateBuffers(1, &rendererID);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), vertices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &rendererID);
	}

	void OpenGLIndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	}

	void OpenGLIndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
