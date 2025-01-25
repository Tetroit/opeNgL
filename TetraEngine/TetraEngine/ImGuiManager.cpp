#include "ImGuiManager.h"
#include "Core.h"

ImGuiManager::ImGuiManager()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls


	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(Core::glfwManager->window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void ImGuiManager::Update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::ShowDemoWindow(); // Show demo window! :)

	if (io->WantCaptureKeyboard || io->WantTextInput) {
		if (GLFWManager::get()->sendKeyboardEvents)
			GLFWManager::get()->ToggleKeyboardEvents(false);
	}
	else {
		if (!GLFWManager::get()->sendKeyboardEvents)
			GLFWManager::get()->ToggleKeyboardEvents(true);
	}
	if (io->WantCaptureMouse || io->WantCaptureKeyboard)
	{
		if (GLFWManager::get()->sendMouseClickEvents)
			GLFWManager::get()->ToggleMouseClickEvents(false);
		if (GLFWManager::get()->sendMouseMoveEvents)
			GLFWManager::get()->ToggleMouseMoveEvents(false);
	}
	else
	{
		if (!GLFWManager::get()->sendMouseClickEvents)
			GLFWManager::get()->ToggleMouseClickEvents(true);
		if (!GLFWManager::get()->sendMouseMoveEvents)
			GLFWManager::get()->ToggleMouseMoveEvents(true);
	}
}

void ImGuiManager::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ImGuiManager::~ImGuiManager()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	io = nullptr;
}
