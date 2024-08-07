#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "MeshRenderer.h"

class GameObject
{
public:
	static glm::mat4 currentTransform;
	glm::mat4 transform;
	GameObject* parent;
	MeshRenderer* renderer = &MeshRenderer::defaultRenderer;
	std::vector<GameObject*> children;
	GameObject(glm::vec3 pos);
	GameObject(glm::vec3 pos, MeshRenderer* meshRenderer);
	void AddChild(GameObject* child);
	void Render();
	void getGlobalPos();
	glm::vec3 getPos();
};

