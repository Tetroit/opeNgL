#pragma once
#include "Behaviour.h"
class Enemy : public Behaviour
{
	bool CheckCollision(GameObject* other);
	int& score;
	float lifetime = 5.f;
public:
	Enemy(int& score);
	void Start();
	void Update();
};

