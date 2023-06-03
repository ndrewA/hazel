#include "hzpch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace hazel
{
	Shader* Shader::create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::getAPI())
		{
		case rendererAPI::none:
			HZ_CORE_ASSERT(false, "rendererAPI::none not supported!");
			return nullptr;
		case rendererAPI::opengl:
			return new OpenGLShader(vertexSource, fragmentSource);
		}

		HZ_CORE_ASSERT(false, "Unknown rendererAPI!");
		return nullptr;
	}
}