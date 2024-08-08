#include "GameObject.h"

glm::mat4 GameObject::currentTransform;
extern glm::mat4 transform;
extern GameObject* parent;
extern MeshRenderer renderer;

GameObject::GameObject(glm::vec3 pos)
{
	parent = nullptr;
	transform = glm::mat4(1);
	transform[3][0] = pos.x;
	transform[3][1] = pos.y;
	transform[3][2] = pos.z;
}
GameObject::GameObject(glm::vec3 pos, MeshRenderer* meshRenderer)
{
	parent = nullptr;
	transform = glm::mat4(1);
	renderer = meshRenderer;
	transform[3][0] = pos.x;
	transform[3][1] = pos.y;
	transform[3][2] = pos.z;
}
void GameObject::AddChild (GameObject* child)
{
	children.push_back(child);
	child->parent = this;
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