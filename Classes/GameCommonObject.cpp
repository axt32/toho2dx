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
	//Custom Function ȣ��
	pCustomFunction->InitCustomFunction();
}

void GameCommonObject::update(float dt)
{
	//Custom Function ȣ��
	if ( pCustomFunction != nullptr)
	{ 
		pCustomFunction->Run();
	}


	GameBaseObject::update(dt);		//MFC�� �䳻���� �����Լ� ȣ���� �Ʒ��ܿ� �־���.
}