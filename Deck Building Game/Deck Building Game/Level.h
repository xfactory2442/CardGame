#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Player.h"
#include "EnemyManager.h"

class Level
{
public:
	Level();
	~Level();
	bool Update(float dt);
	void Render();

private:
	void Begin_Draw();
	void End_Draw();

	bool turn_ = true; //turn_ = true : player turn.
	Player player_;
	EnemyManager* enemy_manager_ = nullptr;
};

