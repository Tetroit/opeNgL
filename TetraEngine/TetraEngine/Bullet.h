#pragma once
#include <glm/glm.hpp>
#include "Behaviour.h"
class Bullet : public Behaviour
{
	void Update();
	void Start();

public:

	Bullet();
	glm::vec3 velocity = glm::vec3(1,0,0);
	float lifetime = 5;
};

