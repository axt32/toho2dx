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

Stage1_EnemyPattern1::Stage1_EnemyPattern1()
{
	m_iBulletStyle = 1;
	m_iBulletSubStyle = 0;
	m_iBulletQuantity = 1;

	m_iShotBulletCurrentFrame = 0;
	m_iShotBulletDestFrame = 10;
}

Stage1_EnemyPattern1::~Stage1_EnemyPattern1()
{

}


void Stage1_EnemyPattern1::InitCustomFunction()
{
	float x = float(GAME_WIDTH) + 50.f;
	float y = float(RandomHelper::random_int(0, GAME_HEIGHT));
	float fDestX = - 50.f;
	float fDestY = float(RandomHelper::random_int(0, GAME_HEIGHT));

	ccBezierConfig bezierConfig;
	Vec2 startpoint = Vec2(x, y);
	Vec2 endpoint = Vec2(fDestX, fDestY);

	bezierConfig.controlPoint_1 = Vec2(fDestX, fDestY + float(RandomHelper::random_int(0, int(abs(fDestY - y)))));
//	bezierConfig.controlPoint_2 = Vec2(fDestX + float(RandomHelper::random_int(0, int(abs(fDestX - x)))), fDestY);
	bezierConfig.controlPoint_2 = Vec2(800, fDestY);
	bezierConfig.endPosition = endpoint;

	BezierTo * bezierTo = BezierTo::create(float(RandomHelper::random_int(m_iMinimumDuration, m_iMaximumDuration)) / 10.f, bezierConfig);
	m_pObject->setPosition(startpoint);
	m_pObject->runAction(Sequence::create(bezierTo, RemoveSelf::create(), NULL));		//베지어가 끝나면 자동으로 지워주는듯?

	m_iShotBulletCurrentFrame = RandomHelper::random_int(0, m_iShotBulletDestFrame - 1);
}
void Stage1_EnemyPattern1::Run()
{
	if (m_pObject->GetInsideStatus() == true)
	{
		if (++m_iShotBulletCurrentFrame == m_iShotBulletDestFrame)
		{
			for (int i = 0; i < m_iBulletQuantity; i++)
			{
				g_pSceneStage->MakeEnemyShot(m_iBulletStyle, m_iBulletSubStyle, m_pObject->getPositionX(), m_pObject->getPositionY(), (float)RandomHelper::random_int(15, 23) / 10.f, 0.f, (float)RandomHelper::random_int(0, 360), 0.f);
			}

			m_iShotBulletCurrentFrame = 0;
		}
	}
}