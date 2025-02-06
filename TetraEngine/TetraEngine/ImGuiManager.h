#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

class ImGuiManager
{
public:
	bool enableDockSpace = true;
	static void HelpMarker(const char* desc);
	ImGuiIO* io;
	ImGuiManager();
	void ShowDockSpace();
	void Update();
	void Render();
	~ImGuiManager();
};

