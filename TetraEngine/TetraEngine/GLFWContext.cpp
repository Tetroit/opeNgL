#include "GLFWContext.h"
#include "Scene.h"
#include "Camera.h"
#include "InputManager.h"


GLFWContext* GLFWContext::current = nullptr;

GLFWContext::GLFWContext(int width, int height) : width(width), height(height)
{
	//window

	glfwInit();
	window = glfwCreateWindow(width, height, "showcase", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);
	if (!cursorEnabled)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(window);

	if (current == nullptr)
		current = this;
}
GLFWContext::~GLFWContext()
{
}
void GLFWContext::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {

	//ImGui_ImplGlfw_CursorPosCallback(window, xposIn, yposIn);
	if (current->captureMouse)
	{
		float posX = (float)xposIn;
		float posY = (float)yposIn;
		float deltaX, deltaY;
		deltaX = posX - current->lastMouseX;
		deltaY = current->lastMouseY - posY;
		current->lastMouseX = posX;
		current->lastMouseY = posY;

		Scene::currentScene->mainCamera->ProcessMouseMovement(deltaX, deltaY);
	}
}

void GLFWContext::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
}

void GLFWContext::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		current->inputManager->OnKeyDown(key);

	if (action == GLFW_RELEASE)
		current->inputManager->OnKeyUp(key);
}
