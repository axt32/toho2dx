#pragma once
#include "cocos2d.h"
#include "../GameObjects/GameBaseObject.h"
USING_NS_CC;

//��ӹ޾� ���
class GameCustomFunction
{
public:
	GameBaseObject * m_pObject;

	virtual void InitCustomFunction() = 0;		//���� �����Լ��̹Ƿ� ���� Ŭ�������� �� �Լ��� ���� ȣ������ �ʾƵ� �ȴ�.
	virtual void Run() = 0;

	GameCustomFunction();
	virtual ~GameCustomFunction();
};