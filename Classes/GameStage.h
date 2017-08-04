//#ifndef __HELLOWORLD_SCENE_H__
//#define __HELLOWORLD_SCENE_H__

#pragma once

#include "cocos2d.h"
#include "GamePlayer.h"

class GamePlayer;
class GameStage : public cocos2d::Scene		//원래는 Scene 였음
{

public:
	GamePlayer m_Player;

public:
	cocos2d::Sprite * m_sprWallpaper;
	cocos2d::Point touchPoint;
	float angleOffset;
	cocos2d::Layer * layerPlayer;
	cocos2d::Layer * layerBullet;

	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuChangeCallback(cocos2d::Ref* pSender);
	void menuBomberCallback(cocos2d::Ref* pSender);


	virtual void update(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(GameStage);

	void MovePlayer(float IN_fDestX, float IN_fDestY);
	void FireBullet();

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event);

	void spriteMoveFinished(cocos2d::CCNode* sender);

};

//#endif // __HELLOWORLD_SCENE_H__
