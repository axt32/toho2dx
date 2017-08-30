#include "GameCommonObject.h"

GameCommonObject::GameCommonObject()
{
	m_pCustomFunction = nullptr;
}

GameCommonObject::~GameCommonObject()
{
	if (m_pCustomFunction != nullptr)
	{
		delete m_pCustomFunction;
	}
}

void GameCommonObject::InvokeInit()
{
	//Custom Function 호출
	m_pCustomFunction->InitCustomFunction();
}

void GameCommonObject::update(float dt)
{
	//Custom Function 호출
	if ( m_pCustomFunction != nullptr)
	{ 
		m_pCustomFunction->Run();
	}

	GameBaseObject::update(dt);		//MFC를 흉내내어 가상함수 호출을 아랫단에 넣었다.
}