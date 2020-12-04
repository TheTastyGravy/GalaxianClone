#include "Enemy.h"
#include "EnemyProjectile.h"

Vector2 Enemy::formationVel;
Player* Enemy::player;


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
}


void Enemy::update(float deltaTime)
{
	//update formation position
	formationPos = Vector2Add(formationPos, Vector2Scale(formationVel, deltaTime));


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
				new EnemyProjectile(position, rotation, 300);
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

		//1 in 10 chance each second to attack
		int val = rand() % (int)(150 * (1/deltaTime));
		if (val == 1)
		{
			attacking = true;
		}
	}
}

void Enemy::draw()
{
	//update formation velocity after update
	if (formationPos.x > screenSize.x - 5)
	{
		formationVel.x = -abs(formationVel.x);
	}
	else if (formationPos.x < 5)
	{
		formationVel.x = abs(formationVel.x);
	}
	if (formationPos.y > screenSize.y - 5)
	{
		formationVel.y = -abs(formationVel.x);
	}
	else if (formationPos.y < 5)
	{
		formationVel.y = abs(formationVel.x);
	}


	DrawCircleV(position, 10, RED);

	//reverse rotation
	float val = 360 - rotation + 90;
	DrawCircleSector(position, 15, val + 30, val - 30, 4, DARKPURPLE);
}