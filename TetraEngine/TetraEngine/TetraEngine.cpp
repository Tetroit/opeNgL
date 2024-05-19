#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "VertexData.h"
#include "Time.h"

extern void processInput(GLFWwindow* window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
int main()
{
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

	glfwMakeContextCurrent(window);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	VertexData vd = VertexData(0);
	Vertex vertices[] = {
		Vertex(-0.5f, -0.5f, 0.0f, /*color*/ 0.0f, 1.0f, 0.0f, /*uv*/ 0.0f, 0.0f),
		Vertex(0.5f, -0.5f, 0.0f, /*color*/ 0.0f, 0.0f, 1.0f, /*uv*/ 1.0f, 0.0f),
		Vertex(-0.5f,  0.5f, 0.0f,/*color*/ 1.0f, 0.0f, 0.0f, /*uv*/ 0.0f, 1.0f),
		Vertex(0.5f,  0.5f, 0.0f, /*color*/ 1.0f, 1.0f, 1.0f, /*uv*/ 1.0f, 1.0f),
	};

	unsigned int index[] = {
		0,1,2,
		1,2,3,
	};

	vd.LoadVerts(vertices, 4);
	vd.LoadFaces(index, 6);
	vd.Setup();

	while (!glfwWindowShouldClose(window))
	{
		Time::Update();
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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
}
