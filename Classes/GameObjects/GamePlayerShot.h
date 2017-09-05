#pragma once
#include "GameCommonObject.h"

class GamePlayerShot : public GameCommonObject
{
public:
	int m_iDamage;

	GamePlayerShot();
	~GamePlayerShot();

	virtual void update(float dt);
};