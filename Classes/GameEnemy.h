#pragma once
#include "GameEnemyBullet.h"

#define ENEMY_TYPE1_WIDTH 30
#define ENEMY_TYPE1_HEIGHT 29
#define ENEMY_TYPE1_FRAMES 4

class GameEnemy : public GameEnemyBullet
{
public:
	GameEnemy();
	~GameEnemy();

};