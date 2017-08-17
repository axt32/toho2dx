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
	//Custom Function ȣ��
	pCustomFunction->InitCustomFunction();
}

void GameEnemyBullet::update(float dt)
{
	//Custom Function ȣ��
	pCustomFunction->Run();

	GameObject::update(dt);		//MFC�� �䳻���� �����Լ� ȣ���� �Ʒ��ܿ� �־���.
}