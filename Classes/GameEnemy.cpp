#include "GameEnemy.h"
#include "GameUtil.h"
#include "Common.h"

GameEnemy::GameEnemy()
{
	m_iHP = 1;
	m_bInsideCheck = true;
	m_bBoundaryCheck = true;
}

GameEnemy::~GameEnemy()
{

}

void GameEnemy::update(float dt)
{
	if (GameUtil::CircleCollisionCheck(g_pGameStage->m_Player.GetPosition().x, g_pGameStage->m_Player.GetPosition().y, g_pGameStage->m_Player.m_fCollisionRadius, this->getPositionX(), this->getPositionY(), this->m_fCollisionRadius))
	{
		CCLOG("Player Damaged!!");
		g_pGameStage->MakeExplosion(this->getPositionX(), this->getPositionY(), true);
		g_pGameStage->MakeExplosion(g_pGameStage->m_Player.GetPosition().x, g_pGameStage->m_Player.GetPosition().y);
		this->removeFromParent();
		return;
	}

	GameCommonObject::update(dt);
}