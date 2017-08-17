#pragma once
#include "GameObject.h"
#include "GameCustomFunction.h"

class GameEnemyBullet : public GameObject
{
public:
	GameEnemyBullet();
	virtual ~GameEnemyBullet();

	GameCustomFunction * pCustomFunction;

	void InvokeInit();
	virtual void update(float dt);
};