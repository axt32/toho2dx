#include "GameEnemyBullet.h"

GameEnemyBullet::GameEnemyBullet()
{
	pCustomFunction = nullptr;
}

GameEnemyBullet::~GameEnemyBullet()
{
	if (pCustomFunction != nullptr)
	{
		delete pCustomFunction;
	}
}

void GameEnemyBullet::InvokeInit()
{
	//Custom Function 호출
	pCustomFunction->InitCustomFunction();
}

void GameEnemyBullet::update(float dt)
{
	//Custom Function 호출
	pCustomFunction->Run();

	GameObject::update(dt);		//MFC를 흉내내어 가상함수 호출을 아랫단에 넣었다.
}