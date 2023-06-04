#pragma once

namespace hazel
{
	enum class shaderDataType
	{
		none = 0,
		float2, float3, float4,
		mat3, mat4,
		int1, int2, int3, int4,
		bool1
	};

	static uint32_t getShaderDataTypeSize(shaderDataType type)
	{
		{
			switch (type)
			{
			case shaderDataType::none:		return 0;
			case shaderDataType::float4:	return 4 *		sizeof(float);
			case shaderDataType::float3:	return 3 *		sizeof(float);
			case shaderDataType::float2:	return 2 *		sizeof(float);
			case shaderDataType::mat3:		return 3 * 3 *	sizeof(float);
			case shaderDataType::mat4:		return 4 * 4 *	sizeof(float);
			case shaderDataType::int1:		return 1 *		sizeof(int);
			case shaderDataType::int2:		return 2 *		sizeof(int);
			case shaderDataType::int3:		return 3 *		sizeof(int);
			case shaderDataType::int4:		return 4 *		sizeof(int);
			case shaderDataType::bool1:		return 1 *		sizeof(bool);
			}

			HZ_CORE_ASSERT(false, "shaderType unkonwn!");
			return 0;
		}
	}

	struct BufferElement
	{
		shaderDataType type;
		std::string name;
		uint16_t offset;
		uint32_t size;
		bool normalized;

		BufferElement(const shaderDataType type, const std::string& name, bool normalized = false)
			: type(type), name(name), offset(0), size(getShaderDataTypeSize(type)), normalized(normalized) { }

		uint32_t getComponentCount() const;
	};

	class BufferLayout
	{
	public:
		BufferLayout(const std::initializer_list<BufferElement>& elements);
		BufferLayout() { }

		void setElements(const std::vector<BufferElement>& bufferElements);

		std::vector<BufferElement> getElements() const { return elements; }
		uint32_t getStride() const { return stride; }

		std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		std::vector<BufferElement>::iterator end() { return elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return elements.end(); }

	private:
		void calculateOffsetAndStride();

	private:
		std::vector<BufferElement> elements;
		uint32_t stride = 0;
	};
}

