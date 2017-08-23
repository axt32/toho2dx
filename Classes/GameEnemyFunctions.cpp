#include "GameEnemyFunctions.h"
#include "Common.h"

using namespace EnemyFunctions;

//Test Function

EnemyFunction_Test::EnemyFunction_Test()
{

}

EnemyFunction_Test::~EnemyFunction_Test()
{
	CCLOG("EnemyFunction Test Destructor Invoked!");
}

void EnemyFunction_Test::InitCustomFunction()
{
	CCLOG("EnemyFunction Test Init Invoked!");
}
void EnemyFunction_Test::Run()
{
	CCLOG("EnemyFunction Test Run Invoked!");
}

Stage1_Pattern1::Stage1_Pattern1()
{
	
}

Stage1_Pattern1::~Stage1_Pattern1()
{

}


void Stage1_Pattern1::InitCustomFunction()
{
	float x = float(GAME_WIDTH) + 50.f;
	float y = float(RandomHelper::random_int(0, GAME_HEIGHT));
	float fDestX = - 50.f;
	float fDestY = float(RandomHelper::random_int(0, GAME_HEIGHT));

	ccBezierConfig bezierConfig;
	Vec2 startpoint = Vec2(x, y);
	Vec2 endpoint = Vec2(fDestX, fDestY);

	bezierConfig.controlPoint_1 = Vec2(fDestX, fDestY + float(RandomHelper::random_int(0, int(abs(fDestY - y)))));
	bezierConfig.controlPoint_2 = Vec2(fDestX + float(RandomHelper::random_int(0, int(abs(fDestX - x)))), fDestY);
	bezierConfig.endPosition = endpoint;

	BezierTo * bezierTo = BezierTo::create(float(RandomHelper::random_int(m_iMinimumDuration, m_iMaximumDuration)) / 10.f, bezierConfig);
	m_pObject->setPosition(startpoint);
	m_pObject->runAction(Sequence::create(bezierTo, RemoveSelf::create(), NULL));		//����� ������ �ڵ����� �����ִµ�?

}
void Stage1_Pattern1::Run()
{

}