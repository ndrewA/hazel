#include "hzpch.h"
#include "OpenGLShader.h"

#include <cstdio>
#include <cstdlib>

#include <glad/glad.h>

namespace hazel
{
	OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		unsigned int vertexShader = makeShader(vertexPath, GL_VERTEX_SHADER);
		unsigned int fragmentShader = makeShader(fragmentPath, GL_FRAGMENT_SHADER);

		rendererID = glCreateProgram();

		glAttachShader(rendererID, vertexShader);
		glAttachShader(rendererID, fragmentShader);
		glLinkProgram(rendererID);

		glDetachShader(rendererID, vertexShader);
		glDetachShader(rendererID, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		int isLinked;

		glGetProgramiv(rendererID, GL_LINK_STATUS, &isLinked);
		if (!isLinked) {
			int infoLogLength = 0;
			glGetProgramiv(rendererID, GL_INFO_LOG_LENGTH, &infoLogLength);
			std::vector<char> infoLog(infoLogLength);

			glGetProgramInfoLog(rendererID, infoLogLength, nullptr, infoLog.data());

			HZ_ASSERT(false, "program failed: ", infoLog.data());
		}
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(rendererID);
	}

	void OpenGLShader::bind() const
	{
		glUseProgram(rendererID);
	}

	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}

	char* OpenGLShader::getShaderString(const std::string path) const
	{
		std::fstream file(path);
		HZ_ASSERT(file.is_open(), "File is not open: " + path);

		std::string shaderString(std::istreambuf_iterator<char>{file}, {});

		char* cShaderString = new char[shaderString.length() + 1];
		strcpy(cShaderString, shaderString.c_str());

		return cShaderString;
	}

	unsigned int OpenGLShader::makeShader(const std::string shaderPath, const uint32_t shaderType) const
	{
		unsigned int shader = glCreateShader(shaderType);

		char* shaderString = getShaderString(shaderPath);

		glShaderSource(shader, 1, &shaderString, nullptr);
		glCompileShader(shader);

		delete[] shaderString;

		int succes;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);

		if (succes == GL_FALSE) {
			int infoLogLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			std::vector<char> infoLog(infoLogLength);

			glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog.data());

			HZ_ERROR("{0}", infoLog.data());
			HZ_ASSERT(false, shaderType == GL_VERTEX_SHADER ? 
								"Vertex shader compilation failed!" 
								: "Fragment shader compilation failed!");
		}
		return shader;
	}
}
