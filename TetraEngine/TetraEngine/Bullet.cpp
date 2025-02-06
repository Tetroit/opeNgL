#include "tetrapc.h"
#include "Bullet.h"
#include "GameObject.h"
#include "Time.h"

Bullet::Bullet() : Behaviour("bullet") {};

void Bullet::Start()
{}
void Bullet::Update()
{
	gameObject->LocalTranslate(velocity * Time::deltaTime);
	lifetime -= Time::deltaTime;
	if (lifetime < 0)
		gameObject->Delete();
}
