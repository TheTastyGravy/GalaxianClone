#include "Enemy.h"

Vector2 Enemy::formationVel;
GameObject* Enemy::player;


Enemy::Enemy(Vector2 position, float rotation, Vector2 screenSize) :
	GameObject(position, rotation),
	screenSize(screenSize),
	attacking(false),
	attackPhase(0),
	formationPos(position),
	attackVel({ 0, 0 })
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
			Vector2 desieredVel{ 0, 0 };
			Vector2 force{ 0, 0 };

			// Get the diference in position to find the heading
			desieredVel = Vector2Subtract(player->getPos(), position);
			// If non-zero, normalise
			if (desieredVel.x != 0.0f && desieredVel.y != 0.0f)
				desieredVel = Vector2Normalize(desieredVel);
			// Multiply the heading by the max speed to get desiered velocity
			desieredVel = Vector2Scale(desieredVel, 200);


			// Find the force nessesary to change the velocity
			force = Vector2Subtract(desieredVel, attackVel);
			// If non-zero, normalise to the base value
			if (force.x != 0.0f && force.y != 0.0f)
			{
				force = Vector2Normalize(force);
				force = Vector2Scale(force, 100);
			}

			//apply force
			attackVel = Vector2Add(attackVel, Vector2Scale(force, deltaTime));


			//next phase is past player
			if (position.y >= player->getPos().y)
			{
				attackPhase++;
			}
		}
		//*****disapear off screen and reappear above
		else if (attackPhase == 1)
		{
			//keep velocity

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
			Vector2 desieredVel{ 0, 0 };
			Vector2 force{ 0, 0 };

			// Get the diference in position to find the heading
			desieredVel = Vector2Subtract(formationPos, position);
			// If non-zero, normalise
			if (desieredVel.x != 0.0f && desieredVel.y != 0.0f)
				desieredVel = Vector2Normalize(desieredVel);
			// Multiply the heading by the max speed to get desiered velocity
			desieredVel = Vector2Scale(desieredVel, 300);


			// Find the force nessesary to change the velocity
			force = Vector2Subtract(desieredVel, attackVel);
			// If non-zero, normalise to the base value
			if (force.x != 0.0f && force.y != 0.0f)
			{
				force = Vector2Normalize(force);
				force = Vector2Scale(force, 500);
			}

			//apply force
			attackVel = Vector2Add(attackVel, Vector2Scale(force, deltaTime));


			//if close to formation position, reenter formation
			if (Vector2Distance(position, formationPos) < 15)
			{
				attackPhase = 0;
				attackVel = Vector2Zero();
				attacking = false;
			}
		}


		//apply velocity
		position = Vector2Add(position, Vector2Scale(attackVel, deltaTime));
	}
	else
	{
		position = formationPos;

		//1 in 10 chance each second to attack
		int val = rand() % (int)(10 * (1/deltaTime));
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
}