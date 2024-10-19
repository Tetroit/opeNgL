#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "MeshRenderer.h"
#include "Behaviour.h"

class Scene;


class GameObject
{
private:
	static glm::mat4 currentTransform;
public:
	std::string name;
	glm::mat4 transform;
	Scene* scene;
	GameObject* parent;
	MeshRenderer* renderer = &MeshRenderer::defaultRenderer;
	std::vector<GameObject*> children;
	std::vector<Behaviour*> scripts;

	GameObject(glm::vec3 pos, const std::string name = "object", MeshRenderer* meshRenderer = &MeshRenderer::defaultRenderer);
	~GameObject();

	static GameObject* Create(glm::vec3 pos, const std::string name = "object", MeshRenderer* meshRenderer = &MeshRenderer::defaultRenderer);
	void Rename(const std::string);
	void AddChild(GameObject* child);
	void AddBehaviour(Behaviour* script);
	virtual void OnSceneAdded(Scene* scene);
	virtual void OnSceneRemoved();
	virtual void Render();
	void Update();
	void getGlobalPos();
	glm::vec3 getPos();
};

