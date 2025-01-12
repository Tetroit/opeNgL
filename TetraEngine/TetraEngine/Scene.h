#pragma once

#include "LightManager.h"
#include <string>
#include <memory>

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
	std::vector<Shader*> utilizedRenderers;

	LightManager lightManager;
	Skybox* skybox;
	Camera* mainCamera = nullptr;

	Scene();
	~Scene();
	void AddObject(GameObject* go);
	void RemoveObject(GameObject* go);
	void Render();
	void Update();
	int FindObject(GameObject*);

private:
	
	void DeleteObjects();
};

