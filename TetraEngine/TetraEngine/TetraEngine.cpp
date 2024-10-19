#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <thread>

#include "Time.h"
#include "Scene.h"
#include "ConsoleManager.h"
#include "TestBehaviour.h"

extern void processInput(GLFWwindow* window);
extern void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
extern void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
extern void processConsole();

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void InitialisePresets()
{
	Shader::InitialiseShaders();
	VertexData::InitialisePrefabs();
	MeshRenderer::InitialiseRenderer();
	LightRenderer::InitialiseRenderer();
	Material::Initialize();
}

Camera mainCamera = Camera(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
float lastMouseX, lastMouseY;
bool cursorEnabled;
GLFWwindow* window;
ImGuiIO* io;

int main()
{
	static unsigned int width = 1920;
	static unsigned int height = 1080;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(1920, 1080, "some random shit idk", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	if (!cursorEnabled)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(window);
	ConsoleManager::Initialize(window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls


	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
	ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
	ImGui_ImplOpenGL3_Init("#version 460");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	InitialisePresets();

	Scene myScene;
	myScene.skybox = new Skybox(Skybox::BOX, "Assets/skybox");
	Skybox::current = myScene.skybox;
	Shader shader = Shader("shaders/lit.glvs", "shaders/lit.glfs");
	shader.Use();

	//GameObject cube1(glm::vec3(5, 0, 0), "square2");
	//GameObject cube2(glm::vec3(0, 5, 0), "square3");
	//GameObject cube3(glm::vec3(0, 0, 5), "square4");

	//light.AddChild(&cube1);
	//cube1.AddChild(&cube2);
	//cube2.AddChild(&cube3);

	OBJParser::OBJRead("Assets/meshes/materials.obj");
	Material::ParseMTL("Assets/meshes/materials.mtl");

	MeshRenderer renderer3D = MeshRenderer(VertexData::GetPrefab(VD_SUZANNE), &shader);
	//renderer3D.setTexture("Assets/debug.jpeg");

	auto monke1 = GameObject::Create(glm::vec3(1, 1, 1), "monke1", &renderer3D);
	auto monke3 = GameObject::Create(glm::vec3(-1, -1, -3), "monke3", &renderer3D);
	/*auto pointLight1 = new PointLight(glm::vec3(2, 0, 0), "pl");
	auto pointLight2 = new PointLight(glm::vec3(0, 0, 2), "pl");
	auto pointLight3 = new PointLight(glm::vec3(-2, 0, 0), "pl");
	auto pointLight4 = new PointLight(glm::vec3(0, 0, -2), "pl");*/

	myScene.AddObject(monke1);
	myScene.AddObject(monke3);
	/*myScene.AddObject(pointLight1);
	myScene.AddObject(pointLight2);
	myScene.AddObject(pointLight3);
	myScene.AddObject(pointLight4);*/

	Texture2D specularTex;
	specularTex.Load("Assets/container_specular.png");

	monke1->renderer->material = &Material::collection[0];
	//monke1->renderer->setTexture("Assets/container.png");
	monke1->renderer->setTexture(&specularTex, 2);

	monke3->renderer->material = &Material::collection[0];
	//monke3->renderer->setTexture("Assets/container.png");
	monke3->renderer->setTexture(&specularTex, 2);

	/*pointLight1->diffuse = glm::vec3(0.1, 1, 1);
	pointLight1->attenuation = glm::vec3(1, 0.09, 0.03);
	pointLight2->diffuse = glm::vec3(1, 1, 0.1);
	pointLight2->attenuation = glm::vec3(1, 0.09, 0.03);
	pointLight3->diffuse = glm::vec3(1, 0.1, 0.1);
	pointLight3->attenuation = glm::vec3(1, 0.09, 0.03);
	pointLight4->diffuse = glm::vec3(0.1, 1, 0.1);
	pointLight4->attenuation = glm::vec3(1, 0.09, 0.03);*/

	//Texture2D emissionTex;
	//emissionTex.Load("Assets/matrix.jpg");
	//monke1->renderer->setTexture(&emissionTex, 4);


	//monke1.reset();

	mainCamera.SetProjection((float)glm::radians(45.0), (float)width / (float)height, 0.1f, 100.0f);

	std::thread consoleThread(processConsole);

	//ConsoleManager::PrintMatrix(mainCamera.projectionView);
	bool show_demo_window = true;
	bool show_another_window = true;
	while (!glfwWindowShouldClose(window))
	{
		Time::Update();
		processInput(window);

		Scene::currentScene->Update();

		if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
		{
			ImGui_ImplGlfw_Sleep(10);
			continue;
		}
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		ImGui::Render();

		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//box.Render();
		//renderer2D.Render();
		shader.Use();
		//std::cout << lightPos.x << ' ' << lightPos.y << ' ' << lightPos.z << '\n';
		shader.SetVec3("viewPos", mainCamera.Position);

		myScene.lightManager.fetchPointLights(&shader);

		Scene::currentScene->Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();

		DestroyManager::get()->deleteAll();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	consoleThread.detach();
	consoleThread.~thread();
	glfwTerminate();
	return 0;
}

void processConsole() {

	std::string command;
	while (!glfwWindowShouldClose(window))
	{
		std::getline(std::cin, command);
		ConsoleManager::ParseCommand(command);
	}
}

void processInput(GLFWwindow* window)
{
	if (!io->WantCaptureKeyboard && !io->WantTextInput) {
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

}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {

	//ImGui_ImplGlfw_CursorPosCallback(window, xposIn, yposIn);
	if (!io->WantCaptureMouse)
	{
		float posX = (float)xposIn;
		float posY = (float)yposIn;
		float deltaX, deltaY;
		deltaX = posX - lastMouseX;
		deltaY = lastMouseY - posY;
		lastMouseX = posX;
		lastMouseY = posY;

		mainCamera.ProcessMouseMovement(deltaX, deltaY);
	}
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, (cursorEnabled = !cursorEnabled) ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}
