#pragma once
#include "GameCommonObject.h"

class GameEnemyShot : public GameCommonObject
{
public:
	GameEnemyShot();
	~GameEnemyShot();

	virtual void update(float dt);
};