#pragma once
#include "GameCommonObject.h"

class GameEnemy : public GameCommonObject
{
public:
	int m_iHP;

	GameEnemy();
	~GameEnemy();

	virtual void update(float dt);
};