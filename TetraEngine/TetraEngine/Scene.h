#pragma once
#include "GameObject.h"

class Scene
{
public:
	static Scene* currentScene;
	std::string name;
	std::vector<GameObject*> objects;

	Scene();
	void AddObject(GameObject*);
	void RemoveObject(int id);
	void Render();
	void Update();
};

