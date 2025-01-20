#include "Core.h"
#include "MyApplication.h"
#include "Event.h"
#include <iostream>

ImGuiIO* Core::io = nullptr;

unsigned int Core::width = 1920;
unsigned int Core::height = 1080;

float Core::lastMouseX;
float Core::lastMouseY;

bool Core::cursorEnabled = false;

Application* Core::application = nullptr;
GLFWContext* Core::glfwContext = nullptr;
InputManager* Core::inputManager = nullptr;

void Core::processConsole() {

	std::string command;
	while (!glfwWindowShouldClose(glfwContext->window))
	{
		std::getline(std::cin, command);
		ConsoleManager::ParseCommand(command);
	}
}

void Core::CloseApplication(const Event<KeyInfo>& ev) {

	if (ev.GetType().bits.any) return;
	KeyEvent keyEvent = ev.ToType<KeyEvent>();

	if (ev.GetType().bits.key == GLFW_KEY_ESCAPE 
	&& ev.GetType().bits.action == GLFW_PRESS)
		glfwSetWindowShouldClose(glfwContext->window, true);
}
void Core::processInput(GLFWwindow* window)
{
	if (!io->WantCaptureKeyboard && !io->WantTextInput) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			Scene::currentScene->mainCamera->ProcessKeyboard(FORWARD, Time::deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			Scene::currentScene->mainCamera->ProcessKeyboard(BACKWARD, Time::deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			Scene::currentScene->mainCamera->ProcessKeyboard(RIGHT, Time::deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			Scene::currentScene->mainCamera->ProcessKeyboard(LEFT, Time::deltaTime);
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			Scene::currentScene->mainCamera->ProcessKeyboard(UP, Time::deltaTime);
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			Scene::currentScene->mainCamera->ProcessKeyboard(DOWN, Time::deltaTime);
	}

}


void foo(const Event<KeyInfo>& ev)
{
	std::cout << ev.GetName() << '\n';
	std::cout << (int)ev.GetType().bits.key << '\n';
};


class MyClass {
public:
	void handleEvent(const Event<KeyInfo>& ev) {
		std::cout << "Member Function Handling event with data: " << ev.GetType().raw << '\n';
	}
};

int Core::Initialize()
{

	std::srand(time(NULL));

	inputManager = new InputManager();

	MyClass test;
	//inputManager->keyDispatcher.AddListener<MyClass>(KeyInfo(GLFW_KEY_ESCAPE, GLFW_PRESS), &MyClass::handleEvent, test);

	SET_KEY_EVENT(MyClass, KeyInfo(GLFW_KEY_ESCAPE, GLFW_PRESS), handleEvent, test);

	glfwContext = new GLFWContext(1920, 1080);
	glfwContext->inputManager = inputManager;

	//window

	ConsoleManager::Initialize(glfwContext->window);

	//opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	//imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls


	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(glfwContext->window, true);
#ifdef __EMSCRIPTEN__
	ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
	ImGui_ImplOpenGL3_Init("#version 460");

	//presets
	Core::InitializePresets();

	return 0;
}

void Core::InitializePresets()
{
	if (FreeType::Initialise()) std::cout << "freetype initialised successfully\n";
	Shader::InitialiseShaders();
	std::cout << "shaders initialized\n";
	VertexData::InitialisePrefabs();
	std::cout << "models initialized\n";
	MeshRenderer::InitialiseRenderer();
	LightRenderer::InitialiseRenderer();
	std::cout << "renderers initialized\n";
	Material::Initialize();
	std::cout << "materials initialized\n";
}


void Core::Update()
{

	Time::Update();
	Core::processInput(Core::glfwContext->window);
	inputManager->UpdateKeys();
	Scene::currentScene->Update();

	if (glfwGetWindowAttrib(Core::glfwContext->window, GLFW_ICONIFIED) != 0)
	{
		ImGui_ImplGlfw_Sleep(10);
	}

	int display_w, display_h;
	glfwGetFramebufferSize(Core::glfwContext->window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	application->Update();

	Scene::currentScene->Render();

}
void Core::UpdateOverlay()
{
	//transparent render

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//overlay

	glm::mat4 proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height);
	Shader::textShader->Use();
	Shader::textShader->SetMat4("projection", proj);
}
void Core::AfterUpdate()
{
	glfwSwapBuffers(glfwContext->window);
	glfwPollEvents();

	DestroyManager::get()->deleteAll();
}
void Core::CleanUp() {

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	delete application;
	delete glfwContext;
	delete inputManager;
}
