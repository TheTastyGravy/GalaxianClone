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

	static void setupEnemies(Vector2 velocity, Player* playerObj)
	{
		formationVel = velocity;
		player = playerObj;
	}

protected:
	static Vector2 formationVel;
	static Player* player;

	Vector2 formationPos;

	bool attacking;
	int attackPhase;
	Vector2 attackVel;

	Vector2 screenSize;
};