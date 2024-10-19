#include "GameObject.h"
#include "Scene.h"

glm::mat4 GameObject::currentTransform = glm::mat4(1);

GameObject::GameObject(glm::vec3 pos, const std::string name, MeshRenderer* meshRenderer)
{
	this->name = name;
	parent = nullptr;
	scene = nullptr;
	transform = glm::mat4(1);
	renderer = meshRenderer;
	transform[3][0] = pos.x;
	transform[3][1] = pos.y;
	transform[3][2] = pos.z;
}
GameObject::~GameObject() {
	std::cout << name << " destroyed\n";
}
void GameObject::AddChild (GameObject* child)
{
	children.push_back(child);
	child->parent = this;
}

GameObject* GameObject::Create(glm::vec3 pos, const std::string name, MeshRenderer* meshRenderer) {
	GameObject* ptr = new GameObject(pos, name, meshRenderer);
	return ptr;
}
void GameObject::AddBehaviour(Behaviour* script) {
	scripts.push_back(script);
	script->gameObject = this;
}

void GameObject::Render()
{
	GameObject::currentTransform *= transform;
	renderer->Render(GameObject::currentTransform);
	for (GameObject* go : children) {
		go->Render();
	}
	GameObject::currentTransform *= glm::inverse(transform);
}
void GameObject::Update() {
	for (int i = 0; i < scripts.size(); i++)
	{
		scripts[i]->Update();
	}
	for (int i = 0; i < children.size(); i++) 
	{
		children[i]->Update();
	}
}
void GameObject::OnSceneAdded(Scene* scene)
{
	std::cout << "Object added to scene\n";
}
void GameObject::OnSceneRemoved()
{
	std::cout << "Object removed from scene\n";
}
void GameObject::getGlobalPos()
{
	GameObject* par = parent;
	glm::mat4 global = transform;
	while (par != nullptr)
	{
		global *= glm::inverse(par->transform);
		par = par->parent;
	}
}

glm::vec3 GameObject::getPos() {
	return glm::vec3(transform[3][0], transform[3][1], transform[3][2]);
}