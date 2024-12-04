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
#include "TestBehaviour.h"
#include "FreeType.h"
#include "Bullet.h"
#include "Enemy.h"

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
	if (FreeType::Initialise()) std::cout<<"freetype initialised successfully\n";
	Shader::InitialiseShaders();
	VertexData::InitialisePrefabs();
	MeshRenderer::InitialiseRenderer();
	LightRenderer::InitialiseRenderer();
	Material::Initialize();
}
void Shoot(GameObject* ship, MeshRenderer* bullet, glm::vec3 velocity = glm::vec3(1,0,0), glm::vec3 offset = glm::vec3(0,0,0)) {
	glm::vec3 pos = ship->TransformPoint(offset);
	glm::vec3 dir = glm::normalize(ship->TransformDirection(velocity));

	GameObject* instance = new GameObject(pos, "bullet", bullet);
	Bullet* script = new Bullet();
	script->velocity = velocity;
	instance->AddBehaviour(script);

	instance->LocalRotate(glm::rotation(glm::normalize(velocity), dir));
	instance->LocalScale(glm::vec3(0.4f, 0.04f, 0.04f));
	instance -> UpdateMatrix();

	std::cout << instance->GetGlobalPos().x << " " << instance->GetGlobalPos().y << " " << instance->GetGlobalPos().z << " " << '\n';
	ship->scene->AddObject(instance);
}

Camera mainCamera = Camera(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
float lastMouseX, lastMouseY;
bool cursorEnabled;
bool LMBpressed = false;
GLFWwindow* window;
ImGuiIO* io;

int main()
{
	static unsigned int width = 1920;
	static unsigned int height = 1080;
	std::srand(time(NULL));
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(1920, 1080, "showcase", NULL, NULL);
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
	myScene.skybox = new Skybox(Skybox::BOX, "assets/skybox");
	Skybox::current = myScene.skybox;
	Shader shader = Shader("shaders/lit.glvs", "shaders/lit.glfs");
	shader.Use();

	std::shared_ptr<VertexData> ship = VertexData::LoadFromFile("assets/meshes/ship.obj");

	MeshRenderer shipRenderer(ship, &shader);
	PointLight* light1 = new PointLight(glm::vec3(0, 0, 5), "l1");
	light1->diffuse = glm::vec3(0.1f, 1, 0.7f);
	light1->specular = light1->diffuse * 0.3f;
	light1->ambient = light1->diffuse* 0.0f;
	myScene.lightManager.AddPointLight(light1);
	PointLight* light2 = new PointLight(glm::vec3(0, 0, -5), "l1");
	light2->diffuse = glm::vec3(1, 0.7f, 0.1f);
	light2->specular = light2->diffuse * 0.3f;
	light2->ambient = light2->diffuse * 0.0f;
	myScene.lightManager.AddPointLight(light2);
	//MeshRenderer enemyRenderer = MeshRenderer(VertexData::GetPrefab(ship), &shader);
	//MeshRenderer bullet = MeshRenderer(VertexData::GetPrefab(VD_CUBE), &shader);

	Texture2D specularTex;
	Texture2D diffuseTex;
	Texture2D ambientTex;
	ambientTex.Load("assets/ship/ambient.png", true);
	diffuseTex.Load("assets/ship/diffuse.png", true);
	specularTex.Load("assets/ship/specular.png", true);

	auto player = GameObject::Create(glm::vec3(0, 0, 0), "ship", &shipRenderer);

	//monke1->Rotate(glm::angleAxis(45.0f, glm::vec3(10, 10, 10)));
	player->LocalScale(glm::vec3(0.5f, 0.5f, 0.5f));
	shipRenderer.setTexture(&diffuseTex, 1);
	shipRenderer.setTexture(&specularTex, 2);
	shipRenderer.setTexture(&ambientTex, 4);

	//enemyRenderer.setTexture(&diffuseTex, 1);
	//enemyRenderer.setTexture(&specularTex, 2);
	//enemyRenderer.setTexture(&ambientTex, 4);
	myScene.AddObject(player);
	myScene.AddObject(light1);
	myScene.AddObject(light2);

	//Material emissive = Material(glm::vec3(0, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 1), "emissive");
	Material shipMaterial = Material(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), "ship");
	//Material enemyMaterial = Material(glm::vec3(0.5f, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), "ship");
	//bullet.material = &emissive;
	player->renderer->material = &shipMaterial;
	//enemyRenderer.material = &enemyMaterial;

	mainCamera.SetProjection((float)glm::radians(45.0), (float)width / (float)height, 0.1f, 100.0f);

	std::thread consoleThread(processConsole);
	//player->GlobalRotate(glm::angleAxis(1.f, glm::normalize(glm::vec3(0, 1, 1))));
	
	//float cooldown = 1.0f;
	//float enemyCooldown = 1.0f;
	//int score = 0;

	while (!glfwWindowShouldClose(window))
	{
		Time::Update();
		//cooldown -= Time::deltaTime;
		//enemyCooldown -= Time::deltaTime;
		processInput(window);
		Scene::currentScene->Update();

		if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
		{
			ImGui_ImplGlfw_Sleep(10);
			continue;
		}

		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		player->LocalRotate(glm::angleAxis(Time::sdeltaTime/3, glm::vec3(0, 1, 0)));
		/*glm::vec3 targetPos = glm::vec3(5, -lastMouseY / 500, lastMouseX / 500);
		glm::vec3 newPos = Utils::Lerp(player->GetPos(), targetPos, 3*Time::sdeltaTime);
		glm::vec3 velocity = (newPos - player->GetPos())/Time::sdeltaTime;
		std::cout << velocity.x << " " << velocity.y << " " << velocity.z << '\n';
		player->SetPosition(newPos);
		mainCamera.Position = glm::vec3(0, newPos.y/5, newPos.z / 5);
		player->SetRotation(glm::quatLookAt(
			glm::normalize(glm::vec3(0, velocity.z/15, -1)), 
			glm::normalize(glm::vec3(velocity.y/15, 1, 0)))
		);

		if (cooldown < 0 && LMBpressed)
		{
			Shoot(player, &bullet, glm::vec3(40.f, 0, 0), glm::vec3(10, 0, 0));
			cooldown = 0.2f;
		}
		if (enemyCooldown < 0)
		{
			glm::vec3 pos(
				10,
				Utils::frand() * 3.f - 1.5f,
				Utils::frand() * 6.f - 3.f
			);
			GameObject* enemy = new GameObject(pos, "enemy", &enemyRenderer);
			enemy->AddBehaviour(new Enemy(score));
			enemy->GlobalScale(glm::vec3(0.03f, 0.03f, 0.03f));
			enemy->LocalRotate(glm::angleAxis(glm::pi<float>(), glm::vec3(0, 1, 0)));
			myScene.AddObject(enemy);
			enemyCooldown = 1.f;
		}*/

		shader.Use();
		shader.SetVec3("viewPos", mainCamera.Position);

		myScene.lightManager.fetchPointLights(&shader);

		Scene::currentScene->Render();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Shader::textShader->Use();
		glm::mat4 proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height);
		Shader::textShader->SetMat4("projection", proj);

		//FreeType::RenderText("score:" + std::to_string(score), 100.0f, 1000.0f, 1.0f, glm::vec3(1, 1, 1));

		glfwSwapBuffers(window);
		glfwPollEvents();

		DestroyManager::get()->deleteAll();
		//Sleep(10);
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
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		LMBpressed = true;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		LMBpressed = false;
}
