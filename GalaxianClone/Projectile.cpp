#include "Projectile.h"


Projectile::Projectile(Vector2 position, float rotation, float speed) :
	GameObject(position, rotation),
	timer(0)
{
	//velocity is speed in direction of rotation
	velocity = Vector2Rotate({ speed, 0 }, rotation);
}

Projectile::~Projectile()
{
}


void Projectile::update(float deltaTime)
{
	//move
	position = Vector2Add(position, Vector2Scale(velocity, deltaTime));

	//destroy projectile after 5 seconds
	timer += deltaTime;
	if (timer > 5)
	{
		delete this;
	}
}

void Projectile::draw()
{
	DrawCircleV(position, 3, WHITE);
}