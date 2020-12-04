#include "GameApp.h"
#include <time.h>
#include <string>
#include "raylib.h"
#include "GameObjectPool.h"

#include "Player.h"
#include "Enemy.h"


void GameApp::run()
{
	startup();

	// Game loop
	while (!WindowShouldClose())
	{
		update(GameObjectPool::getPool());
		draw(GameObjectPool::getPool());
	}

	shutdown();
}


void GameApp::update(std::vector<GameObject*>& objects)
{
	float deltaTime = GetFrameTime();

	// Update objects
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->update(deltaTime);
	}

	Enemy::updateEnemies(deltaTime);
}

void GameApp::draw(std::vector<GameObject*>& objects)
{
	BeginDrawing();
	ClearBackground(BLACK);

	// Draw objects
	for (auto object : objects)
	{
		object->draw();
	}

	EndDrawing();
}


void GameApp::startup()
{
	// Setup window
	InitWindow(SCREEN_WIDTH, SCREEN_HIGHT, "Galaxian");
	SetTargetFPS(60);

	Player* player = new Player({ SCREEN_WIDTH*0.5f, SCREEN_HIGHT*0.9f }, 270, 200, SCREEN_WIDTH);


	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			new Enemy({ (float)(100 + 65 * x), (float)(100 + 55 * y) }, 90, { (float)SCREEN_WIDTH, (float)SCREEN_HIGHT });
		}
	}

	Enemy::setupEnemies(player);
}

void GameApp::shutdown()
{
	CloseWindow();

	std::vector<GameObject*> objects = GameObjectPool::getPool();

	// Delete all objects
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
}