#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

class Texture2D;
class Viewport;
class ImGuiManager
{
public:
	bool enableDockSpace = true;
	bool showViewport = true;
	bool allowSceneInteraction = false;
	Texture2D* testTex;

	static void HelpMarker(const char* desc);
	static void DrawTexture2D(const Texture2D& texture, int width, int height);
	ImGuiIO* io;
	ImGuiManager();
	void ShowDockSpace();
	void ShowViewport(Viewport* vp);
	void Update();
	void Render();
	~ImGuiManager();
};

