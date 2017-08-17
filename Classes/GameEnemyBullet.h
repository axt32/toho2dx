#pragma once
#include "GameObject.h"
#include "GameCustomFunction.h"

class GameEnemyBullet : public GameObject
{
public:
	GameCustomFunction * pInitFunciton;
	GameCustomFunction * pRunFunction;

	

	virtual void update(float dt);
};