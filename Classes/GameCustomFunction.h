#pragma once
#include "cocos2d.h"
USING_NS_CC;

//��ӹ޾� ���
class GameCustomFunction
{
public:
	virtual void InitCustomFunction() = 0;		//���� �����Լ��̹Ƿ� ���� Ŭ�������� �� �Լ��� ���� ȣ������ �ʾƵ� �ȴ�.
	virtual void Run() = 0;

	GameCustomFunction();
	virtual ~GameCustomFunction();
};