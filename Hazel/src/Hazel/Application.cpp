#include "hzpch.h"

#include <filesystem>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Application.h"
#include "Input.h"

#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"
#include "Renderer/BufferLayout.h"

namespace hazel
{
	Application* Application::instance = nullptr;

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

	Application::Application() 
	{
		HZ_CORE_ASSERT(!instance, "Application already exists!");
		instance = this;

		window = std::unique_ptr<Window>(Window::Create());
		window->setEventCallback(BIND_EVENT_FN(Application::onEvent));

		imGuiLayer = new ImGuiLayer;
		pushOverlay(imGuiLayer);

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		float vertices[] = {
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f,
		};

		vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
		vertexBuffer->bind(); 
		{

			BufferLayout layout
			(
				{ { shaderDataType::float3, "aPosition" },
				 { shaderDataType::float4, "aColor" } }
			);

			vertexBuffer->setLayout(layout);
		}

		{
			uint32_t index = 0;
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
		}

		uint32_t indices[] =
		{
			0, 1, 2,
			0, 2, 3
		};

		indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(indices[0])));
		vertexBuffer->bind();

		std::string shaderPath = std::filesystem::absolute("../Hazel/src/Platform/OpenGL/Shader/").string();
		shader.reset(Shader::create(shaderPath + "shader.vert",
								    shaderPath + "shader.frag"));
	}

	Application::~Application() 
	{ 
	}

	void Application::pushLayer(Layer* layer)
	{
		layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* layer)
	{
		layerStack.pushOverlay(layer);
		layer->onAttach();
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));

		for (auto it = layerStack.end(); it != layerStack.begin();) {
			(*--it)->onEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::run()
	{
		while (running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->bind();
			glBindVertexArray(vertexArray);
			glDrawElements(GL_TRIANGLES, indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

			for (auto& layer : layerStack)
				layer->onUpdate();

			imGuiLayer->begin();
			for (auto& layer : layerStack)
				layer->onImGuiRender();
			imGuiLayer->end();

			window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		running = false;

		return true;
	}
}