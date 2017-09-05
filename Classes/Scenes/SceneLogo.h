#pragma once

#include "cocos2d.h"
USING_NS_CC;

class SceneLogo : public cocos2d::Scene
{
public:
	cocos2d::Sprite * m_sprGameLogo;

	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(SceneLogo);

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event);

};