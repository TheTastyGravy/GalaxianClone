#include "Player.h"
#include "Projectile.h"


Player::Player(Vector2 position, float rotation, float speed) :
	GameObject(position, rotation),
	speed(speed)
{
	addTag(Tag::Player);
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

	DrawTriangle(v1, v2, v3, WHITE);
}

void Player::update(float deltaTime)
{
	Vector2 force = { 0,0 };

	if (IsKeyDown(KEY_W))
	{ force.y = -1; }
	if (IsKeyDown(KEY_S))
	{ force.y = 1; }
	if (IsKeyDown(KEY_A))
	{ force.x = -1; }
	if (IsKeyDown(KEY_D))
	{ force.x = 1; }

	force = Vector2Scale(force, deltaTime * speed);
	position = Vector2Add(position, force);



	if (IsKeyPressed(KEY_SPACE))
	{
		shoot();
	}
}

void Player::shoot()
{
	new Projectile(position, rotation, 250);
}