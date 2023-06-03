#pragma once

namespace hazel
{
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() { }

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual size_t getCount() const = 0;

		static IndexBuffer* create(uint32_t* vertices, size_t count);
	};
}

