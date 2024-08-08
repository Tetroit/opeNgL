#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "Time.h"
#include "GameObject.h"

extern void processInput(GLFWwindow* window);
extern void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void InitialisePresets()
{
	Shader::InitialiseShaders();
	VertexData::InitialisePrefabs();
	MeshRenderer::InitialiseRenderer();
}
Camera mainCamera = Camera(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
float lastMouseX, lastMouseY;

int main()
{
	static unsigned int width = 1920;
	static unsigned int height = 1080;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "some random shit idk", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(window);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	InitialisePresets();
	GameObject::currentTransform = glm::mat4(1);

	Shader shader = Shader("shaders/lit.glvs", "shaders/lit.glfs");
	shader.Use();
	glm::vec4 ambient(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 diffuse(1.0f, 1.0f, 1.0f, 1.0f);
	shader.SetVec4("ambientColor", ambient);
	shader.SetVec4("diffuseColor", diffuse);
	GameObject light(glm::vec3(5, 0, 0));

	GameObject cube1(glm::vec3(5, 0, 0));
	GameObject cube2(glm::vec3(0, 5, 0));
	GameObject cube3(glm::vec3(0, 0, 5));

	light.AddChild(&cube1);
	cube1.AddChild(&cube2);
	cube2.AddChild(&cube3);

	MeshRenderer renderer3D = MeshRenderer(VertexData::GetPrefab(VD_SUZANNE), &shader);
	renderer3D.setTexture("Assets/debug.jpeg");

	GameObject monke(glm::vec3(0, 0, 0), &renderer3D);

	mainCamera.projectionView = glm::perspective((float)glm::radians(45.0), (float)width / (float)height, 0.1f, 100.0f);
	glm::mat4 cameraTransform;

	while (!glfwWindowShouldClose(window))
	{
		Time::Update();
		processInput(window);

		light.transform[3][0] = cos(Time::time) * 5;
		light.transform[3][2] = sin(Time::time) * 5;
		light.transform = glm::rotate(light.transform, Time::deltaTime, glm::vec3(0, 1, 0));
		cube1.transform = glm::rotate(cube1.transform, Time::deltaTime*2, glm::vec3(0, 0, 1));
		cube2.transform = glm::rotate(cube2.transform, Time::deltaTime*3, glm::vec3(1, 0, 0));
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//box.Render();
		//renderer2D.Render();
		shader.Use();
		glm::vec3 lightPos = light.getPos();
		shader.SetVec3("lightPos", lightPos);
		shader.SetVec3("viewPos", mainCamera.Position);
		monke.Render();
		light.Render();

		//cube1.Render();
		//cube2.Render();
		//cube3.Render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		//std::cout << Time::GetFPS() << '\n';
	}
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		mainCamera.ProcessKeyboard(FORWARD, Time::deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		mainCamera.ProcessKeyboard(BACKWARD, Time::deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		mainCamera.ProcessKeyboard(RIGHT, Time::deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		mainCamera.ProcessKeyboard(LEFT, Time::deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		mainCamera.ProcessKeyboard(UP, Time::deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		mainCamera.ProcessKeyboard(DOWN, Time::deltaTime);


}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	float posX = (float)xposIn;
	float posY = (float)yposIn;
	float deltaX, deltaY;
	deltaX = posX - lastMouseX;
	deltaY = lastMouseY - posY;
	lastMouseX = posX;
	lastMouseY = posY;

	mainCamera.ProcessMouseMovement(deltaX, deltaY);
}
