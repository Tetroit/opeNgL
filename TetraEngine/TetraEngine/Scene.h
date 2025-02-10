#pragma once

#include "LightManager.h"
#include <string>
#include <memory>
#include <map>

class Skybox;
class GameObject;
class Camera;
class Shader;

class Scene
{
public:
	static Scene* currentScene;

	std::string name;
	std::vector<std::unique_ptr<GameObject>> objects;
	std::vector<GameObject*> toDelete;
	std::map<Shader*, int> utilizedShaders;

	LightManager lightManager;
	Skybox* skybox = nullptr;
	Camera* cameraContext = nullptr;

	Scene();
	~Scene();
	void AddObject(GameObject* go);
	void RemoveObject(GameObject* go);
	void RegisterShader(Shader* shader);
	void DeregisterShader(Shader* shader);
	void SetGlobalShaderData();
	void Render(Camera* cam);
	void Render();
	void Update();
	int FindObject(GameObject*);

private:
	
	void DeleteObjects();
};

