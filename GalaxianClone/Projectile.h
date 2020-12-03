#pragma once
#include "GameObject.h"


class Projectile : public GameObject
{
public:
	Projectile(Vector2 position, float rotation, float speed);
	~Projectile();

	void update(float deltaTime) override;
	void draw() override;

	bool enabled;

private:
	Vector2 velocity;

	float timer;

	
};