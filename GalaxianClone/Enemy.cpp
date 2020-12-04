#include "Enemy.h"
#include "EnemyProjectile.h"
#include "GameObjectPool.h"

Player* Enemy::player;
float Enemy::randShoot;
float Enemy::randAttack;
bool Enemy::isAttacking;


Enemy::Enemy(Vector2 position, float rotation, Vector2 screenSize) :
	GameObject(position, rotation),
	screenSize(screenSize),
	attacking(false),
	attackPhase(0),
	formationPos(position),
	attackVel({ 0, 0 }),
	shootTimer(0)
{
	addTag(Tag::Enemy);
}

Enemy::~Enemy()
{
	if (attacking)
	{
		Enemy::isAttacking = false;
	}
}


void Enemy::draw()
{
	DrawCircleV(position, 13, RED);

	//reverse rotation
	float val = 360 - rotation + 90;
	DrawCircleSector(position, 17, val + 30, val - 30, 4, DARKPURPLE);
}

void Enemy::update(float deltaTime)
{
	if (attacking)
	{
		//*****move toward player
		if (attackPhase == 0)
		{
			// find the direction currently being faced
			Vector2 thing = Vector2Rotate({ 1, 0 }, rotation);
			//angle between velocity and the direction of the player
			float newRot = Vector2Angle(thing, Vector2Subtract(player->getPos(), position)) ;

			//get change in rot and clamp to prevent sharp turns
			newRot -= rotation;
			newRot = Clamp(newRot, -10, 10);
			//scale by delta time and multiply to increase turn speed
			newRot *= deltaTime * 4;
			rotation += newRot;

			attackVel = Vector2Rotate({ 200, 0 }, rotation);


			//shoot at player
			shootTimer += deltaTime;
			if (shootTimer > 1)
			{
				shoot();
				shootTimer = 0;
			}


			//next phase is past player
			if (position.y >= player->getPos().y - 10)
			{
				attackPhase++;
			}
		}
		//*****disapear off screen and reappear above
		else if (attackPhase == 1)
		{
			//make it face downwards
			float newRot = 90;

			//get change in rot and clamp
			newRot -= rotation;
			newRot = Clamp(newRot, -15, 15);

			newRot *= deltaTime * 4;
			rotation += newRot;

			attackVel = Vector2Rotate({ 200, 0 }, rotation);


			//once off screen, move back to top
			if (position.y > screenSize.y)
			{
				position.y = 0;
				attackPhase++;
			}
		}
		//*****rejoin formation
		else if (attackPhase == 2)
		{
			// find the direction currently being faced
			Vector2 thing = Vector2Rotate({ 1, 0 }, rotation);
			//angle between velocity and the direction of the player
			float newRot = Vector2Angle(thing, Vector2Subtract(formationPos, position));

			//get change in rot
			newRot -= rotation;
			newRot = Clamp(newRot, -30, 30);
			//scale by delta time and multiply to increase turn speed
			newRot *= deltaTime * 15;
			rotation += newRot;

			attackVel = Vector2Rotate({ 250, 0 }, rotation);


			//if close to formation position, reenter formation
			if (Vector2Distance(position, formationPos) <= 20)
			{
				attackPhase = 0;
				attackVel = Vector2Zero();
				attacking = false;
				rotation = 90;
				shootTimer = 0;

				Enemy::isAttacking = false;
			}
		}


		//apply velocity
		position = Vector2Add(position, Vector2Scale(attackVel, deltaTime));

		//check if the enemy has hit the player
		if (CheckCollisionCircleRec(position, 10, { player->getPos().x, player->getPos().y, 13, 10 }))
		{
			player->damage();
		}
	}
	else
	{
		position = formationPos;
	}
}

void Enemy::shoot()
{
	new EnemyProjectile(position, rotation, 300);
}


void Enemy::updateEnemies(float deltaTime)
{
	randShoot += deltaTime;
	if (!isAttacking)
	{
		randAttack += deltaTime;
	}
	

	//random float between 0 and 50
	float randVal1 = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 50));
	float randVal2 = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 100));

	if (randVal1 < randShoot)
	{
		std::vector<GameObject*> enemies = GameObjectPool::searchForTag(Tag::Enemy);

		//make random enemy shoot
		static_cast<Enemy*>(enemies[rand() % enemies.size()])->shoot();

		randShoot = 0;
	}

	if (randVal2 < randAttack && !isAttacking)
	{
		std::vector<GameObject*> enemies = GameObjectPool::searchForTag(Tag::Enemy);

		//make random enemy attack
		static_cast<Enemy*>(enemies[rand() % enemies.size()])->attacking = true;

		isAttacking = true;

		randAttack = 0;
	}
}