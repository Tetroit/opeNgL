#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

class ImGuiManager
{
public:
	ImGuiIO* io;
	ImGuiManager();
	void Update();
	void Render();
	~ImGuiManager();
};

