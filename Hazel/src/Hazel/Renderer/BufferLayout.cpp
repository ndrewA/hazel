#include "hzpch.h"
#include "BufferLayout.h"

namespace hazel
{
	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
		: elements(elements)
	{
		calculateOffsetAndStride();
	}
	void BufferLayout::setElements(const std::vector<BufferElement>& bufferElements)
	{
		elements = bufferElements;
		calculateOffsetAndStride();
	}

	void BufferLayout::calculateOffsetAndStride()
	{
		uint32_t offset = 0;
		stride = 0;
		for (auto& element : elements) {
			element.offset = offset;
			offset += element.size;
		}
		stride = offset;
	}

	uint32_t BufferElement::getComponentCount() const
	{
		switch (type)
		{
		case shaderDataType::none:		return 0;
		case shaderDataType::float4:	return 4;
		case shaderDataType::float3:	return 3;
		case shaderDataType::float2:	return 2;
		case shaderDataType::mat3:		return 3 * 3;
		case shaderDataType::mat4:		return 4 * 4;
		case shaderDataType::int1:		return 1;
		case shaderDataType::int2:		return 2;
		case shaderDataType::int3:		return 3;
		case shaderDataType::int4:		return 4;
		case shaderDataType::bool1:		return 1;
		}

		HZ_CORE_ASSERT(false, "shaderType unkonwn!");
		return 0;
	}
}