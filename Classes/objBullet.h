#pragma once
#include "cocos2d.h"
USING_NS_CC;

class objBullet : public Sprite
{
private:
	float dirX, dirY;

public:
	objBullet();
	~objBullet();

	static objBullet * createAndInit( float rotation );
	void update(float dt);
};