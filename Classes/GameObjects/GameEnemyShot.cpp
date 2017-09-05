#include "GameEnemyShot.h"
#include "Common.h"
#include "GameUtil.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

GameEnemyShot::GameEnemyShot()
{
	m_bInsideCheck = false;
	m_bBoundaryCheck = true;
}

GameEnemyShot::~GameEnemyShot()
{

}

void GameEnemyShot::update(float dt)
{
	if (GameUtil::CircleCollisionCheck(g_pSceneStage->m_Player.GetPosition().x, g_pSceneStage->m_Player.GetPosition().y, g_pSceneStage->m_Player.m_fCollisionRadius, this->getPositionX(), this->getPositionY(), this->m_fCollisionRadius))
	{
		CCLOG("Player Damaged!!");
		SimpleAudioEngine::getInstance()->playEffect("se/playerdead.wav", false);
		g_pSceneStage->MakeExplosion(this->getPositionX(), this->getPositionY(), true);
		g_pSceneStage->MakeExplosion(g_pSceneStage->m_Player.GetPosition().x, g_pSceneStage->m_Player.GetPosition().y);
		this->removeFromParent();
		return;
	}

	GameCommonObject::update(dt);
}