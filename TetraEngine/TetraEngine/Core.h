#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>
#include <thread>

#include "Time.h"
#include "Scene.h"
#include "ConsoleManager.h"
#include "InputManager.h"
//#include "TestBehaviour.h"
#include "FreeType.h"
#include "Application.h"
#include "DestroyManager.h"
#include "PointLight.h"
#include "Material.h"
#include "LightRenderer.h"
#include "VertexData.h"
#include "Camera.h"
#include "Texture2D.h"
#include "Skybox.h"
#include "OBJParser.h"

static class Core
{
public:
	static GLFWwindow* window;
	static ImGuiIO* io;
	static unsigned int width, height;
	static float lastMouseX, lastMouseY;
	static bool LMBpressed;
	static bool cursorEnabled;
	static Application* application;

private:

	template <typename T>
	static void CreateApplication() {
		if (std::is_base_of<Application, T>::value)
			application = new T();
		else
			throw std::invalid_argument("input is not an application type");
	}

	static int Initialize();
	static void InitializePresets();
	static void Update();
	static void UpdateOverlay();
	static void CleanUp();
	static void AfterUpdate();

	//console
	static void processConsole();
	//input
	static void processInput(GLFWwindow* window);
	static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	friend int main();
};

