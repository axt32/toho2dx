#include "GamePlayerShot.h"
#include "Common.h"
#include "GameEnemy.h"
#include "GameUtil.h"

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
	int iCount = g_pGameStage->m_pLayerEnemy->getChildrenCount();

	for (int i = 0; i < iCount; i++)
	{
		CCNode * child = g_pGameStage->m_pLayerEnemy->getChildren().at(i);
		GameEnemy * pObj = dynamic_cast<GameEnemy*>(child);

		if (GameUtil::CircleCollisionCheck(pObj->getPositionX(), pObj->getPositionY(), pObj->m_fCollisionRadius, this->getPositionX(), this->getPositionY(), this->m_fCollisionRadius))
		{
			pObj->m_iHP -= this->m_iDamage;
			g_pGameStage->MakeExplosion(this->getPositionX(), this->getPositionY(), true);

			if (pObj->m_iHP <= 0)
			{
				g_pGameStage->MakeExplosion(pObj->getPositionX(), pObj->getPositionY(), false);
				pObj->removeFromParent();
			}

			this->removeFromParent();
			return;
		}
	}

	GameCommonObject::update(dt);
}