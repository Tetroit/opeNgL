#include "PointLight.h"
#include "Scene.h"

PointLight::PointLight(glm::vec3 pos, const std::string name, LightRenderer* meshRenderer) : Light(pos, name, meshRenderer)
{
	attenuation = glm::vec3(1,0,0);
}

void PointLight::OnSceneAdded(Scene* scene)
{

	lightId = scene->lightManager.AddPointLight(this);
	std::cout << "PointLight added to scene\n";
}
void PointLight::OnSceneRemoved()
{
	scene->lightManager.RemovePointLight(lightId);
	std::cout << "PointLight removed from scene\n";
}
