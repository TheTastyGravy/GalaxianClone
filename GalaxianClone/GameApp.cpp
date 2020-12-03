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

	GameObject* player = new Player({ 500, 500 }, 270, 200, SCREEN_WIDTH);


	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			new Enemy({ (float)(100 + 60 * x), (float)(100 + 50 * y) }, 0, { (float)SCREEN_WIDTH, (float)SCREEN_HIGHT });
		}
	}

	Enemy::setupEnemies({ 200, 0 }, player);
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