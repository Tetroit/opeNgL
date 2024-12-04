#pragma once
#include "GameObject.h"
#include "LightManager.h"
#include "Skybox.h"

class Scene
{
public:
	static Scene* currentScene;
	std::string name;
	std::vector<std::unique_ptr<GameObject>> objects;
	std::vector<GameObject*> toDelete;

	LightManager lightManager;
	Skybox* skybox;

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

