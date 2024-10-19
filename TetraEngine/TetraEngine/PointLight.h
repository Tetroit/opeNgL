#pragma once
#include "Light.h"

class LightManager;
class Scene;

class PointLight : public Light
{
public:
	int lightId = 0;
	PointLight(glm::vec3 pos, const std::string name = "object", LightRenderer* meshRenderer = &LightRenderer::defaultRenderer);
	glm::vec3 attenuation;
	void OnSceneAdded(Scene* scene) override;
	void OnSceneRemoved() override;
};

