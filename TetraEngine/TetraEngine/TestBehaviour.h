#pragma once
#include "Behaviour.h"
#include "Time.h"

class TestBehaviour : public Behaviour {
public:
	void Update() 
	{
		gameObject->transform[3][1] = sin(Time::time * 10);
		std::cout << gameObject->transform[3][1] << '\n';
	}
};