#include "Scene.h"

Scene* Scene::currentScene = nullptr;

Scene::Scene() {
	objects.clear();
	if (currentScene == nullptr)
		currentScene = this;
}
Scene::~Scene() {
	for (int i = 0; i < objects.size(); i++)
		objects[i]->scene = nullptr;
	objects.clear();
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
}
void Scene::AddObject(GameObject* go) {
	std::unique_ptr<GameObject> ptr(go);
	go->scene = this;
	go->OnSceneAdded(this);
	objects.push_back(std::move(ptr));
}
int Scene::FindObject(GameObject* go) {
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].get() == go)
			return i;
	}
	return -1;
}
void Scene::RemoveObject(GameObject* go) {

	go->OnSceneRemoved();
	int pos = FindObject(go);
	if (pos != -1)
		objects.erase(objects.begin() + pos);
	else {
		std::cout << "Scene::RemoveObject:\tobject not found\n";
		return;
	}
}