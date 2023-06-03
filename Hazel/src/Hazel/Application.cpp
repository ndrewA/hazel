#include "hzpch.h"

#include "Application.h"
#include "Input.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

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
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
		};

		uint32_t indices[] =
		{
			0, 1, 2
		};

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);
		

		vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
		vertexBuffer->bind(); 

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);

		indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(indices[0])));
		vertexBuffer->bind();

		std::string vertexSource = R"(
			#version 460
			
			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec4 aColor;
			
			out vec4 color;

			void main() {
				color = aColor;
				gl_Position = vec4(aPosition, 1.0f);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core
			
			in vec4 color;

			out vec4 FragColor;

			void main()
			{
				FragColor = color;
			} 
		)";

		shader = std::make_unique<Shader>(vertexSource, fragmentSource);
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