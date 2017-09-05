#pragma once
#include "GameBaseObject.h"
#include "../CustomFunctions/GameCustomFunction.h"

class GameCommonObject : public GameBaseObject
{
public:
	GameCommonObject();
	virtual ~GameCommonObject();

	GameCustomFunction * m_pCustomFunction;

	void InvokeInit();
	virtual void update(float dt);
};