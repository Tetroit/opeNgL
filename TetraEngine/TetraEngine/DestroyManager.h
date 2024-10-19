#pragma once

#include "GameObject.h"
#include <queue>

class DestroyManager
{
public:
	static DestroyManager* get();
	std::queue<GameObject*> toDelete;
	void clear();
	void deleteAll();
	void push(GameObject* go);

};

