#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Shader.h"
#include "VertexData.h"

class GameObject
{
public:
	glm::mat4 transform;
	GameObject* parent;
	VertexData* renderAs;
	std::vector<GameObject*> children;
	GameObject(glm::vec3 pos);
	void AddChild(GameObject* child);
	void Render(Shader* shader);
	void getGlobalPos();
};

