#include "Player.h"
#include <string>


Player::Player(Vector2 position, float rotation, float speed, int screenSizeX) :
	GameObject(position, rotation),
	speed(speed),
	screenSizeX(screenSizeX),
	lives(3),
	isInvulnerable(false),
	invulnTimer(0),
	gameOver(false),
	score(0)
{
	addTag(Tag::Player);

	//create projectile
	proj = new Projectile({ 0, 0 }, 270, 250, this);
}

Player::~Player()
{
}


void Player::draw()
{
	// Display player as a triangle
	Vector2 v1 = { 8, 0 };
	v1 = Vector2Rotate(v1, rotation);
	v1 = Vector2Add(v1, position);

	Vector2 v2 = { -10, -6.5f };
	v2 = Vector2Rotate(v2, rotation);
	v2 = Vector2Add(v2, position);

	Vector2 v3 = { -10, +6.5f };
	v3 = Vector2Rotate(v3, rotation);
	v3 = Vector2Add(v3, position);

	

	if (isInvulnerable)
	{
		//blink when invuln
		float dec = floor(invulnTimer);
		DrawTriangle(v1, v2, v3, (invulnTimer - dec < 0.5f) ? DARKGRAY : WHITE);
	}
	else
	{
		DrawTriangle(v1, v2, v3, WHITE);
	}

	//display score and lives
	DrawText(("Score: " + std::to_string(score)).c_str(), 20, 20, 30, WHITE);
	DrawText(("Lives: " + std::to_string(lives)).c_str(), screenSizeX - 125, 20, 30, WHITE);
}

void Player::update(float deltaTime)
{
	//use timer to unset invuln after 3 seconds
	if (isInvulnerable)
	{
		invulnTimer += deltaTime;
		if (invulnTimer > 3)
		{
			isInvulnerable = false;
		}
	}

	//get movement
	Vector2 force = { 0,0 };
	if (IsKeyDown(KEY_A) && position.x > 20)
	{
		force.x = -1;
	}
	if (IsKeyDown(KEY_D) && position.x < screenSizeX - 20)
	{
		force.x = 1;
	}

	force = Vector2Scale(force, deltaTime * speed);
	position = Vector2Add(position, force);


	if (IsKeyPressed(KEY_SPACE))
	{
		shoot();
	}
}

void Player::shoot()
{
	//the player only has 1 projectile at a time, and cant shoot while invuln
	if (!proj->enabled && !isInvulnerable)
	{
		proj->enabled = true;
		proj->setPos(position);
	}
}


void Player::damage()
{
	if (isInvulnerable)
	{
		return;
	}

	lives--;
	isInvulnerable = true;
	invulnTimer = 0;


	if (lives < 0)
	{
		gameOver = true;
	}
}