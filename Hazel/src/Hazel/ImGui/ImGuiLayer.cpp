
#include "hzpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
// ====== TEMPORARY ========
#include <GLFW/glfw3.h>
#include <glad/glad.h>
// =========================

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Platform/GLFW/ImGuiGLFWRenderer.h"

#include "Hazel/Core.h"
#include "Hazel/Application.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace hazel
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
		onDetach();
	}

	void ImGuiLayer::onAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;   
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), false);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::onDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::onUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();
		io.DisplaySize = ImVec2((float)app.getWindow().getWidth(), (float)app.getWindow().getHeight());
		
		float currentTime = (float)glfwGetTime();
		io.DeltaTime = time > 0.0 ? (currentTime - time) : (1.0f / 60.0f);
		time = currentTime;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::onEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowFocusEvent>(BIND_EVENT_FN(ImGuiLayer::handleFocus));
		dispatcher.dispatch<WindowLostFocusEvent>(BIND_EVENT_FN(ImGuiLayer::handleLostFocus));
		dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FN(ImGuiLayer::handleKeyPressed));
		dispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::handleKeyReleased));
		dispatcher.dispatch<CharEvent>(BIND_EVENT_FN(ImGuiLayer::handleCharInput));
		dispatcher.dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(ImGuiLayer::handleMouseButtonPressed));
		dispatcher.dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(ImGuiLayer::handleMouseButtonReleased));
		dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FN(ImGuiLayer::handleMouseMoved));
		dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FN(ImGuiLayer::handleMouseScrolled));
	}

	bool ImGuiLayer::handleFocus(WindowFocusEvent& e)
	{
		ImGui_ImplGlfw_WindowFocusCallback(glfwGetCurrentContext(), 1);
		return false;
	}

	bool ImGuiLayer::handleLostFocus(WindowLostFocusEvent& e)
	{
		ImGui_ImplGlfw_WindowFocusCallback(glfwGetCurrentContext(), 0);
		return false;
	}

	bool ImGuiLayer::handleWindowResize(WindowResizeEvent& e)
	{
		Application& app = Application::get();
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)app.getWindow().getWidth(), (float)app.getWindow().getHeight());
		glViewport(0, 0, e.getWidth(), e.getHeight());

		return false;
	}
	
	bool ImGuiLayer::handleKeyPressed(KeyPressedEvent& e)
	{
		ImGui_ImplGlfw_KeyCallback(glfwGetCurrentContext(), 
								   e.getKeyCode(), e.getScanCode(), GLFW_PRESS, e.getMods());
		return ImGui::GetIO().WantCaptureKeyboard;
	}

	bool ImGuiLayer::handleKeyReleased(KeyReleasedEvent& e)
	{
		ImGui_ImplGlfw_KeyCallback(glfwGetCurrentContext(), 
								   e.getKeyCode(), e.getScanCode(), GLFW_RELEASE, e.getMods());
		return ImGui::GetIO().WantCaptureKeyboard;
	}

	bool ImGuiLayer::handleCharInput(CharEvent& e)
	{
		ImGui_ImplGlfw_CharCallback(glfwGetCurrentContext(), e.getCodePoint());
		return ImGui::GetIO().WantCaptureKeyboard;
	}

	bool ImGuiLayer::handleMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		ImGui_ImplGlfw_MouseButtonCallback(glfwGetCurrentContext(), 
										   e.getButton(), GLFW_PRESS, e.getMods());
		return ImGui::GetIO().WantCaptureMouse;
	}

	bool ImGuiLayer::handleMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		ImGui_ImplGlfw_MouseButtonCallback(glfwGetCurrentContext(), 
										   e.getButton(), GLFW_RELEASE, e.getMods());
		return ImGui::GetIO().WantCaptureMouse;
	}

	bool ImGuiLayer::handleMouseMoved(MouseMovedEvent& e)
	{
		ImGui_ImplGlfw_CursorPosCallback(glfwGetCurrentContext(), 
										 e.getX(), e.getY());
		return ImGui::GetIO().WantCaptureMouse;
	}

	bool ImGuiLayer::handleMouseScrolled(MouseScrolledEvent& e)
	{
		ImGui_ImplGlfw_ScrollCallback(glfwGetCurrentContext(), 
									  e.getXOffset(), e.getYOffset());
		return ImGui::GetIO().WantCaptureMouse;
	}
}
