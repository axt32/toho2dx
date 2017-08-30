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
	//Custom Function ȣ��
	m_pCustomFunction->InitCustomFunction();
}

void GameCommonObject::update(float dt)
{
	//Custom Function ȣ��
	if ( m_pCustomFunction != nullptr)
	{ 
		m_pCustomFunction->Run();
	}

	GameBaseObject::update(dt);		//MFC�� �䳻���� �����Լ� ȣ���� �Ʒ��ܿ� �־���.
}