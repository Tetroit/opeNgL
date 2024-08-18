#pragma once
#include "Behaviour.h"
#include <glm/glm.hpp>
#include "Time.h"

class TestBehaviour : public Behaviour {
public:
	void Update() 
	{
		gameObject->transform = glm::rotate(gameObject->transform, Time::deltaTime, glm::vec3(0.1f, 0.2f, 0.3f));
	}
};