#pragma once

#include "Hazel/Renderer/Shader.h"

namespace hazel
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath);
		virtual ~OpenGLShader();

		void bind() const override;
		void unbind() const override;

	private:
		char* getShaderString(const std::string path) const;

		unsigned int makeShader(const std::string shaderPath, const uint32_t shaderType) const;

	private:
		uint32_t rendererID;
	};
}

