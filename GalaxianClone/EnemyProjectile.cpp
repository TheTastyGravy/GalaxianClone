#include "EnemyProjectile.h"
#include "GameObjectPool.h"
#include "Player.h"

EnemyProjectile::EnemyProjectile(Vector2 position, float rotation, float speed) :
	GameObject(position, rotation),
	timer(0)
{
	//velocity is speed in direction of rotation
	velocity = Vector2Rotate({ speed, 0 }, rotation);

}

EnemyProjectile::~EnemyProjectile()
{
}


void EnemyProjectile::update(float deltaTime)
{
	position = Vector2Add(position, Vector2Scale(velocity, deltaTime));

	//destroy projectile after 2 seconds
	timer += deltaTime;
	if (timer > 2)
	{
		delete this;
	}

		
	Player* player = static_cast<Player*>(GameObjectPool::searchForTag(Tag::Player)[0]);
	
	if (CheckCollisionPointRec(position, { player->getPos().x - 8, player->getPos().y - 10, 16, 20 }))
	{
		player->damage();
	}
}

void EnemyProjectile::draw()
{
	DrawCircleV(position, 3, WHITE);
}