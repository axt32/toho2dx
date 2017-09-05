#pragma once

#include "cocos2d.h"
#include "GameObjects/GamePlayer.h"
#include "CustomFunctions/GameCustomFunction.h"

class GamePlayerShot;
class SceneStage : public cocos2d::Scene
{

public:
	GamePlayer m_Player;

	int m_iCurrentFrame;

public:
	cocos2d::Sprite * m_sprBackground;
	cocos2d::Point touchPoint;
	float angleOffset;

	cocos2d::Layer * m_pLayerPlayerShot;
	cocos2d::Layer * m_pLayerEnemy;
	cocos2d::Layer * m_pLayerEnemyShot;
	cocos2d::Layer * m_pLayerExplosion;

	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(SceneStage);

	void MovePlayer(float IN_fDestX, float IN_fDestY);
	void PlayerFireBullet();

	void MakeEnemy();
	void MakeEnemyShot(int IN_iBulletType, int IN_iBulletSubStyle, float IN_fX, float IN_fY, float IN_fSpeed, float IN_fAddSpeed, float IN_fAngle, float IN_fAddAngle, GameCustomFunction * IN_pBarrageFunction = nullptr);
	
	void MakeExplosion(float IN_fX, float IN_fY, bool IN_bSmallExplosion = false);

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event);

	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuChangeCallback(cocos2d::Ref* pSender);
	void menuBomberCallback(cocos2d::Ref* pSender);

//	void spriteMoveFinished(cocos2d::CCNode* sender);
};