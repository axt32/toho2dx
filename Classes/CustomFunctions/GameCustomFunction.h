#pragma once
#include "cocos2d.h"
#include "../GameObjects/GameBaseObject.h"
USING_NS_CC;

//상속받아 사용
class GameCustomFunction
{
public:
	GameBaseObject * m_pObject;

	virtual void InitCustomFunction() = 0;		//순수 가상함수이므로 하위 클래스에서 이 함수를 굳이 호출하지 않아도 된다.
	virtual void Run() = 0;

	GameCustomFunction();
	virtual ~GameCustomFunction();
};