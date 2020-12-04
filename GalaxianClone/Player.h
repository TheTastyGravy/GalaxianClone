#pragma once
#include "GameObject.h"
#include "Projectile.h"


class Player : public GameObject
{
public:
	Player(Vector2 position, float rotation, float speed, int screenSizeX);
	~Player();

	void update(float deltaTime) override;
	void draw() override;

	void damage();
	void addScore(int score) { this->score += score; }
	int getScore() { return score; }

	bool gameOver;

private:
	void shoot();

	float speed;

	int screenSizeX;

	Projectile* proj;

	int score;
	int lives;
	bool isInvulnerable;
	float invulnTimer;

};