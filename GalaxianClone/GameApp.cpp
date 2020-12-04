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

	if (gameOver)
	{
		//space will restart the game
		if (IsKeyPressed(KEY_SPACE))
		{
			startGame();
		}
	}
	else
	{
		Enemy::updateEnemies(deltaTime);

		// Update objects
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->update(deltaTime);
		}

		gameOver = static_cast<Player*>(GameObjectPool::searchForTag(Tag::Player)[0])->gameOver;
	}
}

void GameApp::draw(std::vector<GameObject*>& objects)
{
	BeginDrawing();
	ClearBackground(BLACK);

	if (gameOver)
	{
		DrawText("Game Over", SCREEN_WIDTH / 2 - MeasureText("Game Over", 40) / 2, SCREEN_HIGHT / 4 - 40 / 2, 40, WHITE);

		DrawText("Press space to replay", SCREEN_WIDTH / 2 - MeasureText("Press space to replay", 25) / 2, SCREEN_HIGHT / 2 - 25 / 2, 25, WHITE);
	}
	else
	{
		// Draw objects
		for (auto object : objects)
		{
			object->draw();
		}
	}

	EndDrawing();
}


void GameApp::startup()
{
	// Setup window
	InitWindow(SCREEN_WIDTH, SCREEN_HIGHT, "Galaxian");
	SetTargetFPS(60);

	startGame();
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


void GameApp::startGame()
{
	//clear object pool
	std::vector<GameObject*> objects = GameObjectPool::getPool();
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}


	Player* player = new Player({ SCREEN_WIDTH * 0.5f, SCREEN_HIGHT * 0.9f }, 270, 200, SCREEN_WIDTH);

	//create enemies
	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			new Enemy({ (float)(100 + 65 * x), (float)(100 + 55 * y) }, 90, { (float)SCREEN_WIDTH, (float)SCREEN_HIGHT });
		}
	}
	Enemy::setupEnemies(player);


	gameOver = false;
}