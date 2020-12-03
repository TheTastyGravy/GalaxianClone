#pragma once
#include <vector>
#include <string>
#include "GameObject.h"


class GameApp
{
public:
	GameApp() {}
	virtual ~GameApp() {}

	void run();

	void update(std::vector<GameObject*>& objects);
	void draw(std::vector<GameObject*>& objects);

	void startup();
	void shutdown();

protected:
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HIGHT = 600;

};