#pragma once
#include <functional>

class Behaviour
{
	friend class GameObject;

public:
	
	GameObject* gameObject;

	Behaviour();
	virtual void Update();
};

