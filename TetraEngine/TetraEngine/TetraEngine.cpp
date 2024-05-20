#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "VertexData.h"
#include "Time.h"
#include "Camera.h"

extern void processInput(GLFWwindow* window);
extern void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
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

	Shader shader = Shader("shaders/vertexShader.glvs", "shaders/fragmentShader.glfs");

	VertexData vd = VertexData(0);
	Vertex vertices[] = {
		Vertex(-0.5f, -0.5f, 0.0f, /*color*/ 0.0f, 1.0f, 0.0f, /*uv*/ 0.0f, 0.0f),
		Vertex(0.5f, -0.5f, 0.0f, /*color*/ 0.0f, 0.0f, 1.0f, /*uv*/ 1.0f, 0.0f),
		Vertex(-0.5f,  0.5f, 0.0f,/*color*/ 1.0f, 0.0f, 0.0f, /*uv*/ 0.0f, 1.0f),
		Vertex(0.5f,  0.5f, 0.0f, /*color*/ 1.0f, 1.0f, 1.0f, /*uv*/ 1.0f, 1.0f),
	};

	vd.shader = &shader;

	unsigned int index[] = {
		0,1,2,
		1,2,3,
	};

	vd.LoadVerts(vertices, 4);
	vd.LoadFaces(index, 6);
	vd.Setup();

	glm::mat4 projectionView = glm::perspective((float)glm::radians(45.0), (float)width / (float)height, 0.1f, 100.0f);


	glm::mat4 cameraTransform = mainCamera.GetViewMatrix();
	vd.transform *= glm::mat4(1);

	while (!glfwWindowShouldClose(window))
	{
		Time::Update();
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		cameraTransform = mainCamera.GetViewMatrix();

		unsigned int ploc = glGetUniformLocation(shader.ID, "projection");
		glUniformMatrix4fv(ploc, 1, GL_FALSE, glm::value_ptr(projectionView));
		unsigned int loc = glGetUniformLocation(shader.ID, "view");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(cameraTransform));

		vd.Update();

		glfwSwapBuffers(window);
		glfwPollEvents();
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
