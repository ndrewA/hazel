#include "hzpch.h"

#include <filesystem>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Application.h"
#include "Input.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer/BufferLayout.h"

namespace hazel
{
	Application* Application::instance = nullptr;

	Application::Application() 
	{
		HZ_CORE_ASSERT(!instance, "Application already exists!");
		instance = this;

		window = std::unique_ptr<Window>(Window::Create());
		window->setEventCallback(BIND_EVENT_FN(Application::onEvent));

		imGuiLayer = new ImGuiLayer;
		pushOverlay(imGuiLayer);

		float vertices[] = {
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f,
		};
		vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));

		vertexBuffer->setLayout(
		  { { shaderDataType::float3, "aPosition" },
			{ shaderDataType::float4, "aColor"    } });

		uint32_t indices[] =
		{
			0, 1, 2,
			0, 2, 3
		};
		indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(indices[0])));
		
		vertexArray.reset(VertexArray::create());
		vertexArray->addVertexBuffer(vertexBuffer);
		vertexArray->setIndexBuffer(indexBuffer);

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
			vertexArray->bind();
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