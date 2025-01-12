#include "Scene.h"

#include <iostream>

#include "Core.h"

Scene* Scene::currentScene = nullptr;

Scene::Scene() {

	mainCamera = new Camera(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	mainCamera->SetProjection((float)glm::radians(45.0), (float)Core::width / (float)Core::height, 0.1f, 100.0f);
	objects.clear();
	toDelete.clear();
	utilizedRenderers.clear();
	if (currentScene == nullptr)
		currentScene = this;
}
Scene::~Scene() {
	for (int i = 0; i < objects.size(); i++)
		objects[i]->scene = nullptr;
	objects.clear();
	toDelete.clear();
	delete mainCamera;
}
void Scene::Render() {

	if (skybox != nullptr)
	{
		skybox->Render();
	}
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->parent == nullptr && objects[i])
			objects[i]->Render();
	}
}
void Scene::Update() {
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->parent == nullptr)
			objects[i]->Update();
	}
	DeleteObjects();
}
void Scene::AddObject(GameObject* go) {
	std::unique_ptr<GameObject> ptr(go);
	go->scene = this;
	go->OnSceneAdded(this);
	objects.push_back(std::move(ptr));
	for (GameObject* child : go->children)
		AddObject(child);
}
int Scene::FindObject(GameObject* go) {
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].get() == go)
			return i;
	}
	return -1;
}
void Scene::DeleteObjects()
{
	for (GameObject* go : toDelete)
	{
		go->OnSceneRemoved();
		int pos = FindObject(go);
		if (pos != -1)
			objects.erase(objects.begin() + pos);
		else {
			std::cout << "Scene::RemoveObject:\tobject not found\n";
			return;
		}
	}
	toDelete.clear();
}
void Scene::RemoveObject(GameObject* go) {

	for (int i = 0; i < toDelete.size(); i++)
	{
		if (toDelete[i] == go)
			return;
	}
	toDelete.push_back(go);
}