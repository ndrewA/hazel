#pragma once
namespace hazel
{
	enum class rendererAPI
	{
		none = 0,
		opengl = 1
	};

	class Renderer
	{
	public:
		inline static rendererAPI getAPI() { return rendererAPI; }
	private:
		static rendererAPI rendererAPI;
	};
}

