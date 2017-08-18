#include "GameCommonObject.h"

GameCommonObject::GameCommonObject()
{
	pCustomFunction = nullptr;
}

GameCommonObject::~GameCommonObject()
{
	if (pCustomFunction != nullptr)
	{
		delete pCustomFunction;
	}
}

void GameCommonObject::InvokeInit()
{
	//Custom Function 호출
	pCustomFunction->InitCustomFunction();
}

void GameCommonObject::update(float dt)
{
	//Custom Function 호출
	if ( pCustomFunction != nullptr)
	{ 
		pCustomFunction->Run();
	}


	GameBaseObject::update(dt);		//MFC를 흉내내어 가상함수 호출을 아랫단에 넣었다.
}