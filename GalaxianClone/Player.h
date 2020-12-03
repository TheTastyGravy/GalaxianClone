#pragma once
#include "GameObject.h"


class Player : public GameObject
{
public:
	Player(Vector2 position, float rotation, float speed);
	~Player();

	void update(float deltaTime) override;
	void draw() override;


private:
	void shoot();

	float speed;


};