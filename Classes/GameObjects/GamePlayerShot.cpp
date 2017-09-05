#include "GamePlayerShot.h"
#include "Common.h"
#include "GameEnemy.h"
#include "GameUtil.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

GamePlayerShot::GamePlayerShot()
{
	m_bInsideCheck = false;
	m_bBoundaryCheck = true;
	m_iDamage = 1;
}
GamePlayerShot :: ~GamePlayerShot()
{
	
}

void GamePlayerShot::update(float dt)
{
	int iCount = g_pSceneStage->m_pLayerEnemy->getChildrenCount();

	for (int i = 0; i < iCount; i++)
	{
		CCNode * child = g_pSceneStage->m_pLayerEnemy->getChildren().at(i);
		GameEnemy * pObj = dynamic_cast<GameEnemy*>(child);

		if (GameUtil::CircleCollisionCheck(pObj->getPositionX(), pObj->getPositionY(), pObj->m_fCollisionRadius, this->getPositionX(), this->getPositionY(), this->m_fCollisionRadius))
		{
			pObj->m_iHP -= this->m_iDamage;
			g_pSceneStage->MakeExplosion(this->getPositionX(), this->getPositionY(), true);

			if (pObj->m_iHP <= 0)
			{
				g_pSceneStage->MakeExplosion(pObj->getPositionX(), pObj->getPositionY(), false);
				pObj->removeFromParent();
				SimpleAudioEngine::getInstance()->playEffect("se/enemydead.wav", false);
			}
			else
			{
				SimpleAudioEngine::getInstance()->playEffect("se/enemydamaged.wav", false);
			}

			this->removeFromParent();
			return;
		}
	}

	GameCommonObject::update(dt);
}