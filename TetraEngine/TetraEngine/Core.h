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

#define SET_KEY_EVENT(Type, keyInfo, func, obj) Core::inputManager->keyDispatcher.AddListener<Type>(keyInfo, &Type::func, obj);

static class Core
{
public:

	static ImGuiIO* io;
	static unsigned int width, height;
	static float lastMouseX, lastMouseY;
	static bool cursorEnabled;
	static Application* application;

	static GLFWContext* glfwContext;
	static InputManager* inputManager;

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
	static void CloseApplication(const Event<KeyInfo>& ev);
	//input
	static void processInput(GLFWwindow* window);

	friend int main();
};

