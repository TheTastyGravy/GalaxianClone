#pragma once
#include "GameObject.h"
#include "Player.h"


class Enemy : public GameObject
{
public:
	Enemy(Vector2 position, float rotation, Vector2 screenSize);
	~Enemy();

	void update(float deltaTime) override;
	void draw() override;

	static void setupEnemies(Player* playerObj)
	{
		player = playerObj;

		randShoot = 0;
		randAttack = 0;
		isAttacking = false;
	}

	static void updateEnemies(float deltaTime);

	void shoot();

protected:
	static float randShoot;
	static float randAttack;
	static bool isAttacking;

	static Player* player;

	Vector2 formationPos;

	bool attacking;
	int attackPhase;
	Vector2 attackVel;
	float shootTimer;

	Vector2 screenSize;
};