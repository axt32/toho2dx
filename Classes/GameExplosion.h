#pragma once
#include "GameCommonObject.h"

class GameExplosion : public GameCommonObject
{
public:
	GameExplosion();
	~GameExplosion();

	virtual void update(float dt);
};