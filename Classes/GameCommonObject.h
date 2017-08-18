#pragma once
#include "GameBaseObject.h"
#include "GameCustomFunction.h"

class GameCommonObject : public GameBaseObject
{
public:
	GameCommonObject();
	virtual ~GameCommonObject();

	GameCustomFunction * pCustomFunction;

	void InvokeInit();
	virtual void update(float dt);
};