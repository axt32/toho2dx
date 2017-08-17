#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "VaListElement.h"
#include <vector>

//��ӹ޾� ���
class GameCustomFunction
{
public:
	std::vector<VaListElement> m_vecVaListElement;

	virtual void Init(void * pParams, ...) = 0;
	virtual void Run(void * pParams, ...) = 0;

	GameCustomFunction();
	~GameCustomFunction();
};