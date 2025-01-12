
#include "Core.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	if (Core::Initialize() != 0)
		return -1;

	Scene myScene;
	myScene.skybox = new Skybox(Skybox::BOX, "assets/skybox");
	Skybox::current = myScene.skybox;
	Shader shader = Shader("shaders/lit.glvs", "shaders/lit.glfs");
	shader.Use();

	int shipID = OBJParser::OBJRead("assets/meshes/ship.obj");
	std::shared_ptr<VertexData> ship = VertexData::GetPrefab(shipID);

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

	std::thread consoleThread(Core::processConsole);
	//player->GlobalRotate(glm::angleAxis(1.f, glm::normalize(glm::vec3(0, 1, 1))));
	
	//float cooldown = 1.0f;
	//float enemyCooldown = 1.0f;
	//int score = 0;

	while (!glfwWindowShouldClose(Core::window))
	{
		Core::Update();
		
		player->LocalRotate(glm::angleAxis(Time::sdeltaTime/3, glm::vec3(0, 1, 0)));

		shader.Use();
		shader.SetVec3("viewPos", Scene::currentScene->mainCamera->Position);

		Scene::currentScene->lightManager.fetchPointLights(&shader);
		Scene::currentScene->Render();

		Core::UpdateOverlay();
		Core::AfterUpdate();
		//Sleep(10);
	}


	consoleThread.detach();
	consoleThread.~thread();
	Core::CleanUp();

	return 0;
}
