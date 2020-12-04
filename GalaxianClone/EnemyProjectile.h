#pragma once
#include "GameObject.h"
#include "Player.h"


class EnemyProjectile : public GameObject
{
public:
	EnemyProjectile(Vector2 position, float rotation, float speed);
	~EnemyProjectile();

	void update(float deltaTime) override;
	void draw() override;

private:
	float timer;

	Vector2 velocity;
};