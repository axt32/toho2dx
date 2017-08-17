#pragma once

#include "cocos2d.h"
#include "GamePlayer.h"
#include "GameEnemy.h"
#include "GameBullet.h"

class GameStage : public cocos2d::Scene		//원래는 Scene 였음
{

public:
	GamePlayer m_Player;

public:
	cocos2d::Sprite * m_sprBackground;
	cocos2d::Point touchPoint;
	float angleOffset;
	cocos2d::Layer * layerEnemyBullet;

	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(GameStage);

	void MovePlayer(float IN_fDestX, float IN_fDestY);
	void FireBullet();

	void PlayerFireBullet();

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event);

	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuChangeCallback(cocos2d::Ref* pSender);
	void menuBomberCallback(cocos2d::Ref* pSender);

//	void spriteMoveFinished(cocos2d::CCNode* sender);
};