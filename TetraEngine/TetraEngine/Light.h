#pragma once
#include "MeshRenderer.h"
#include "GameObject.h"
#include "LightRenderer.h"

class Light : public GameObject
{
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	void Render() override;
	Light(glm::vec3 pos, const std::string name = "object", LightRenderer* meshRenderer = &LightRenderer::defaultRenderer);
	static Light* Create(glm::vec3 pos, const std::string name = "object", LightRenderer* meshRenderer = &LightRenderer::defaultRenderer);
};
