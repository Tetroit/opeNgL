#include "GameObject.h"

extern GameObject* parent;
extern VertexData* renderAs;
extern glm::mat4;

GameObject::GameObject(glm::vec3 pos)
{
	transform[0][3] = pos.x;
	transform[1][3] = pos.y;
	transform[2][3] = pos.z;
	
}
void GameObject::AddChild (GameObject* child)
{
	children.push_back(child);
	child->parent = this;
}
void GameObject::Render(Shader* shader)
{
	shader->Use();
	renderAs->Draw();
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