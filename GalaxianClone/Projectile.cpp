#include "Projectile.h"
#include "GameObjectPool.h"
#include "Player.h"


Projectile::Projectile(Vector2 position, float rotation, float speed, GameObject* player) :
	GameObject(position, rotation),
	timer(0),
	enabled(false),
	player(player)
{
	//velocity is speed in direction of rotation
	velocity = Vector2Rotate({ speed, 0 }, rotation);
}

Projectile::~Projectile()
{
}


void Projectile::update(float deltaTime)
{
	if (!enabled)
	{
		return;
	}

	//move
	position = Vector2Add(position, Vector2Scale(velocity, deltaTime));

	//destroy projectile after 5 seconds
	timer += deltaTime;
	if (timer > 2.5f)
	{
		timer = 0;
		enabled = false;
	}


	//check for collision for enemies
	std::vector<GameObject*> enemies = GameObjectPool::searchForTag(Tag::Enemy);

	for (int i = 0; i < enemies.size(); i++)
	{
		if (CheckCollisionPointCircle(position, enemies[i]->getPos(), 16))
		{
			delete enemies[i];
			enabled = false;
			timer = 0;

			static_cast<Player*>(player)->addScore(100);
		}
	}
}

void Projectile::draw()
{
	if (enabled)
	{
		DrawCircleV(position, 3, WHITE);
	}
}