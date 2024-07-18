#include "GameObject.h"

extern GameObject* parent;
extern MeshRenderer renderer;
extern glm::mat4;

GameObject::GameObject(glm::vec3 pos)
{
	transform = glm::mat4(1);
	transform[3][0] = pos.x;
	transform[3][1] = pos.y;
	transform[3][2] = pos.z;
}
GameObject::GameObject(glm::vec3 pos, MeshRenderer* meshRenderer)
{
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
	renderer->Render(transform);
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