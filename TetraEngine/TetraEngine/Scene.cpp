#include "Scene.h"

Scene* Scene::currentScene = nullptr;

Scene::Scene() {
	objects.clear();
	if (currentScene == nullptr)
		currentScene = this;
}
void Scene::Render() {
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->parent == nullptr)
			objects[i]->Render();
	}
}
void Scene::Update() {
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->parent == nullptr)
			objects[i]->Update();
	}
}
void Scene::AddObject(GameObject* go) {
	objects.push_back(go);
}
void Scene::RemoveObject(int id) {
	objects.erase(objects.begin() + id);
}